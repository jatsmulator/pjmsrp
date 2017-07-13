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
#ifndef PJMSRP_PARSER_MESSAGE_H_
#define PJMSRP_PARSER_MESSAGE_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_message.h"
#include "pjmsrp/pjmsrp_ragel_state.h"

PJMSRP_BEGIN_DECLS

PJ_DECL(pjmsrp_message_t*) pjmsrp_message_parse_2(pj_pool_t* pool, const void *input, pj_size_t size, pj_size_t* msg_size);
PJ_DECL(pjmsrp_message_t*) pjmsrp_message_parse(pj_pool_t* pool, const void *input, pj_size_t size);

PJMSRP_END_DECLS

#endif /* PJMSRP_PARSER_MESSAGE_H_ */
