
#include "pjmsrp/pjmsrp_parser_uri.h"

/***********************************
*	Ragel state machine.
*/
%%{
	machine pjmsrp_machine_parser_uri;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}

	#/* Sets HOST type */
	action is_ipv4 { uri->authority.host_type = pjmsrp_host_ipv4; }
	action is_ipv6 { uri->authority.host_type = pjmsrp_host_ipv6; }
	action is_hostname { uri->authority.host_type = pjmsrp_host_hostname; }

	action parse_scheme{
		PJMSRP_PARSER_SET_STRING(pool, uri->scheme);
	}

	action parse_userinfo{
		PJMSRP_PARSER_SET_STRING(pool, uri->authority.userinfo);
	}

	action parse_host{
		PJMSRP_PARSER_SET_STRING(pool, uri->authority.host);
		if(uri->authority.host_type == pjmsrp_host_ipv6){
			pj_strunquote_2(&uri->authority.host.ptr, '[', ']');
			uri->authority.host.slen = uri->authority.host.slen -2;
		}
	}

	action parse_port{
		PJMSRP_PARSER_SET_INT(pool, uri->authority.port);
	}

	action parse_session_id{
		PJMSRP_PARSER_SET_STRING(pool, uri->session_id);
	}

	action parse_transport{
		PJMSRP_PARSER_SET_STRING(pool, uri->transport);
	}

	action parse_param{
		PJMSRP_PARSER_ADD_PARAM(pool, uri->params);
	}
	
	

	#//MSRP-URI	=  	msrp-scheme  "://" authority  ["/" session-id] ";" transport  *( ";" URI-parameter)
	#//msrp-scheme	= 	"msrp" / "msrps"
	#//session-id	= 	1*( unreserved / "+" / "=" / "/" )
	#//transport	= 	"tcp" / 1*ALPHANUM
	#//URI-parameter	= 	token ["=" token]
	#//authority	=  	[ userinfo  "@" ]   host    [ ":"   port ] 

	msrp_scheme = ("msrp" | "msrps")>tag %parse_scheme;

	userinfo = (unreserved | pct_encoded | sub_delims | ":")* >tag %parse_userinfo;
	myhost = ((IPv6reference >is_ipv6)>2 | (IPv4address >is_ipv4)>1 | (hostname >is_hostname)>0)>tag %parse_host;
	authority = (userinfo "@")? myhost (":" port>tag %parse_port)?;
	
	session_id = (unreserved | "+" | "=" | "/")+ >tag %parse_session_id;

	transport = ("tcp" | alphanum*)>tag %parse_transport;

	URI_parameter = (token ("=" token)?)>tag %parse_param;

	URI = msrp_scheme "://" authority ("/" session_id)? ";" transport ( ";" URI_parameter)*;
	
	# Entry point
	main := URI;
}%%

PJ_DEF(pjmsrp_uri_t*) pjmsrp_uri_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_uri_t *uri = pjmsrp_uri_create(pool);
	
	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_uri_first_final);
	(void)(pjmsrp_machine_parser_uri_error);
	(void)(pjmsrp_machine_parser_uri_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < %%{ write first_final; }%% ){
		 PJ_LOG(3, ("pjmsrp_parser_uri.c", "Failed to parse MSRP/MSRPS header."));
	}
	
	return uri;
}