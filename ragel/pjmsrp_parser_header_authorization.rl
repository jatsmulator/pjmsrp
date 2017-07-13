/* 
* Copyright (C) 2016 John Li.
*
* Contact: John Li <jatsmulator(at)gmail.com>
*
* PJRCS is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* PJRCS is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PJRCS; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/
 
/**@file pjmsrp_parser_header_byte_range.rl
 * @brief MSRP "From-Path" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 #include "pjmsrp/pjmsrp_header_authorization.h"
 
/***********************************
*	Ragel state machine.
*/
%%{
	machine pjmsrp_machine_parser_header_authorization;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}
	
	action is_digest{
		pj_strdup2_with_null(pool, &hdr_Authorization->scheme, "Digest");
	}

	action is_basic{
		pj_strdup2_with_null(pool, &hdr_Authorization->scheme, "Basic");
	}

	action is_auth{
		hdr_Authorization->type = pjmsrp_http_htype_Authorization;
	}

	action is_proxy{
		hdr_Authorization->type = pjmsrp_http_htype_Proxy_Authorization;
	}

	action parse_username{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->username);
		pj_strunquote(&hdr_Authorization->username);
	}

	action parse_realm{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->realm);
		pj_strunquote(&hdr_Authorization->realm);
	}

	action parse_nonce{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->nonce);
		pj_strunquote(&hdr_Authorization->nonce);
	}

	action parse_uri{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->uri);
	}

	action parse_response{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->response);
		pj_strunquote(&hdr_Authorization->response);
	}

	action parse_algorithm{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->algorithm);
	}

	action parse_cnonce{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->cnonce);
		pj_strunquote(&hdr_Authorization->cnonce);
	}

	action parse_opaque{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->opaque);
		pj_strunquote(&hdr_Authorization->opaque);
	}

	action parse_qop{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->qop);
		//pj_strunquote(&hdr_Authorization->qop);
	}

	action parse_nc{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Authorization->nc);
	}

	action parse_param{
		PJMSRP_PARSER_ADD_PARAM(pool, hdr_Authorization->params);
	}

	action eob{
	}
	
	#FIXME: Only Digest (MD5, AKAv1-MD5 and AKAv2-MD5) is supported
	qop_value  = "auth" | "auth-int" | token;
	other_response = (any+);
	auth_param = generic_param>tag %parse_param;
	
	username = "username"i EQUAL quoted_string>tag %parse_username;
	realm = "realm"i EQUAL quoted_string>tag %parse_realm;
	nonce = "nonce"i EQUAL quoted_string>tag %parse_nonce;
	digest_uri = "uri"i EQUAL LDQUOT <: (any*)>tag %parse_uri :> RDQUOT;
	#dresponse = "response"i EQUAL LDQUOT <: (LHEX{32})>tag %parse_response :> RDQUOT;
	dresponse = "response"i EQUAL quoted_string>tag %parse_response;
	algorithm = "algorithm"i EQUAL <:token>tag %parse_algorithm;
	cnonce = "cnonce"i EQUAL quoted_string>tag %parse_cnonce;
	opaque = "opaque"i EQUAL quoted_string>tag %parse_opaque;
	message_qop = "qop"i EQUAL qop_value>tag %parse_qop;
	nonce_count = "nc"i EQUAL (LHEX{8})>tag %parse_nc;
	
	dig_resp = (username | realm | nonce | digest_uri | dresponse | algorithm | cnonce | opaque | message_qop | nonce_count)@1 | auth_param@0;
	digest_response = dig_resp ( COMMA <:dig_resp )*;
	credentials = ( ("Digest"i%is_digest | "Basic"i%is_basic) LWS digest_response ) | other_response;
	Authorization = ("Authorization"i>is_auth | "Proxy-Authorization"i>is_proxy) HCOLON credentials;

	# Entry point
	main := Authorization :>CRLF @eob;

}%%

PJ_DEF(pjmsrp_header_authorization_t*) pjmsrp_header_authorization_create(pj_pool_t* pool, pj_str_t* scheme,
		pj_str_t* username,pj_str_t* realm, pj_str_t* nonce, pj_str_t* uri, pj_str_t* response, pj_str_t* algorithm,
	    pj_str_t* cnonce, pj_str_t* opaque, pj_str_t* qop, pj_str_t* nc, pj_param_list_t *params){

	pjmsrp_header_authorization_t *authorization = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_authorization_t);

	authorization->pool = pool;


	pj_strcreate(pool, &authorization->scheme, scheme);
	pj_strcreate(pool, &authorization->username, username);
	pj_strcreate(pool, &authorization->realm, realm);
	pj_strcreate(pool, &authorization->nonce, nonce);
	pj_strcreate(pool, &authorization->uri, uri);
	pj_strcreate(pool, &authorization->response, response);
	pj_strcreate(pool, &authorization->algorithm, algorithm);
	pj_strcreate(pool, &authorization->cnonce, cnonce);
	pj_strcreate(pool, &authorization->opaque, opaque);
	pj_strcreate(pool, &authorization->qop, qop);
	pj_strcreate(pool, &authorization->nc, nc);

	if (params == NULL){
		pj_list_init(&authorization->params);
	} else {
		authorization->params = params;
		pj_list_init(&authorization->params);
	}

	return authorization;
}


PJ_DEF(pjmsrp_header_authorization_t*) pjmsrp_header_authorization_create_default(pj_pool_t* pool){
	return pjmsrp_header_authorization_create(pool,
			NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
}

PJ_DEF(int) pjmsrp_header_authorization_tostring(const pjmsrp_header_authorization_t* Authorization, pj_str_t* output)
{
    if(Authorization) {
        if(Authorization && Authorization->scheme.ptr) {
            return pj_strappend2_v(Authorization->pool, output, "%s %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
                                       Authorization->scheme.ptr,

                                       Authorization->username.ptr ? "username=\"" : "",
                                       Authorization->username.ptr ? Authorization->username.ptr : "",
                                       Authorization->username.ptr ? "\"" : "",

                                       Authorization->realm.ptr ? ",realm=\"" : "",
                                       Authorization->realm.ptr ? Authorization->realm.ptr : "",
                                       Authorization->realm.ptr ? "\"" : "",

                                       Authorization->nonce.ptr ? ",nonce=\"" : "",
                                       Authorization->nonce.ptr ? Authorization->nonce.ptr : "",
                                       Authorization->nonce.ptr ? "\"" : "",

                                       Authorization->uri.ptr ? ",uri=\"" : "",
                                       Authorization->uri.ptr ? Authorization->uri.ptr : "",
                                       Authorization->uri.ptr ? "\"" : "",

                                       Authorization->response.ptr ? ",response=\"" : "",
                                       Authorization->response.ptr ? Authorization->response.ptr : "",
                                       Authorization->response.ptr ? "\"" : "",

                                       Authorization->algorithm.ptr ? ",algorithm=" : "",
                                       Authorization->algorithm.ptr ? Authorization->algorithm.ptr : "",

                                       Authorization->cnonce.ptr ? ",cnonce=\"" : "",
                                       Authorization->cnonce.ptr ? Authorization->cnonce.ptr : "",
                                       Authorization->cnonce.ptr ? "\"" : "",

                                       Authorization->opaque.ptr ? ",opaque=\"" : "",
                                       Authorization->opaque.ptr ? Authorization->opaque.ptr : "",
                                       Authorization->opaque.ptr ? "\"" : "",

                                       Authorization->qop.ptr ? ",qop=" : "",
                                       Authorization->qop.ptr ? Authorization->qop.ptr : "",

                                       Authorization->nc.ptr ? ",nc=" : "",
                                       Authorization->nc.ptr ? Authorization->nc.ptr : ""
                                      );
        }
    }
    return -1;
}

PJ_DEF(pjmsrp_header_authorization_t*) pjmsrp_header_authorization_parse(pj_pool_t* pool, const char *data, pj_size_t size){
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_authorization_t *hdr_Authorization = pjmsrp_header_authorization_create_default(pool);
	
	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_authorization_first_final);
	(void)(pjmsrp_machine_parser_header_authorization_error);
	(void)(pjmsrp_machine_parser_header_authorization_en_main);

	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < %%{ write first_final; }%% ){
		//do nothing
	}
	
	return hdr_Authorization;
}

PJ_DEF(pjmsrp_header_proxy_authorization_t*) pjmsrp_header_proxy_authorization_parse(pj_pool_t* pool, const char *data, pj_size_t size){
	return pjmsrp_header_authorization_parse(pool, data, size);
}