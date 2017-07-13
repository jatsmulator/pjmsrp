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
#ifndef PJMSRP_HEADER_DUMMY_H_
#define PJMSRP_HEADER_DUMMY_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_header.h"
#include "pjmsrp/pjmsrp_ragel_state.h"

PJMSRP_BEGIN_DECLS

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @struct
///
/// @brief	MSRP Dummy header.
///
/// @par ABNF :  hname  ":" SP hval CRLF
///
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct pjmsrp_header_dummy_s {
	pj_pool_t* pool;
    pj_str_t name;
    pj_str_t value;
}pjmsrp_header_dummy_t;

PJ_DECL(pjmsrp_header_dummy_t*) pjmsrp_header_dummy_create_default(pj_pool_t *pool);
PJ_DECL(pjmsrp_header_dummy_t*) pjmsrp_header_dummy_create(pj_pool_t *pool, pj_str_t* name, pj_str_t* value);
PJ_DECL(pjmsrp_header_dummy_t*) pjmsrp_header_dummy_parse(pj_pool_t* pool, const char *data, pj_size_t size);
PJ_DECL(int) pjmsrp_header_dummy_tostring(const pjmsrp_header_dummy_t* dummy, pj_str_t* output);

PJMSRP_END_DECLS



#endif /* PJMSRP_HEADER_DUMMY_H_ */
