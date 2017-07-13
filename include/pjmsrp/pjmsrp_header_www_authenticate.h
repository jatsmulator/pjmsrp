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
#ifndef PJMSRP_HEADER_WWW_AUTHENTICATE_H_
#define PJMSRP_HEADER_WWW_AUTHENTICATE_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_header.h"
#include "pjmsrp/pjmsrp_ragel_state.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @struct
///
/// @brief	MSRP header 'WWW-Authenticate'.
///
/// @par ABNF = WWW-Authenticate	= 	"WWW-Authenticate" HCOLON challenge
///				challenge	= 	("Digest" LWS digest-cln *(COMMA digest-cln)) / other-challenge
///				other-challenge	= 	auth-scheme / auth-param *(COMMA auth-param)
///				digest-cln	= 	realm / domain / nonce / opaque / stale / algorithm / qop-options / auth-param
///				realm	= 	"realm" EQUAL realm-value
///				realm-value	= 	quoted-string
///				domain	= 	"domain" EQUAL LDQUOT URI *( 1*SP URI ) RDQUOT
///				URI	= 	absoluteURI / abs-path
///				opaque	= 	"opaque" EQUAL quoted-string
///				stale	= 	"stale" EQUAL ( "true" / "false" )
///				qop-options	= 	"qop" EQUAL LDQUOT qop-value *("," qop-value) RDQUOT
///				qop-value	= 	"auth" / "auth-int" / token
///
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct pjmsrp_header_www_authenticate_s {

	pj_pool_t* pool;
	pjmsrp_header_authenticate_type_e type;
    pj_str_t scheme;
    pj_str_t realm;
    pj_str_t domain;
    pj_str_t nonce;
    pj_str_t opaque;
    unsigned stale:1;
    pj_str_t algorithm;
    pj_str_t qop;

    pj_param_list_t* params;
}pjmsrp_header_www_authenticate_t;

typedef pjmsrp_header_www_authenticate_t pjmsrp_header_proxy_authenticate_t;

PJ_DECL(pjmsrp_header_www_authenticate_t*) pjmsrp_header_www_authenticate_create(pj_pool_t* pool);
PJ_DECL(pjmsrp_header_www_authenticate_t*) pjmsrp_header_www_authenticate_parse(pj_pool_t* pool, const char *data, pj_size_t size);
PJ_DECL(pjmsrp_header_proxy_authenticate_t*) pjmsrp_header_proxy_authenticate_parse(pj_pool_t* pool, const char *data, pj_size_t size);
PJ_DECL(int) pjmsrp_header_www_authenticate_tostring(const pjmsrp_header_www_authenticate_t* www_authenticate, pj_str_t* output);
#endif /* PJMSRP_HEADER_WWW_AUTHENTICATE_H_ */
