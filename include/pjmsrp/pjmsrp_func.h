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

#ifndef PJMSRP_FUNC_H_
#define PJMSRP_FUNC_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_message.h"

PJMSRP_BEGIN_DECLS

PJ_DECL(pjmsrp_request_t*) pjmsrp_create_bodiless(pj_pool_t* pool, const pjmsrp_uri_t* To, const pjmsrp_uri_t* From);
PJ_DECL(pjmsrp_response_t*) pjmsrp_create_response(pj_pool_t* pool, const pjmsrp_request_t* request, short status, const char* comment);
PJ_DECL(pjmsrp_request_t*) pjmsrp_create_report(pj_pool_t* pool, const pjmsrp_request_t* SEND, short status, const char* reason);
PJ_DECL(pj_bool_t) pjmsrp_isReportRequired(pj_pool_t* pool, const pjmsrp_request_t* request, pj_bool_t failed);

PJMSRP_END_DECLS

#endif /* PJMSRP_FUNC_H_ */
