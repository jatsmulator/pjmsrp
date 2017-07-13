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
 
/**@file pjmsrp_parser_header_byte_range.rl
 * @brief MSRP "From-Path" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 #include "pjmsrp/pjmsrp_header_byte_range.h"
 
 /***********************************
*	Ragel state machine.
*/

%%{

	machine pjmsrp_machine_parser_header_byte_range;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	
	action tag{
		tag_start = p;
	}
	
	action parse_start{
		PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->start, int64_t, atoi64);
	}
	
	action parse_end{
		if(tag_start && *tag_start == '*'){
			hdr_Byte_Range->end = -1;
		}
		else{
			PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->end, int64_t, atoi64);
		}
	}
	
	action parse_total{
		if(tag_start && *tag_start == '*'){
			hdr_Byte_Range->total = -1;
		}
		else{
			PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->total, int64_t, atoi64);
		}
	}

	#// Byte-Range	=  	 "Byte-Range:" SP range-start  "-" range-end  "/" total
	#//range-start	= 	1*DIGIT
	#//range-end	= 	1*DIGIT / "*"
	#//total		= 	1*DIGIT / "*"
	Byte_Range = "Byte-Range:"i SP DIGIT+>tag %parse_start "-" (DIGIT+ | "*")>tag %parse_end "/" (DIGIT+ | "*")>tag %parse_total;
	
	# Entry point
	main := Byte_Range :>CRLF?;
	
}%%

PJ_DEF(pjmsrp_header_byte_range_t*) pjmsrp_header_byte_range_create(pj_pool_t *pool, int64_t start, int64_t end, int64_t total){

	pjmsrp_header_byte_range_t *byte_range = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_byte_range_t);

	byte_range->pool = pool;
	byte_range->start = start;
	byte_range->end   = end;
	byte_range->total = total;

	return byte_range;
}

PJ_DEF(pjmsrp_header_byte_range_t*) pjmsrp_header_byte_range_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_byte_range_create(pool, 1, -1, -1);
}

PJ_DEF(int) pjmsrp_header_byte_range_tostring(const pjmsrp_header_byte_range_t *ByteRange, pj_str_t* output)
{

	pj_istr_t start, end, total;

	if(!ByteRange){
		return 0;
	}

    if(ByteRange->start>=0) {
        pj_itoa(ByteRange->start, &start);
    }
    if(ByteRange->end>=0) {
    	pj_itoa(ByteRange->end, &end);
    }
    if(ByteRange->total>=0) {
    	pj_itoa(ByteRange->total, &total);
    }

    return pj_strappend2_v(
    		ByteRange->pool, output, "%s-%s/%s",
                               ByteRange->start>=0 ? start : "*",
                               ByteRange->end>=0 ? end : "*",
                               ByteRange->total>=0 ? total : "*"
                              );

}


PJ_DEF(pjmsrp_header_byte_range_t*) pjmsrp_header_byte_range_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	pj_int32_t cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_byte_range_t *hdr_Byte_Range = pjmsrp_header_byte_range_create_default(pool);

	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_byte_range_first_final);
	(void)(pjmsrp_machine_parser_header_byte_range_error);
	(void)(pjmsrp_machine_parser_header_byte_range_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_byte_range.c", "Failed to parse Byte-Range header."));
	}
	
	return hdr_Byte_Range;
}