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
 
/**@file pjmsrp_parser_header_dummy.rl
 * @brief MSRP "Dummy" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 #include "pjmsrp/pjmsrp_header_dummy.h"
 
 /***********************************
*	Ragel state machine.
*/
%%{
	machine pjmsrp_machine_parser_header_dummy;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}

	action parse_hname{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Dummy->name);
	}

	action parse_hval{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Dummy->value);
	}
	
	#//hname  ":" SP hval CRLF
	Dummy = hname>tag %parse_hname :>SP* ":" SP*<: hval>tag %parse_hval;
	
	# Entry point
	main := Dummy :>CRLF?;

}%%

PJ_DEF(pjmsrp_header_dummy_t*) pjmsrp_header_dummy_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_dummy_create(pool, NULL, NULL);
}

PJ_DEF(pjmsrp_header_dummy_t*) pjmsrp_header_dummy_create(pj_pool_t *pool, pj_str_t* name, pj_str_t* value)
{
	pjmsrp_header_dummy_t *dummy = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_dummy_t);
	
	if (name){
		pj_strcreate(pool, &dummy->name, name);
	} else {
		pj_str_t* tmp = pj_strcreate_null(pool);
		dummy->name = *tmp;
	}
	
	if (value){
		pj_strcreate(pool, &dummy->value, value);
	} else {
		pj_str_t* tmp = pj_strcreate_null(pool);
		dummy->value = *tmp;
	}

	return dummy;	
}

PJ_DEF(pjmsrp_header_dummy_t*) pjmsrp_header_dummy_parse(pj_pool_t* pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_dummy_t *hdr_Dummy = pjmsrp_header_dummy_create_default(pool);
	
	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_dummy_first_final);
	(void)(pjmsrp_machine_parser_header_dummy_error);
	(void)(pjmsrp_machine_parser_header_dummy_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, (__FILE__, "Failed to parse Dummy header."));
	}
	
	return hdr_Dummy;
}


PJ_DEF(int) pjmsrp_header_dummy_tostring(const pjmsrp_header_dummy_t* dummy, pj_str_t* output)
{
    if(dummy) {
        if(dummy->value.ptr) {
            return pj_strappend(dummy->pool, output, &dummy->value);
        }
        return 0;
    }

    return -1;
}