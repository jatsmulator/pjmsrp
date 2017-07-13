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

#ifndef PJMSRP_MESSAGE_H_
#define PJMSRP_MESSAGE_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_header.h"
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
#include "pjmsrp/pjmsrp_header_content_type.h"

PJMSRP_BEGIN_DECLS

#define PJMSRP_MESSAGE_IS_REQUEST(self) ((self) ? (self)->type == PJMSRP_REQUEST : PJ_FALSE)
#define PJMSRP_MESSAGE_IS_RESPONSE(self) ((self) ? (self)->type == PJMSRP_RESPONSE : PJ_FALSE)

#define PJMSRP_MESSAGE(self)				((pjmsrp_message_t*)(self))
#define PJMSRP_MESSAGE_AS_RESPONSE(self)	((pjmsrp_response_t*)(self))
#define PJMSRP_MESSAGE_AS_REQUEST(self)		((pjmsrp_request_t*)(self))


#define PJMSRP_RESPONSE_CODE(self)			 (PJMSRP_MESSAGE_IS_RESPONSE((self)) ? (self)->line.response.status : 0)
#define PJMSRP_RESPONSE_PHRASE(self)		 (PJMSRP_MESSAGE_IS_RESPONSE((self)) ? (self)->line.response.comment.ptr : NULL)

#define PJMSRP_REQUEST_METHOD(self)			 (PJMSRP_MESSAGE_IS_REQUEST((self)) ? (self)->line.request.method.ptr : NULL)
#define PJMSRP_REQUEST_IS_SEND(self)		 (PJMSRP_MESSAGE_IS_REQUEST(self) && (self)->line.request.type == PJMSRP_SEND)
#define PJMSRP_REQUEST_IS_REPORT(self)		 (PJMSRP_MESSAGE_IS_REQUEST(self) && (self)->line.request.type == PJMSRP_REPORT)
#define PJMSRP_REQUEST_IS_AUTH(self)		 (PJMSRP_MESSAGE_IS_REQUEST(self) && (self)->line.request.type == PJMSRP_AUTH)

#define PJMSRP_MESSAGE_HAS_CONTENT(message)	 ((message) && (message)->Content.ptr && (0 != (message)->Content.slen))
#define PJMSRP_MESSAGE_CONTENT(message)		 (PJMSRP_MESSAGE_HAS_CONTENT(message) ? (message)->Content.ptr : 0)

#define PJMSRP_RESPONSE_IS(self, code)		(PJMSRP_RESPONSE_CODE((self)) == code)
#define PJMSRP_RESPONSE_IS_NXX(self, N)		(PJMSRP_MESSAGE_IS_RESPONSE((self)) && N##00<= PJMSRP_RESPONSE_CODE((self)) && PJMSRP_RESPONSE_CODE((self)) <= N##99)
#define PJMSRP_RESPONSE_IS_1XX(self)		PJMSRP_RESPONSE_IS_NXX(self, 1)
#define PJMSRP_RESPONSE_IS_2XX(self)		PJMSRP_RESPONSE_IS_NXX(self, 2)
#define PJMSRP_RESPONSE_IS_3XX(self)		PJMSRP_RESPONSE_IS_NXX(self, 3)
#define PJMSRP_RESPONSE_IS_4XX(self)		PJMSRP_RESPONSE_IS_NXX(self, 4)
#define PJMSRP_RESPONSE_IS_5XX(self)		PJMSRP_RESPONSE_IS_NXX(self, 5)
#define PJMSRP_RESPONSE_IS_6XX(self)		PJMSRP_RESPONSE_IS_NXX(self, 6)
#define PJMSRP_RESPONSE_IS_23456(self)		(PJMSRP_MESSAGE_IS_RESPONSE((self)) && 200<= PJMSRP_RESPONSE_CODE((self)) && PJMSRP_RESPONSE_CODE((self)) <= 699)
#define PJMSRP_RESPONSE_IS_3456(self)		(PJMSRP_MESSAGE_IS_RESPONSE((self)) && 300<= PJMSRP_RESPONSE_CODE((self)) && PJMSRP_RESPONSE_CODE((self)) <= 699)

/**	Defines the message type (Request or Response).
**/
typedef enum pjmsrp_message_type_e {
	PJMSRP_UNKNOWN,
	PJMSRP_REQUEST,
    PJMSRP_RESPONSE,
}pjmsrp_message_type_t;

/**
 * define two request types
 */
typedef enum pjmsrp_request_type_e {
    PJMSRP_NONE = 0,

    PJMSRP_SEND,  /**< deliver a complete message or a chunk */
    PJMSRP_REPORT,/**< report on the status of a previously sent message, or a range of bytes inside a message */
    PJMSRP_AUTH
    //...
}pjmsrp_request_type_t;


typedef struct pjmsrp_message_s {

	/**< Request line , eg: MSRP a786hjs2 SEND or MSRP a786hjs2 200 OK */
	pj_pool_t* pool;
	pjmsrp_message_type_t type;		/**< message type */
	pj_str_t tid;					/**< transaction identifier eg: a786hjs2 **/
	union {
		struct {
			pj_str_t method;  	    /**< the value of request type, eg: SEND */
			pjmsrp_request_type_t type;
		} request;

		struct {
			short status;  	/**< status code, eg: 200 */
			pj_str_t comment; 	/**< comment for status , eg: OK or FAILURE */
		} response;
	} line;

    // Very common headers
    pjmsrp_header_to_path_t* to_path; 			/**<  To-Path: msrp://192.168.1.206:53542/2aaf0dcd2694;tcp  */
    pjmsrp_header_from_path_t* from_path;		/**<  From-Path: msrp://192.168.1.76:40000/1470087498348;tcp */
    pjmsrp_header_message_id_t* message_id; 		/**< Message-ID: 1469695661674 **/
    pjmsrp_header_byte_range_t* byte_range;		/**< Byte-Range: 1-6924/6924 **/
    pjmsrp_header_failure_report_t* failure_report;
    pjmsrp_header_success_report_t* success_report;	/**< Success-Report: no **/
    pjmsrp_header_status_t* status;
    pjmsrp_header_expires_t* expires;
    pjmsrp_header_max_expires_t* max_expires;
    pjmsrp_header_min_expires_t* min_expires;
    pjmsrp_header_use_path_t* use_path;
    pjmsrp_header_www_authenticate_t* www_authenticate;
    pjmsrp_header_dummy_t* dummy;

    //! List of @ref pjmsrp_header_t elements.
    pjmsrp_headers_list_t headers;

    // Content
    pjmsrp_header_content_type_t* content_type; /**< Content-Type: message/cpim **/
    pj_str_t Content;					   /**<                  **/

    // End line
    struct {
    	pj_str_t tid; 	/**< transaction identifier eg: a786hjs2 **/
    	char cflag;	/**< continuation-flag eg: $ **/
    } end_line;
}pjmsrp_message_t;


typedef pjmsrp_message_t pjmsrp_request_t;  /**< MSRP request message. */
typedef pjmsrp_message_t pjmsrp_response_t; /**< MSRP response message. */

//functions

PJ_DECL(pjmsrp_message_t*) pjmsrp_message_create(pj_pool_t* pool, pjmsrp_message_type_t type, const pj_str_t* tid, const pj_str_t* method, pj_int16_t status, const pj_str_t* comment);
PJ_DECL(pjmsrp_message_t*) pjmsrp_request_create(pj_pool_t* pool, const pj_str_t* tid, const pj_str_t* method);
PJ_DECL(pjmsrp_message_t*) pjmsrp_response_create(pj_pool_t* pool, const pj_str_t* tid, pj_int16_t status, const pj_str_t* comment);
PJ_DECL(pjmsrp_message_t*) pjmsrp_message_create_default(pj_pool_t* pool);
PJ_DECL(pjmsrp_request_type_t) pjmsrp_request_get_type(const pj_str_t* method);
PJ_DECL(int) pjmsrp_message_add_header(pj_pool_t* pool, pjmsrp_message_t *self, const pjmsrp_header_t *hdr);

PJ_DECL(int) pjmsrp_message_tostring(pjmsrp_message_t *self, pj_str_t* output);
PJ_DECL(int) pjmsrp_start_line_tostring(pjmsrp_message_t *self, pj_str_t* output);
PJ_DECL(int) pjmsrp_end_line_tostring(pjmsrp_message_t *self, pj_str_t* output);
PJ_DECL(int) pjmsrp_content_tostring(pjmsrp_message_t *self, pj_str_t* output);
PJ_DECL(int) pjmsrp_header_tostring2(const pjmsrp_message_t *self, pj_str_t *output);

PJMSRP_END_DECLS
#endif /* PJMSRP_MESSAGE_H_ */
