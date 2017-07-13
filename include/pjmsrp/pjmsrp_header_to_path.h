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

#ifndef PJMSRP_HEADER_TO_PATH_H_
#define PJMSRP_HEADER_TO_PATH_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_header.h"
#include "pjmsrp/pjmsrp_parser_uri.h"

PJMSRP_BEGIN_DECLS

/// @struct
///
/// @brief	MSRP 'To-Path' header.
///
/// @par ABNF :  "To-Path:" SP MSRP-URI  *( SP MSRP-URI )
///
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct pjmsrp_header_to_path_s {
	pj_pool_t* pool;
    pjmsrp_uri_t *uri;
    pjmsrp_uris_list_t otherURIs;
}pjmsrp_header_to_path_t;

PJ_DECL(void) pjmsrp_header_to_path_init(pjmsrp_header_to_path_t* uri);
PJ_DECL(pj_status_t) pjmsrp_header_to_path_assign(pj_pool_t *pool, pjmsrp_header_to_path_t *newFromPath, const pjmsrp_header_to_path_t *rhs);
PJ_DECL(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_create_default(pj_pool_t *pool);
PJ_DECL(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_create(pj_pool_t *pool,const pjmsrp_uri_t* uri, const pjmsrp_uris_list_t* otherURIs);
PJ_DECL(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_clone(pj_pool_t *pool, const pjmsrp_header_to_path_t *uri);
PJ_DECL(pjmsrp_header_to_path_t*)	pjmsrp_header_to_path_parse(pj_pool_t *pool, const char *data, pj_size_t size);
PJ_DECL(int) pjmsrp_header_to_path_tostring(const pjmsrp_header_to_path_t* to_path, pj_str_t* output);

PJMSRP_END_DECLS

#endif /* PJMSRP_HEADER_TO_PATH_H_ */
