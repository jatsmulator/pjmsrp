
/* #line 1 "./ragel/pjmsrp_parser_header_byte_range.rl" */
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


/* #line 77 "./ragel/pjmsrp_parser_header_byte_range.rl" */


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
	
/* #line 99 "./src/pjmsrp_parser_header_byte_range.c" */
static const char _pjmsrp_machine_parser_header_byte_range_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3
};

static const char _pjmsrp_machine_parser_header_byte_range_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 9, 11, 
	13, 15, 17, 19, 20, 21, 23, 26, 
	29, 30, 33, 34, 37, 38, 38
};

static const char _pjmsrp_machine_parser_header_byte_range_trans_keys[] = {
	66, 98, 89, 121, 84, 116, 69, 101, 
	45, 82, 114, 65, 97, 78, 110, 71, 
	103, 69, 101, 58, 32, 48, 57, 45, 
	48, 57, 42, 48, 57, 47, 42, 48, 
	57, 10, 47, 48, 57, 13, 13, 48, 
	57, 0
};

static const char _pjmsrp_machine_parser_header_byte_range_single_lengths[] = {
	0, 2, 2, 2, 2, 1, 2, 2, 
	2, 2, 2, 1, 1, 0, 1, 1, 
	1, 1, 1, 1, 1, 0, 1
};

static const char _pjmsrp_machine_parser_header_byte_range_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 1, 1, 
	0, 1, 0, 1, 0, 0, 1
};

static const char _pjmsrp_machine_parser_header_byte_range_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 14, 17, 
	20, 23, 26, 29, 31, 33, 35, 38, 
	41, 43, 46, 48, 51, 53, 54
};

static const char _pjmsrp_machine_parser_header_byte_range_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 5, 1, 6, 6, 
	1, 7, 7, 1, 8, 8, 1, 9, 
	9, 1, 10, 10, 1, 11, 1, 12, 
	1, 13, 1, 14, 15, 1, 16, 17, 
	1, 18, 1, 19, 20, 1, 21, 1, 
	18, 22, 1, 23, 1, 1, 23, 24, 
	1, 0
};

static const char _pjmsrp_machine_parser_header_byte_range_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 15, 14, 
	16, 19, 17, 20, 22, 21, 19, 18, 
	22
};

static const char _pjmsrp_machine_parser_header_byte_range_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 3, 0, 
	1, 1, 5, 1, 1, 0, 0, 7, 
	0
};

static const char _pjmsrp_machine_parser_header_byte_range_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 7, 0, 7
};

static const int pjmsrp_machine_parser_header_byte_range_start = 1;
static const int pjmsrp_machine_parser_header_byte_range_first_final = 20;
static const int pjmsrp_machine_parser_header_byte_range_error = 0;

static const int pjmsrp_machine_parser_header_byte_range_en_main = 1;


/* #line 137 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_byte_range_first_final);
	(void)(pjmsrp_machine_parser_header_byte_range_error);
	(void)(pjmsrp_machine_parser_header_byte_range_en_main);
	
/* #line 182 "./src/pjmsrp_parser_header_byte_range.c" */
	{
	cs = pjmsrp_machine_parser_header_byte_range_start;
	}

/* #line 142 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	
/* #line 189 "./src/pjmsrp_parser_header_byte_range.c" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _pjmsrp_machine_parser_header_byte_range_trans_keys + _pjmsrp_machine_parser_header_byte_range_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_byte_range_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_byte_range_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _pjmsrp_machine_parser_header_byte_range_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _pjmsrp_machine_parser_header_byte_range_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_byte_range_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_byte_range_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_byte_range_actions + _pjmsrp_machine_parser_header_byte_range_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 42 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 46 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	{
		PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->start, int64_t, atoi64);
	}
	break;
	case 2:
/* #line 50 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	{
		if(tag_start && *tag_start == '*'){
			hdr_Byte_Range->end = -1;
		}
		else{
			PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->end, int64_t, atoi64);
		}
	}
	break;
	case 3:
/* #line 59 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	{
		if(tag_start && *tag_start == '*'){
			hdr_Byte_Range->total = -1;
		}
		else{
			PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->total, int64_t, atoi64);
		}
	}
	break;
/* #line 297 "./src/pjmsrp_parser_header_byte_range.c" */
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _pjmsrp_machine_parser_header_byte_range_actions + _pjmsrp_machine_parser_header_byte_range_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 3:
/* #line 59 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	{
		if(tag_start && *tag_start == '*'){
			hdr_Byte_Range->total = -1;
		}
		else{
			PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Byte_Range->total, int64_t, atoi64);
		}
	}
	break;
/* #line 324 "./src/pjmsrp_parser_header_byte_range.c" */
		}
	}
	}

	_out: {}
	}

/* #line 143 "./ragel/pjmsrp_parser_header_byte_range.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < 20 ){
		PJ_LOG(3, ("pjmsrp_parser_header_byte_range.c", "Failed to parse Byte-Range header."));
	}
	
	return hdr_Byte_Range;
}