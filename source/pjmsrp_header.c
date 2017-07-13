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

#include "pjmsrp/pjmsrp_header.h"
#include "pjmsrp/pjmsrp_header_dummy.h"

PJ_DEF(const char*) pjmsrp_header_get_name(pjmsrp_header_type_t type)
{
    switch(type) {
    case pjmsrp_htype_authentication_info:
        return "Authentication-Info";
    case pjmsrp_htype_authorization:
        return "Authorization";
    case pjmsrp_htype_byte_range:
        return "Byte-Range";
    case pjmsrp_htype_content_type:
        return "Content-Type";
    case pjmsrp_htype_expires:
        return "Expires";
    case pjmsrp_htype_failure_report:
        return "Failure-Report";
    case pjmsrp_htype_from_path:
        return "From-Path";
    case pjmsrp_htype_max_expires:
        return "Max-Expires";
    case pjmsrp_htype_message_id:
        return "Message-ID";
    case pjmsrp_htype_min_expires:
        return "Min-Expires";
    case pjmsrp_htype_status:
        return "Status";
    case pjmsrp_htype_success_report:
        return "Success-Report";
    case pjmsrp_htype_to_path:
        return "To-Path";
    case pjmsrp_htype_use_path:
        return "Use-Path";
    case pjmsrp_htype_www_authenticate:
        return "WWW-Authenticate";

    default:
        return "unknown-header";
    }
}

PJ_DEF(const char*) pjmsrp_header_get_nameex(const pjmsrp_header_t *self)
{
    if(self) {
        if(self->type == pjmsrp_htype_dummy) {
            return ((pjmsrp_header_dummy_t*)(self))->name.ptr;
        }
        else {
            return pjmsrp_header_get_name(self->type);
        }
    }
    return "unknown-header";
}

PJ_DEF(int) pjmsrp_header_serialize(const pjmsrp_header_t *self, pj_str_t *output)
{
    int ret = -1;
    if(!self || !output) {
        return -1;
    }

    /* Name */
    pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_nameex(self));

    /* Value */
    if((ret = self->tostring(self, output))) {
        // Abort?
    }

    /* CRLF*/
    ret = pj_strappend2(self->pool, output, "\r\n", 2);

    return ret;
}

PJ_DEF(char*) pjmsrp_header_tostring(const pjmsrp_header_t *self)
{
    char* ret = NULL;
    pj_str_t* buffer;
    if(self && self->tostring) {
        if((buffer = pj_strcreate_null(self->pool))) {
            self->tostring(self, buffer);
            strncpy(ret, buffer->ptr, buffer->slen);
        }
    }
    return ret;
}


