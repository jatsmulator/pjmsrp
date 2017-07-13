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
#ifndef PJMSRP_HEADER_AUTHORIZATION_H_
#define PJMSRP_HEADER_AUTHORIZATION_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_header.h"
#include "pjmsrp/pjmsrp_ragel_state.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @struct
///
/// @brief	MSRP header 'Authorization' as per RFC 3261 subclause .
///
/// @par ABNF = Authorization	= 	"Authorization" HCOLON credentials
/// 								credentials	= 	("Digest" LWS digest-response) / other-response
/// 								digest-response	= 	dig-resp *(COMMA dig-resp)
/// 								dig-resp	= 	username / realm / nonce / digest-uri / dresponse / algorithm / cnonce / opaque / message-qop / nonce-count / auth-param / auts
/// 								username	= 	"username" EQUAL username-value
/// 								username-value	= 	quoted-string
/// 								digest-uri	= 	"uri" EQUAL LDQUOT digest-uri-value RDQUOT
/// 								digest-uri-value	= 	auth-request-uri ; equal to request-uri as specified by HTTP/1.1
/// 								message-qop	= 	"qop" EQUAL qop-value
/// 								cnonce	= 	"cnonce" EQUAL cnonce-value
/// 								cnonce-value	= 	nonce-value
/// 								nonce-count	= 	"nc" EQUAL nc-value
/// 								nc-value	= 	8LHEX
/// 								dresponse	= 	"response" EQUAL request-digest
/// 								request-digest	= 	LDQUOT 32LHEX RDQUOT
/// 								auth-request-uri = not-defined
///
/// 								auth-param	= 	auth-param-name EQUAL ( token / quoted-string )
/// 								auth-param-name	= 	token
///
/// 								other-response	= 	auth-scheme LWS auth-param *(COMMA auth-param)
/// 								auth-scheme	= 	token
/// 								auts	= 	"auts" EQUAL auts-param
/// 								auts-param	= 	LDQUOT auts-value RDQUOT
/// 								auts-value	= 	<base64 encoding of AUTS>
///
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct pjmsrp_header_Authorization_s {

	pj_pool_t* pool;
	pjmsrp_header_authenticate_type_e type;
    pj_str_t scheme;
    pj_str_t username;
    pj_str_t realm;
    pj_str_t nonce;
    pj_str_t uri;
    pj_str_t response;
    pj_str_t algorithm;
    pj_str_t cnonce;
    pj_str_t opaque;
    pj_str_t qop;
    pj_str_t nc;

    pj_param_list_t *params;
}pjmsrp_header_authorization_t;

typedef pjmsrp_header_authorization_t pjmsrp_header_proxy_authorization_t;

PJ_DECL(pjmsrp_header_authorization_t*) pjmsrp_header_authorization_create(pj_pool_t* pool, pj_str_t* scheme,
		pj_str_t* username,pj_str_t* realm, pj_str_t* nonce, pj_str_t* uri, pj_str_t* response, pj_str_t* algorithm,
	    pj_str_t* cnonce, pj_str_t* opaque, pj_str_t* qop, pj_str_t* nc, pj_param_list_t *params);

PJ_DECL(pjmsrp_header_authorization_t*) pjmsrp_header_authorization_create_default(pj_pool_t* pool);
PJ_DECL(pjmsrp_header_authorization_t*) pjmsrp_header_authorization_parse(pj_pool_t* pool, const char *data, pj_size_t size);
PJ_DECL(pjmsrp_header_proxy_authorization_t*) pjmsrp_header_proxy_authorization_parse(pj_pool_t* pool, const char *data, pj_size_t size);
PJ_DECL(int) pjmsrp_header_authorization_tostring(const pjmsrp_header_authorization_t* Authorization, pj_str_t* output);


#endif /* PJMSRP_HEADER_AUTHORIZATION_H_ */
