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
 
/**@file pjmsrp_parser_header_expires.rl
 * @brief MSRP "Status" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 
 #include "pjmsrp/pjmsrp_header_expires.h"
 
 /***********************************
*	Ragel state machine.
*/

/***********************************
*	Ragel state machine.
*/
%%{
	machine pjmsrp_machine_parser_header_expires;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}

	action parse_value{
		PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Expires->value, int64_t, atoi64)
	}
	
	#// "Expires:" SP 1*DIGIT 
	Expires = "Expires:"i SP DIGIT+>tag %parse_value;
	
	# Entry point
	main := Expires :>CRLF?;

}%%


PJ_DEF(pjmsrp_header_expires_t*) pjmsrp_header_expires_create(pj_pool_t *pool, int64_t value){
	pjmsrp_header_expires_t *expires = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_expires_t);
	
	expires->pool = pool;
	expires->value = value;
	
	return expires;	
}

PJ_DEF(pjmsrp_header_expires_t*) pjmsrp_header_expires_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_expires_create(pool, -1);
}

PJ_DEF(int) pjmsrp_header_expires_tostring(const pjmsrp_header_expires_t *expires, pj_str_t* output)
{
	if(expires){
		if(expires->value >= 0){
			return pj_strappend2_v(expires->pool, output, "%lld", expires->value);
		}
		return 0;
	}

	return -1;
}


PJ_DEF(pjmsrp_header_expires_t) *pjmsrp_header_expires_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_expires_t *hdr_Expires = pjmsrp_header_expires_create_default(pool);
	
	const char *tag_start = NULL;
	
	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_expires_first_final);
	(void)(pjmsrp_machine_parser_header_expires_error);
	(void)(pjmsrp_machine_parser_header_expires_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_expires.c", "Failed to parse 'expires' header."));
	}
	
	return hdr_Expires;
}