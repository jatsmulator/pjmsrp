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


#include "pjmsrp/pjmsrp_message.h"

PJ_DEF(pjmsrp_message_t*) pjmsrp_message_create_default(pj_pool_t* pool){
	return pjmsrp_message_create(pool, PJMSRP_UNKNOWN, NULL, NULL, 0, NULL);
}

PJ_DEF(pjmsrp_message_t*) pjmsrp_message_create(pj_pool_t* pool, pjmsrp_message_type_t type, const pj_str_t* tid,
		const pj_str_t* method, pj_int16_t status, const pj_str_t* comment){

	pjmsrp_message_t *message;

	if ((message = PJ_POOL_ZALLOC_T(pool, pjmsrp_message_t))){

		message->pool = pool;
		message->type = type;
		if (tid){
			pj_strdup_with_null(pool, &message->tid, tid);
		}

		if(message->type == PJMSRP_RESPONSE) {
			message->line.response.status = status;
			if(comment){
				pj_strdup_with_null(pool, &message->line.response.comment, comment);
			}
		} else {
			if(method){
				pj_strdup_with_null(pool, &message->line.request.method, method);
				message->line.request.type = pjmsrp_request_get_type(method);
			}
		}

	    pj_list_init(&message->headers);

	    if(message->tid.slen > 0 ){
	    	pj_strdup_with_null(pool, &message->end_line.tid, &message->tid);
	    }
	    message->end_line.cflag = '$';

		message->from_path = pjmsrp_header_from_path_create_default(pool);
		message->to_path = pjmsrp_header_to_path_create_default(pool);

	}
    return message;
}

PJ_DEF(pjmsrp_message_t*) pjmsrp_request_create(pj_pool_t* pool, const pj_str_t* tid, const pj_str_t* method){
	return pjmsrp_message_create(pool, PJMSRP_REQUEST, tid, method, 0, NULL);
}

PJ_DEF(pjmsrp_message_t*) pjmsrp_response_create(pj_pool_t* pool, const pj_str_t* tid, pj_int16_t status, const pj_str_t* comment){
	return pjmsrp_message_create(pool, PJMSRP_RESPONSE, tid, NULL, status, comment);
}

PJ_DEF(pjmsrp_request_type_t) pjmsrp_request_get_type(const pj_str_t* method){
    if(method && method->slen > 0) {
        if(pj_stricmp2(method, "SEND") == 0) {
            return PJMSRP_SEND;
        }
        else if(pj_stricmp2(method, "REPORT") == 0) {
            return PJMSRP_REPORT;
        }
        else if(pj_stricmp2(method, "AUTH") == 0) {
            return PJMSRP_AUTH;
        }
    }
    return PJMSRP_NONE;
}

PJ_DEF(int) pjmsrp_message_add_header(pj_pool_t* pool, pjmsrp_message_t *self, const pjmsrp_header_t *hdr)
{
#define ADD_HEADER(type, field) \
		case pjmsrp_htype_##type: \
			{ \
				if(!self->field) \
				{ \
					self->field = (pjmsrp_header_##type##_t*)hdr; \
					return 0; \
				} \
				break; \
			}

    if(self && hdr) {
    	pjmsrp_headers_list_t *headers;
        switch(hdr->type) {
			ADD_HEADER(to_path, to_path);
			ADD_HEADER(from_path, from_path);
			ADD_HEADER(message_id, message_id);
			ADD_HEADER(byte_range, byte_range);
			ADD_HEADER(failure_report, failure_report);
			ADD_HEADER(success_report, success_report);
			ADD_HEADER(status, status);
			ADD_HEADER(content_type, content_type);

        default:
            break;
        }

		headers = (pjmsrp_headers_list_t*) PJ_POOL_ZALLOC_T(self->pool, pjmsrp_headers_list_t);
		headers->header = *hdr;
		pj_list_push_back(&self->headers, headers);

        return 0;
    }
    return -1;
}

PJ_DECL(int) pjmsrp_message_tostring(pjmsrp_message_t *self, pj_str_t* output)
{
	if(!self){
		return -1;
	}
	pjmsrp_start_line_tostring(self, output);
	pjmsrp_header_tostring2(self, output);
	pjmsrp_content_tostring(self, output);
	pjmsrp_end_line_tostring(self, output);
	return 0;
}

PJ_DECL(int) pjmsrp_start_line_tostring(pjmsrp_message_t *self, pj_str_t* output)
{
	if(PJMSRP_MESSAGE_IS_REQUEST(self)){
		pj_strappend2_v(self->pool, output, "MSRP %s %s\r\n", self->tid.ptr, self->line.request.method.ptr);
	}
	else if(PJMSRP_MESSAGE_IS_RESPONSE(self)){
		pj_strappend2_v(self->pool, output, "MSRP %s %u %s\r\n", self->tid.ptr, self->line.response.status, self->line.response.comment.ptr);
	}

	return -1;
}

PJ_DECL(int) pjmsrp_end_line_tostring(pjmsrp_message_t *self, pj_str_t* output)
{
	if(self){
		pj_strappend2_v(self->pool, output, "-------%s%c\r\n", self->tid.ptr, self->end_line.cflag);
	}
	return -1;
}

PJ_DECL(int) pjmsrp_content_tostring(pjmsrp_message_t *self, pj_str_t* output)
{
	int ret = 0;
	
	if(PJMSRP_MESSAGE_HAS_CONTENT(self)){
		/* CRLF*/
		ret = pj_strappend2(self->pool, output, "\r\n", 2);
		
		/* Value */
		ret = pj_strappend(self->pool, output, &self->Content);
		
		/* CRLF*/
		ret = pj_strappend2(self->pool, output, "\r\n", 2);
	}
	return -1;
}

PJ_DECL(int) pjmsrp_header_tostring2(const pjmsrp_message_t* self, pj_str_t *output)
{
	if(!self){
		return -1;
	}
	
	if(self->to_path){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_to_path));
		pjmsrp_header_to_path_tostring(self->to_path, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->from_path){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_from_path));
		pjmsrp_header_from_path_tostring(self->from_path, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->message_id){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_message_id));
		pjmsrp_header_message_id_tostring(self->message_id, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->byte_range){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_byte_range));
		pjmsrp_header_byte_range_tostring(self->byte_range, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->failure_report){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_failure_report));
		pjmsrp_header_failure_report_tostring(self->failure_report, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->success_report){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_success_report));
		pjmsrp_header_success_report_tostring(self->success_report, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->status){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_status));
		pjmsrp_header_status_tostring(self->status, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->expires){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_expires));
		pjmsrp_header_expires_tostring(self->expires, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->max_expires){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_max_expires));
		pjmsrp_header_max_expires_tostring(self->max_expires, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->min_expires){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_min_expires));
		pjmsrp_header_min_expires_tostring(self->min_expires, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->use_path){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_use_path));
		pjmsrp_header_use_path_tostring(self->use_path, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->www_authenticate){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_www_authenticate));
		pjmsrp_header_www_authenticate_tostring(self->www_authenticate, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->content_type){
		pj_strappend2_v(self->pool, output, "%s: ", pjmsrp_header_get_name(pjmsrp_htype_content_type));
		pjmsrp_header_content_type_tostring(self->content_type, output);
		pj_strappend2(self->pool, output, "\r\n", 2);
	}
	if(self->dummy){
		pj_strappend2_v(self->pool, output, "%s: %s\r\n", self->dummy->name.ptr, self->dummy->value.ptr);
	}
	return 0;
}

