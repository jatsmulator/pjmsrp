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

#ifndef PJMSRP_HEADER_H_
#define PJMSRP_HEADER_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_common.h"

PJMSRP_BEGIN_DECLS

struct pjmsrp_header_s;

#define PJMSRP_HEADER(self)					((pjmsrp_header_t*)(self))
#define PJMSRP_HEADER_VALUE_TOSTRING_F(self)	((pjmsrp_header_value_tostring_f)(self))

typedef int (*pjmsrp_header_value_tostring_f)(const struct pjmsrp_header_s* header, pj_str_t* output);
/**
 * @enum	pjmsrp_header_type_e
 *
 * @brief	List of all supported headers.
**/
typedef enum pjmsrp_header_type_e {
    pjmsrp_htype_authentication_info,
    pjmsrp_htype_authorization,
    pjmsrp_htype_byte_range,
    pjmsrp_htype_content_type,
    pjmsrp_htype_dummy,
    pjmsrp_htype_expires,
    pjmsrp_htype_failure_report,
    pjmsrp_htype_from_path,
    pjmsrp_htype_max_expires,
    pjmsrp_htype_message_id,
    pjmsrp_htype_min_expires,
    pjmsrp_htype_status,
    pjmsrp_htype_success_report,
    pjmsrp_htype_to_path,
    pjmsrp_htype_use_path,
    pjmsrp_htype_www_authenticate
} pjmsrp_header_type_t;

typedef enum pjmsrp_header_authenticate_type_s {
	pjmsrp_http_htype_Authorization,
	pjmsrp_http_htype_Proxy_Authorization,
	pjmsrp_http_htype_Proxy_Authenticate,
	pjmsrp_http_htype_WWW_Authenticate

}pjmsrp_header_authenticate_type_e;

typedef struct pjmsrp_header_s {

	pj_pool_t* pool;
	pjmsrp_header_type_t type;
	pjmsrp_header_value_tostring_f tostring;

}pjmsrp_header_t;

#define PJMSRP_DECLARE_HEADER pjmsrp_header_t __header__

typedef struct pjmsrp_headers_list_s
{
	PJ_DECL_LIST_MEMBER(struct pjmsrp_headers_list_s);
	pjmsrp_header_t header;
} pjmsrp_headers_list_t; /**< List of @ref pjmsrp_header_t elements. */


PJ_DECL(const char*) pjmsrp_header_get_name(pjmsrp_header_type_t type);
PJ_DECL(const char*) pjmsrp_header_get_nameex(const pjmsrp_header_t *self);
PJ_DECL(int) pjmsrp_header_serialize(const pjmsrp_header_t *self, pj_str_t *output);
PJ_DECL(char*) pjmsrp_header_tostring(const pjmsrp_header_t *self);


PJMSRP_END_DECLS


#endif /* PJMSRP_HEADER_H_ */
