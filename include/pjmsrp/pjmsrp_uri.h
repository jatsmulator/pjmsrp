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

#ifndef PJMSRP_URI_H_
#define PJMSRP_URI_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_header.h"

PJMSRP_BEGIN_DECLS
//PJ_BEGIN_DECL

#define PJMSRP_URI_IS_SECURE(uri)		((uri) && (strncasecmp(uri->scheme.ptr, "msrps") ? 1 : 0))
#define PJMSRP_URI(self)					((pjmsrp_uri_t*)(self))

/** The type of the authority host.
*/
typedef enum pjmsrp_host_type_e {
	pjmsrp_host_unknown,
	pjmsrp_host_hostname,
	pjmsrp_host_ipv4,
	pjmsrp_host_ipv6
}pjmsrp_host_type_t;


/**
 * @struct	pjmsrp_uri_s
 *
 * @brief	MSRP/MSRPS/TEL URI.
**/
typedef struct pjmsrp_uri_s {
	pj_pool_t* pool;
    pj_str_t scheme;
    struct {
    	pj_str_t userinfo;
        pjmsrp_host_type_t host_type; /**< IPv4 or IPv6 or domain name. */
        pj_str_t host;
        pj_int32_t port;
    } authority;
    pj_str_t session_id;
    pj_str_t transport;

    pj_param_list_t params; /**< list of @ref pj_params_L_t elements containing all parameters. */
}pjmsrp_uri_t;

typedef struct pjmsrp_uris_list_s{
	PJ_DECL_LIST_MEMBER(struct pjmsrp_uris_list_s);
	pjmsrp_uri_t uri;
}pjmsrp_uris_list_t;


//PJMSRP_API pjmsrp_uri_t* pjmsrp_uri_create(const pj_char_t* scheme, const pj_char_t* host,
//		pjmsrp_host_type_t host_type, pj_int32_t port, const pj_char_t* session_id, const pj_char_t* transport);
//
//PJMSRP_API pjmsrp_uri_t* pjmsrp_uri_init(pj_pool_t *pool, const pj_char_t* scheme, const pj_char_t* host,
//		pjmsrp_host_type_t host_type, pj_int32_t port, const pj_char_t* session_id, const pj_char_t* transport);
PJ_DECL(void) 			pjmsrp_uri_init(pjmsrp_uri_t* uri);
PJ_DECL(pjmsrp_uri_t*) 	pjmsrp_uri_create(pj_pool_t *pool);
PJ_DECL(pjmsrp_uri_t*) 	pjmsrp_uri_clone(pj_pool_t *pool, const pjmsrp_uri_t *uri);
PJ_DECL(pj_status_t)	pjmsrp_uri_assign(pj_pool_t *pool, pjmsrp_uri_t *uri, const pjmsrp_uri_t *rhs);
//PJ_DECL(int) 			pjmsrp_uri_tostring(const pjmsrp_uri_t *uri, char *buf, pj_size_t len);
PJ_DECL(void)			pjmsrp_uri_list_clone(pj_pool_t *pool, pjmsrp_uris_list_t *dst_uris,const pjmsrp_uris_list_t *src_uris);
PJ_DECL(void)			pjmsrp_uri_param_clone(pj_pool_t *pool, pj_param_list_t *dst_list, const pj_param_list_t *src_list);
PJ_DECL(void)			pjmsrp_uri_param_shallow_clone(pj_pool_t *pool, pj_param_list_t *dst_list, const pj_param_list_t *src_list);
PJ_DECL(int) 			pjmsrp_uri_serialize(const pjmsrp_uri_t *uri, pj_str_t *output);
PJ_DECL(pj_str_t*) 		pjmsrp_uri_tostring(const pjmsrp_uri_t *uri);

PJMSRP_END_DECLS
///PJ_END_DECL


#endif /* PJMSRP_URI_H_ */
