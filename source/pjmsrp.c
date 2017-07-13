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

#include "pjmsrp.h"

#define PJMSRP_DEFAULT_NAMESPACE	0 // "000"

PJ_DEF(pjmsrp_request_t*) pjmsrp_create_bodiless(pj_pool_t* pool, const pjmsrp_uri_t* To, const pjmsrp_uri_t* From){
    /* RFC 4975 - 7.1. Constructing Requests
    	Requests with no bodies are useful when a client wishes to send
    	"traffic", but does not wish to send content to be rendered to the
    	peer user.  For example, the active endpoint sends a SEND request
    	immediately upon establishing a connection.  If it has nothing to
    	say at the moment, it can send a request with no body.  Bodiless
    	requests may also be used in certain applications to keep Network
    	Address Translation (NAT) bindings alive, etc.

    	Bodiless requests are distinct from requests with empty bodies.  A
    	request with an empty body will have a Content-Type header field
    	value and will generally be rendered to the recipient according to
    	the rules for that type.
    */

    pjmsrp_request_t* BODILESS = NULL;
    pj_str_t tid;
    pj_str_t mid;
    pj_str_t send = {"SEND", 4};
    pj_strrandom(pool, &tid);
    pj_strrandom(pool, &mid);

    if(!(BODILESS = pjmsrp_request_create(pool, &tid, &send))) {
        goto bail;
    }

    if (To){
    	BODILESS->to_path->uri = pjmsrp_uri_clone(pool, To);
    }

    if (From){
    	BODILESS->from_path->uri = pjmsrp_uri_clone(pool, From);
    }

    if (!BODILESS->message_id){

    	//Construct with mid instance
    	BODILESS->message_id = pjmsrp_header_message_id_create(pool, &mid);
    } else {
        pj_strdup_with_null(pool, &BODILESS->message_id->value, &mid);
    }


bail:
    return BODILESS;
}

PJ_DECL(pjmsrp_response_t*) pjmsrp_create_response(pj_pool_t* pool, const pjmsrp_request_t* request, short status, const char* comment){
	pjmsrp_response_t* response = NULL;
	pj_str_t pjComment = { NULL, 0 };

    if(!request) {
        goto bail;
    }

	if (comment){
		pjComment.ptr = pj_pool_alloc(pool, strlen(comment));
		pj_strdup2_with_null(pool, &pjComment, comment);
	}

    /* MSRP response will have the same tid ==> nothing to do */
    if(!(response = pjmsrp_response_create(pool, &request->tid, status, &pjComment))) {
        goto bail;
    }
    /* reverse To-Path and From-Path */
    response->to_path   = (pjmsrp_header_to_path_t*)pjmsrp_header_from_path_clone(pool, request->from_path);
    response->from_path = (pjmsrp_header_from_path_t*)pjmsrp_header_to_path_clone(pool, request->to_path);

    /* Byte-Range */
    response->byte_range = request->byte_range;

bail:
    return response;
}

PJ_DECL(pjmsrp_request_t*) pjmsrp_create_report(pj_pool_t* pool, const pjmsrp_request_t* SEND, short status, const char* reason){
    /*	RFC 4975 - 7.1.2. Sending REPORT Requests

    * REPORT requests are similar to SEND requests, except that report
    * requests MUST NOT include Success-Report or Failure-Report header
    * fields, and MUST contain a Status header field.  REPORT requests MUST
    * contain the Message-ID header field from the original SEND request.
    */
    pjmsrp_request_t* REPORT = NULL;
    pj_str_t tid;
    pj_str_t method = {"REPORT", 6};
    /*	If an MSRP element receives a REPORT for a Message-ID it does not
    	recognize, it SHOULD silently ignore the REPORT.
    */
    if(!SEND || !SEND->message_id) {
        goto bail;
    }

    /*  Generate new tid (Report has it's own tid) */
    pj_strrandom(pool, &tid);

    /* MSRP response will have the same tid ==> nothing to do */
    if(!(REPORT = pjmsrp_request_create(pool, &tid, &method))) {
        goto bail;
    }

    /* reverse To-Path and From-Path */
    REPORT->to_path = (pjmsrp_header_to_path_t*)pjmsrp_header_from_path_clone(pool, SEND->from_path);
    REPORT->from_path = (pjmsrp_header_from_path_t*)pjmsrp_header_to_path_clone(pool, SEND->to_path);
    /* Byte-Range */
    REPORT->byte_range = SEND->byte_range;

    /* Message ID */
    pj_strdup_with_null(pool, &REPORT->message_id->value, &SEND->message_id->value);

    /* Status */
    REPORT->status->_namespace = PJMSRP_DEFAULT_NAMESPACE;
    REPORT->status->code = SEND->status->code;
    pj_strdup_with_null(pool, &REPORT->status->reason, &SEND->status->reason);

bail:
    return REPORT;
}

PJ_DECL(pj_bool_t) pjmsrp_isReportRequired(pj_pool_t* pool, const pjmsrp_request_t* request, pj_bool_t failed){

    if(!request) {
        return PJ_FALSE;
    }

    /* Success Report. */
    if(request->success_report && request->success_report->yes) {
        return PJ_TRUE;
    }

    /* Failure Report */
    if(!request->failure_report || (request->failure_report && request->failure_report->type != freport_no)) {
        return failed;
    }

	return PJ_FALSE;
}

