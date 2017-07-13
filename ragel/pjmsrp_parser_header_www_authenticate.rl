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
 
/**@file pjmsrp_parser_header_www_authenticate.rl
 * @brief MSRP "WWW-Authenticate" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */

#include "pjmsrp/pjmsrp_header_www_authenticate.h"
 
 
 // Check if we have ",CRLF" ==> See WWW-Authenticate header
// As :>CRLF is preceded by any+ ==> p will be at least (start + 1)
// p point to CR
#define prev_not_comma(p) !(p && p[-1] == ',')

/***********************************
*	Ragel state machine.
*/
%%{
	machine pjmsrp_machine_parser_header_www_authenticate;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}
	
	action is_digest{
		pj_strdup2_with_null(pool, &hdr_WWW_Authenticate->scheme, "Digest");
	}

	action is_basic{
		pj_strdup2_with_null(pool, &hdr_WWW_Authenticate->scheme, "Basic");
	}

	action is_auth{
		hdr_WWW_Authenticate->type = pjmsrp_http_htype_WWW_Authenticate;
	}

	action is_proxy{
		hdr_WWW_Authenticate->type = pjmsrp_http_htype_Proxy_Authenticate;
	}

	action parse_realm{
		PJMSRP_PARSER_SET_STRING(pool, hdr_WWW_Authenticate->realm);
		pj_strunquote(&hdr_WWW_Authenticate->realm);
	}

	action parse_domain{
		PJMSRP_PARSER_SET_STRING(pool, hdr_WWW_Authenticate->domain);
		//pj_strunquote(&hdr_WWW_Authenticate->domain);
	}

	action parse_nonce{
		PJMSRP_PARSER_SET_STRING(pool, hdr_WWW_Authenticate->nonce);
		pj_strunquote(&hdr_WWW_Authenticate->nonce);
	}

	action parse_opaque{
		PJMSRP_PARSER_SET_STRING(pool, hdr_WWW_Authenticate->opaque);
		pj_strunquote(&hdr_WWW_Authenticate->opaque);
	}

	action parse_stale{
		hdr_WWW_Authenticate->stale = strnicmp(tag_start, "true", 4);
	}

	action parse_algorithm{
		PJMSRP_PARSER_SET_STRING(pool, hdr_WWW_Authenticate->algorithm);
	}

	action parse_qop{
		PJMSRP_PARSER_SET_STRING(pool, hdr_WWW_Authenticate->qop);
		//pj_strunquote(&hdr_WWW_Authenticate->qop);
	}

	action parse_param{
		PJMSRP_PARSER_ADD_PARAM(pool, hdr_WWW_Authenticate->params);
	}

	action prev_not_comma{
		prev_not_comma(p)
	}

	action eob{
	}

	#FIXME: Only Digest (MD5, AKAv1-MD5 and AKAv2-MD5) is supported
	other_challenge = (any+);
	auth_param = generic_param>tag %parse_param;

	realm = "realm"i EQUAL quoted_string>tag %parse_realm;
	domain = "domain"i EQUAL LDQUOT <: (any*)>tag %parse_domain :> RDQUOT;
	nonce = "nonce"i EQUAL quoted_string>tag %parse_nonce;
	opaque = "opaque"i EQUAL quoted_string>tag %parse_opaque;
	stale = "stale"i EQUAL ( "true"i | "false"i )>tag %parse_stale;
	algorithm = "algorithm"i EQUAL <:token>tag %parse_algorithm;
	qop_options = "qop"i EQUAL LDQUOT <: (any*)>tag %parse_qop :> RDQUOT;
	
	digest_cln = (realm | domain | nonce | opaque | stale | algorithm | qop_options)@1 | auth_param@0;
	challenge = ( ("Digest"i%is_digest | "Basic"i%is_basic) LWS digest_cln ( (COMMA | CRLF) <:digest_cln )* ) | other_challenge;
	WWW_Authenticate = ("WWW-Authenticate"i>is_auth | "Proxy-Authenticate"i>is_proxy) HCOLON challenge;

	# Entry point
	main := WWW_Authenticate CRLF @eob;

}%%

PJ_DEF(pjmsrp_header_www_authenticate_t*) pjmsrp_header_www_authenticate_create(pj_pool_t* pool)
{
	pjmsrp_header_www_authenticate_t *www_authenticate = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_www_authenticate_t);

	www_authenticate->pool = pool;
	pj_bzero(&www_authenticate->scheme, 0);
	pj_bzero(&www_authenticate->realm, 0);
	pj_bzero(&www_authenticate->domain, 0);
	pj_bzero(&www_authenticate->nonce, 0);
	pj_bzero(&www_authenticate->algorithm, 0);
	pj_bzero(&www_authenticate->qop, 0);
	
	pj_list_init(&www_authenticate->params);
	
	return www_authenticate;	
}

PJ_DEF(int) pjmsrp_header_www_authenticate_tostring(const pjmsrp_header_www_authenticate_t* www_authenticate, pj_str_t* output)
{
    if(www_authenticate) {
        if(www_authenticate && www_authenticate->scheme.ptr) {
            return pj_strappend2_v(www_authenticate->pool, output, "%s realm=\"%s\"%s%s%s%s%s%s%s%s%s%s%s%s,stale=%s%s%s",
                                       www_authenticate->scheme.ptr,
                                       www_authenticate->realm.ptr ? www_authenticate->realm.ptr : "",

                                       www_authenticate->domain.ptr ? ",domain=\"" : "",
                                       www_authenticate->domain.ptr ? www_authenticate->domain.ptr : "",
                                       www_authenticate->domain.ptr ? "\"" : "",


                                       www_authenticate->qop.ptr ? ",qop=\"" : "",
                                       www_authenticate->qop.ptr ? www_authenticate->qop.ptr : "",
                                       www_authenticate->qop.ptr ? "\"" : "",


                                       www_authenticate->nonce.ptr ? ",nonce=\"" : "",
                                       www_authenticate->nonce.ptr ? www_authenticate->nonce.ptr : "",
                                       www_authenticate->nonce.ptr ? "\"" : "",

                                       www_authenticate->opaque.ptr ? ",opaque=\"" : "",
                                       www_authenticate->opaque.ptr ? www_authenticate->opaque.ptr : "",
                                       www_authenticate->opaque.ptr ? "\"" : "",

                                       www_authenticate->stale ? "TRUE" : "FALSE",

                                       www_authenticate->algorithm.ptr ? ",algorithm=" : "",
                                       www_authenticate->algorithm.ptr ? www_authenticate->algorithm.ptr : ""
                                      );
        }
    }
    return -1;
}

PJ_DEF(pjmsrp_header_www_authenticate_t*) pjmsrp_header_www_authenticate_parse(pj_pool_t* pool, const char *data, pj_size_t size){

	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_www_authenticate_t *hdr_WWW_Authenticate = pjmsrp_header_www_authenticate_create(pool);
	
	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_www_authenticate_first_final);
	(void)(pjmsrp_machine_parser_header_www_authenticate_error);
	(void)(pjmsrp_machine_parser_header_www_authenticate_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < %%{ write first_final; }%% ){
		//PJ_LOG(3, (__FILE__, "Failed to parse WWW-Authenticate header."));
	}
	
	return hdr_WWW_Authenticate;
}

PJ_DEF(pjmsrp_header_proxy_authenticate_t*) pjmsrp_header_proxy_authenticate_parse(pj_pool_t* pool, const char *data, pj_size_t size){
	return pjmsrp_header_www_authenticate_parse(pool, data, size);
}

 