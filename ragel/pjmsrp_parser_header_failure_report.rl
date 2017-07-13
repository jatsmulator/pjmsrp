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
 
/**@file pjmsrp_parser_header_failure_report.rl
 * @brief MSRP "Message-ID" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 
 #include "pjmsrp/pjmsrp_header_failure_report.h"
 
 /***********************************
*	Ragel state machine.
*/

%%{

	machine pjmsrp_machine_parser_header_failure_report;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action is_yes{
		hdr_Failure_Report->type = freport_yes;
	}

	action is_no{
		hdr_Failure_Report->type = freport_no;
	}

	action ispartial{
		hdr_Failure_Report->type = freport_partial;
	}
	
	#// "Failure-Report:" ( "yes" / "no" / "partial" )  
	Failure_Report = "Failure-Report:"i SP ("yes"i %is_yes | "no"i %is_no | "partial"i %ispartial);
	
	# Entry point
	main := Failure_Report :>CRLF?;
	
}%%

PJ_DEF(pjmsrp_header_failure_report_t*) pjmsrp_header_failure_report_create(pj_pool_t *pool, pjmsrp_freport_type_t type)
{
	pjmsrp_header_failure_report_t *failure_report = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_failure_report_t);
	
	failure_report->pool = pool;
	failure_report->type = type;
	
	return failure_report;	
}

PJ_DEF(pjmsrp_header_failure_report_t*) pjmsrp_header_failure_report_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_failure_report_create(pool, freport_yes);
}

int pjmsrp_header_failure_report_tostring(const pjmsrp_header_failure_report_t* failureReport, pj_str_t* output)
{
	if(failureReport){
		const char* value = (failureReport->type == freport_yes) ? "yes" : (failureReport->type == freport_no ? "no" : "partial");
		return pj_strappend2(failureReport->pool, output, value, strlen(value));
	}

	return -1;
}

PJ_DEF(pjmsrp_header_failure_report_t) *pjmsrp_header_failure_report_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_failure_report_t *hdr_Failure_Report = pjmsrp_header_failure_report_create_default(pool);
	
	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_failure_report_first_final);
	(void)(pjmsrp_machine_parser_header_failure_report_error);
	(void)(pjmsrp_machine_parser_header_failure_report_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_failure_report.c", "Failed to parse 'failure-Report' header."));
	}
	
	return hdr_Failure_Report;
}