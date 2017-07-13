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

/**@file pjmsrp_machine_message.rl
 * @brief Ragel file.
 */
#include "pjmsrp/pjmsrp_parser_message.h"

//pjmsrp headers
#include "pjmsrp/pjmsrp_header_to_path.h"
#include "pjmsrp/pjmsrp_header_from_path.h"
#include "pjmsrp/pjmsrp_header_message_id.h"
#include "pjmsrp/pjmsrp_header_byte_range.h"
#include "pjmsrp/pjmsrp_header_success_report.h"
#include "pjmsrp/pjmsrp_header_failure_report.h"
#include "pjmsrp/pjmsrp_header_dummy.h"
#include "pjmsrp/pjmsrp_header_authentication_info.h"
#include "pjmsrp/pjmsrp_header_authorization.h"
#include "pjmsrp/pjmsrp_header_byte_range.h"
#include "pjmsrp/pjmsrp_header_expires.h"
#include "pjmsrp/pjmsrp_header_failure_report.h"
#include "pjmsrp/pjmsrp_header_max_expires.h"
#include "pjmsrp/pjmsrp_header_min_expires.h"
#include "pjmsrp/pjmsrp_header_status.h"
#include "pjmsrp/pjmsrp_header_use_path.h"
#include "pjmsrp/pjmsrp_header_www_authenticate.h"

//#define PJMSRP_MSG_PARSER_ADD_HEADER(pool, name) \
//	if((header = (pjmsrp_header_t*)pjmsrp_header_##name##_parse(pool,tag_start, (p - tag_start)))){ \
//		pjmsrp_message_add_header(pool, msrp_msg, header); \
//	}
	
//#define	PJMSRP_MSG_PARSER_ADD_HEADER(pool, name)\
//	msrp_msg->##name## = pjmsrp_header_##name##_parse(pool,tag_start, (p - tag_start))\
	
static pj_bool_t parse_payload(pj_pool_t* pool, pjmsrp_message_t* msrp_msg, const char* tag_start, const char** p, const char* pe, pj_bool_t* payload_parsed);
static void set_payload(pj_pool_t* pool, pjmsrp_message_t* msrp_msg, const void* ptr, pj_size_t len);


%%{
	machine pjmsrp_machine_message;
	
	###########################################
	#	Includes
	###########################################
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}

	###########################################
	#	Actions
	###########################################
	action parse_Authentication_Info{
		//FIXME: TMSRP_MSG_PARSER_ADD_HEADER(Authentication_Info);
		//TSK_DEBUG_WARN("Authentication_Info Not implemented");
	}
	
	action parse_Authorization{
		//FIXME: TMSRP_MSG_PARSER_ADD_HEADER(Authorization);
		//TSK_DEBUG_WARN("Authorization Not implemented");
	}
	
	action parse_Byte_Range{
		msrp_msg->byte_range = pjmsrp_header_byte_range_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, byte_range);
	}
	
	action parse_Content_Type{
		msrp_msg->content_type = pjmsrp_header_content_type_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, content_type);
	}
	
	action parse_Expires{
		msrp_msg->expires = pjmsrp_header_expires_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, expires);
	}
	
	action parse_Failure_Report{
		msrp_msg->failure_report = pjmsrp_header_failure_report_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, failure_report);
	}
	
	action parse_From_Path{
		msrp_msg->from_path = pjmsrp_header_from_path_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, from_path);
	}
	
	action parse_Max_Expires{
		msrp_msg->max_expires = pjmsrp_header_max_expires_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, max_expires);
	}
	
	action parse_Message_ID{
		msrp_msg->message_id = pjmsrp_header_message_id_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, message_id);
	}
	
	action parse_Min_Expires{
		msrp_msg->min_expires = pjmsrp_header_min_expires_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, min_expires);
	}
	
	action parse_Status{
		msrp_msg->status = pjmsrp_header_status_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, status);
	}
	
	action parse_Success_Report{
		msrp_msg->success_report = pjmsrp_header_success_report_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, success_report);
	}
	
	action parse_To_Path{
		msrp_msg->to_path = pjmsrp_header_to_path_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, to_path);
	}
	
	action parse_Use_Path{
		msrp_msg->use_path = pjmsrp_header_use_path_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, use_path);
	}
	
	action parse_WWW_Authenticate{
		msrp_msg->www_authenticate = pjmsrp_header_www_authenticate_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, www_authenticate);
	}
	
	action parse_Dummy{
		msrp_msg->dummy = pjmsrp_header_dummy_parse(pool,tag_start, (p - tag_start));
		//PJMSRP_MSG_PARSER_ADD_HEADER(pool, dummy);
	}
	
	action parse_tid{
		PJMSRP_PARSER_SET_STRING(pool, msrp_msg->tid);
	}

	action parse_method{
		if(msrp_msg->type == PJMSRP_UNKNOWN){
			msrp_msg->type = PJMSRP_REQUEST;
			PJMSRP_PARSER_SET_STRING(pool, msrp_msg->line.request.method);
			msrp_msg->line.request.type = pjmsrp_request_get_type(&msrp_msg->line.request.method);
		}
		else{
			//cs = %%{ write first_final; }%%;
			cs = pjmsrp_machine_message_error;
			//PJMSRP_DEBUG_ERROR("Message type already defined.");
		}
	}


	action parse_status_code{
		if(msrp_msg->type == PJMSRP_UNKNOWN){
			msrp_msg->type = PJMSRP_RESPONSE;
			PJMSRP_PARSER_SET_INT(pool, msrp_msg->line.response.status);
		}
		else{
			//cs = %%{ write first_final; }%%;
			cs = pjmsrp_machine_message_error;
			//PJMSRP_DEBUG_ERROR("Message type already defined.");
		}
	}
	action parse_comment{
		PJMSRP_PARSER_SET_STRING(pool, msrp_msg->line.response.comment);
	}

	
	action try_parse_data{
		parse_payload(pool, msrp_msg, tag_start, &p, pe, &payload_parsed); // will update "p"
	}

	action parse_data{
		// if the msrp message contain a valid content-type, then gob it otherwise continue until we reach the endline
		int len;
		if(parse_payload(pool, msrp_msg, tag_start, &p, pe, &payload_parsed)){ // will update "p"
			// (This space left deliberately blank)
		}
		else if((len = (int)(p  - tag_start))>0){
			set_payload(pool, msrp_msg, tag_start, (pj_size_t)len);
		}
	}

	action parse_endtid{
		PJMSRP_PARSER_SET_STRING(pool, msrp_msg->end_line.tid);
	}

	action parse_cflag{
		if(tag_start){
			msrp_msg->end_line.cflag = *tag_start;
		}
		else msrp_msg->end_line.cflag = '#';
	}

	action outside_endline{
		*msg_size = (p - (const char*)input) + 1;
	}
	
	action into_endline{
		into_endline = PJ_TRUE;
	}
	action endtid_match{
		( into_endline || (((pe-p) >7/*seven hyphens*/) && (msrp_msg->tid.ptr) && pj_strnicmp2(&msrp_msg->tid, (p+7), msrp_msg->tid.slen) == 0))
	}


	###########################################
	#	Headers
	###########################################

	Authentication_Info = "Authentication-Info:"i SP any* :>CRLF %parse_Authentication_Info;
	Authorization		= "Authorization:"i SP any* :>CRLF %parse_Authorization;
	Byte_Range			= "Byte-Range:"i SP any* :>CRLF %parse_Byte_Range;
	Content_Type		= "Content-Type:"i SP any* :>CRLF %parse_Content_Type;
	Expires				= "Expires:"i SP any* :>CRLF %parse_Expires;
	Failure_Report		= "Failure-Report:"i SP any* :>CRLF %parse_Failure_Report ;
	From_Path			= "From-Path:"i SP any* :>CRLF %parse_From_Path ;
	Max_Expires			= "Max-Expires:"i SP any* :>CRLF %parse_Max_Expires;
	Message_ID			= "Message-ID:"i SP any* :>CRLF %parse_Message_ID;
	Min_Expires			= "Min-Expires:"i SP any* :>CRLF %parse_Min_Expires;
	Status				= "Status:"i SP any* :>CRLF %parse_Status;
	Success_Report		= "Success-Report:"i SP any* :>CRLF %parse_Success_Report;
	To_Path				= "To-Path:"i SP any* :>CRLF %parse_To_Path;
	Use_Path			= "Use-Path:"i SP any* :>CRLF %parse_Use_Path;
	WWW_Authenticate	= "WWW-Authenticate:"i SP any* :>CRLF %parse_WWW_Authenticate;
	
	Dummy				= hname ":" SP hval :>CRLF %parse_Dummy;
	
	header = (Authentication_Info | Authorization | Byte_Range | Content_Type | Expires | Failure_Report | From_Path | Max_Expires | Message_ID | Min_Expires | Status | Success_Report | To_Path | Use_Path | WWW_Authenticate)>tag @10 | (Dummy>tag) @0;

	#headers = To_Path From_Path ( header )*;
	headers = ( header )*;

	###########################################
	#	Utils
	###########################################
	transact_id	= ident;
	method = UPALPHA*;
	status_code	= DIGIT{3};
	comment	= utf8text;
	
	continuation_flag = "+" | "$" | "#";
	end_line = "-------" transact_id>tag %parse_endtid continuation_flag>tag %parse_cflag CRLF;

	Other_Mime_header = Dummy;

	data = any*;

	###########################################
	#	Request
	###########################################
	req_start = "MSRP" SP transact_id>tag %parse_tid SP method>tag %parse_method CRLF;
	#content_stuff = (Other_Mime_header)* CRLF data>tag %parse_data :>CRLF;
	content_stuff = data>tag >try_parse_data %parse_data;
	msrp_request = req_start headers>10 (CRLF content_stuff CRLF)?>5 :>end_line when endtid_match >into_endline;

	###########################################
	#	Response
	###########################################
	resp_start = "MSRP" SP transact_id>tag %parse_tid SP status_code>tag %parse_status_code (SP comment>tag %parse_comment)? CRLF;
	msrp_response = resp_start headers end_line;

	###########################################
	#	Message
	###########################################
	msrp_req_or_resp = (msrp_request | msrp_response)>1 @outside_endline any*>0;

	###########################################
	#	Entry Point
	###########################################
	main := msrp_req_or_resp;
}%%

PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
/* Ragel data */
%% write data;
PJMSRP_RAGEL_DISABLE_WARNINGS_END()

pjmsrp_message_t* pjmsrp_message_parse(pj_pool_t* pool, const void *input, pj_size_t size)
{
    pj_size_t msg_size;
    return pjmsrp_message_parse_2(pool, input, size, &msg_size);
}


pjmsrp_message_t* pjmsrp_message_parse_2(pj_pool_t* pool, const void *input, pj_size_t size, pj_size_t* msg_size)
{
    pjmsrp_message_t* msrp_msg = NULL;
    const char* tag_start = NULL;
    //pjmsrp_header_t* header = NULL;
    pj_bool_t into_endline = PJ_FALSE;
    pj_bool_t payload_parsed = PJ_FALSE;
    
    /* Ragel variables */
    int cs = 0;
    const char* p = input;
    const char* pe = p + size;
    const char* eof = NULL;

    (void)(eof);
    (void)(pjmsrp_machine_message_first_final);
    (void)(pjmsrp_machine_message_error);
    (void)(pjmsrp_machine_message_en_main);

    *msg_size = 0;

    if(!input || !size){
        PJ_LOG(3, (__FILE__, "Null or empty buffer.")); // --> very common case(stream): do not bother us...
        goto bail;
    }

    if(!(msrp_msg = pjmsrp_message_create_default(pool))){
        goto bail;
    }

    PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
    /* Ragel init */
    %% write init;

    /* Ragel execute */
    %% write exec;
    PJMSRP_RAGEL_DISABLE_WARNINGS_END()

    /* Check result */
    if( cs < %%{ write first_final; }%% ){
        PJ_LOG(3, (__FILE__, "Failed to parse MSRP message.")); //--> very common case(stream): do not bother us...
        goto bail;
    }
    
bail:
    return msrp_msg;
}

static pj_bool_t parse_payload(pj_pool_t* pool, pjmsrp_message_t* msrp_msg, const char* tag_start, const char** p, const char* pe, pj_bool_t* payload_parsed)
{
    int64_t payload_len, endline_len;
    pj_bool_t can_parse_payload;

    if(*payload_parsed){
        PJ_LOG(5, (__FILE__, "payload already parsed"));
        return PJ_TRUE;
    }

    if(pe && p && *p && msrp_msg && (can_parse_payload = PJMSRP_HEADER_BYTE_RANGE_IS_VALID(msrp_msg->byte_range))){
        payload_len = (msrp_msg->byte_range->end - msrp_msg->byte_range->start) + 1;
        endline_len = 2/*CRLF*/ + 7/*hyphens*/ + pj_strlen(&msrp_msg->tid) + 2/*CRLF*/ ;
        can_parse_payload = (pe - tag_start) > (payload_len + endline_len);
        if(can_parse_payload){
            set_payload(pool, msrp_msg, tag_start, (pj_size_t)payload_len);
            *p = ((tag_start + payload_len) - 1);
            *payload_parsed = PJ_TRUE;
            return PJ_TRUE;
        }
    }
    return PJ_FALSE;
}

static void set_payload(pj_pool_t* pool, pjmsrp_message_t* msrp_msg, const void* ptr, pj_size_t len)
{
    if(msrp_msg->Content.ptr){
    	pj_size_t oldsize = msrp_msg->Content.slen;
    	pj_size_t newsize = msrp_msg->Content.slen + len;

    	if (oldsize <= 0){
    		msrp_msg->Content.ptr = (char*)pj_pool_alloc(pool, PJMSRP_MAX_STRING_SIZE);
    		msrp_msg->Content.slen = len;
    	} else {
    		//已经分配了最大字符串大小，暂时不分配；
    	}

    	if (newsize >0 && newsize <= len){
    		pj_bzero(&msrp_msg->Content, 0);
    		pj_memcpy((void*)(msrp_msg->Content.ptr + oldsize), ptr, len);
    		msrp_msg->Content.slen = newsize;
    		msrp_msg->Content.ptr[newsize] = '\0';
    	}
    }
    else{
        msrp_msg->Content.ptr = (char*)pj_pool_alloc(pool, len+1); //allocate memory
        msrp_msg->Content.slen = len;
        if (strlen(ptr) <= PJMSRP_MAX_STRING_SIZE) {
        	pj_memcpy(msrp_msg->Content.ptr, ptr, len);
        	msrp_msg->Content.ptr[len] = '\0';
        }
    }
}