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
 
/**@file pjmsrp_parser_header_status.rl
 * @brief MSRP "Status" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 
 #include "pjmsrp/pjmsrp_header_status.h"
 
 /***********************************
*	Ragel state machine.
*/

/***********************************
*	Ragel state machine.
*/
%%{
	machine pjmsrp_machine_parser_header_status;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}
	
	action parse_namespace{
		PJMSRP_PARSER_SET_INT(pool, hdr_Status->_namespace);
	}
	
	action parse_code{
		PJMSRP_PARSER_SET_INT(pool, hdr_Status->code);
	}
	
	action parse_reason{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Status->reason);
	}

	#/// @par ABNF :  Status	=  	 "Status:" SP namespace  SP status-code  [SP text-reason]
	#/// namespace	= 	3(DIGIT) ; "000" for all codes defined in RFC 4975
	#/// text-reason	= 	utf8text 
	Status = "Status:"i SP DIGIT{3}>tag %parse_namespace SP DIGIT{3}>tag %parse_code (SP utf8text>tag %parse_reason)?;
	
	# Entry point
	main := Status :>CRLF?;

}%%


PJ_DEF(pjmsrp_header_status_t*) pjmsrp_header_status_create(pj_pool_t *pool)
{
	pjmsrp_header_status_t *status = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_status_t);
	pj_bzero(&status->reason, 0);
	status->_namespace = 0;
	status->code = 200;
	
	return status;	
}

PJ_DEF(int) pjmsrp_header_status_tostring(const pjmsrp_header_status_t* status, pj_str_t* output)
{
    if(status) {
        // Status: 000 200 OK
        return pj_strappend2_v(status->pool, output, "%.3hi %.3hi%s%s",
                                   status->_namespace,
                                   status->code,
                                   status->reason.ptr ? " " : "",
                                   status->reason.ptr ? status->reason.ptr : ""
                                  );
    }

    return -1;
}


PJ_DEF(pjmsrp_header_status_t) *pjmsrp_header_status_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_status_t *hdr_Status = pjmsrp_header_status_create(pool);
	
	const char *tag_start = NULL;
	
	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_status_first_final);
	(void)(pjmsrp_machine_parser_header_status_error);
	(void)(pjmsrp_machine_parser_header_status_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_status.c", "Failed to parse 'Status' header."));
	}
	
	return hdr_Status;
}