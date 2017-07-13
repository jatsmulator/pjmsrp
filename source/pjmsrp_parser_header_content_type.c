
/* #line 1 "./ragel/pjmsrp_parser_header_content_type.rl" */
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
 
/**@file pjmsrp_parser_header_content_type.rl
 * @brief MSRP "Content-Type" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
  #include "pjmsrp/pjmsrp_header_content_type.h"
 
 /***********************************
*	Ragel state machine.
*/

/***********************************
*	Ragel state machine.
*/

/* #line 67 "./ragel/pjmsrp_parser_header_content_type.rl" */



PJ_DEF(pjmsrp_header_content_type_t*) pjmsrp_header_content_type_create(pj_pool_t *pool, pj_str_t* value, pj_param_list_t* params)
{
	pjmsrp_header_content_type_t *contentType = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_content_type_t);
	
	contentType->pool = pool;
	
	if (value){
		pj_strcreate(pool, &contentType->value, value); //Allocate memory and assign
	}
	
	if (params == NULL){
		pj_list_init(&contentType->params);
	} else {
		contentType->params = *params;
	}
	
	return contentType;	
}


PJ_DEF(pjmsrp_header_content_type_t*) pjmsrp_header_content_type_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_content_type_create(pool, NULL, NULL);
}

PJ_DEF(int) pjmsrp_header_content_type_tostring(const pjmsrp_header_content_type_t *contentType, pj_str_t* output){
	if(contentType){
		if (contentType->value.ptr){
			pj_strappend(contentType->pool, output, &contentType->value);
		}
		
	    if (!pj_list_empty(&contentType->params)){
	    	pj_params_tostring(contentType->pool, &contentType->params, ';', output);
		}
	}
	
	return -1;
}

PJ_DEF(pjmsrp_header_content_type_t) *pjmsrp_header_content_type_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_content_type_t *hdr_ctype = pjmsrp_header_content_type_create_default(pool);
	
	const char *tag_start = NULL;
	
	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	
/* #line 98 "./src/pjmsrp_parser_header_content_type.c" */
static const char _pjmsrp_machine_parser_header_content_type_actions[] = {
	0, 1, 0, 1, 1, 1, 2
};

static const short _pjmsrp_machine_parser_header_content_type_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	14, 15, 17, 19, 21, 23, 26, 43, 
	44, 46, 62, 78, 82, 83, 85, 88, 
	105, 106, 108, 124, 128, 129, 131, 134, 
	150, 151, 153, 168, 173, 174, 176, 180, 
	196, 197, 199, 214, 215, 221, 227, 233, 
	239, 257, 275, 292
};

static const char _pjmsrp_machine_parser_header_content_type_trans_keys[] = {
	67, 99, 79, 111, 78, 110, 84, 116, 
	69, 101, 78, 110, 84, 116, 45, 84, 
	116, 89, 121, 80, 112, 69, 101, 9, 
	32, 58, 9, 13, 32, 33, 37, 39, 
	126, 42, 43, 45, 46, 48, 57, 65, 
	90, 95, 122, 10, 9, 32, 9, 32, 
	33, 37, 39, 126, 42, 43, 45, 46, 
	48, 57, 65, 90, 95, 122, 9, 13, 
	32, 33, 37, 39, 47, 126, 42, 43, 
	45, 57, 65, 90, 95, 122, 9, 13, 
	32, 47, 10, 9, 32, 9, 32, 47, 
	9, 13, 32, 33, 37, 39, 126, 42, 
	43, 45, 46, 48, 57, 65, 90, 95, 
	122, 10, 9, 32, 9, 32, 33, 37, 
	39, 126, 42, 43, 45, 46, 48, 57, 
	65, 90, 95, 122, 9, 13, 32, 59, 
	10, 9, 32, 9, 32, 59, 9, 13, 
	32, 33, 37, 93, 95, 126, 36, 43, 
	45, 58, 65, 91, 97, 122, 10, 9, 
	32, 9, 32, 33, 37, 93, 95, 126, 
	36, 43, 45, 58, 65, 91, 97, 122, 
	9, 13, 32, 59, 61, 10, 9, 32, 
	9, 32, 59, 61, 9, 13, 32, 33, 
	37, 93, 95, 126, 36, 43, 45, 58, 
	65, 91, 97, 122, 10, 9, 32, 9, 
	32, 33, 37, 93, 95, 126, 36, 43, 
	45, 58, 65, 91, 97, 122, 10, 48, 
	57, 65, 70, 97, 102, 48, 57, 65, 
	70, 97, 102, 48, 57, 65, 70, 97, 
	102, 48, 57, 65, 70, 97, 102, 9, 
	13, 32, 33, 37, 39, 59, 126, 42, 
	43, 45, 46, 48, 57, 65, 90, 95, 
	122, 9, 13, 32, 33, 37, 59, 61, 
	93, 95, 126, 36, 43, 45, 58, 65, 
	91, 97, 122, 9, 13, 32, 33, 37, 
	59, 93, 95, 126, 36, 43, 45, 58, 
	65, 91, 97, 122, 0
};

static const char _pjmsrp_machine_parser_header_content_type_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 2, 
	1, 2, 2, 2, 2, 3, 7, 1, 
	2, 6, 8, 4, 1, 2, 3, 7, 
	1, 2, 6, 4, 1, 2, 3, 8, 
	1, 2, 7, 5, 1, 2, 4, 8, 
	1, 2, 7, 1, 0, 0, 0, 0, 
	8, 10, 9, 0
};

static const char _pjmsrp_machine_parser_header_content_type_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 5, 0, 
	0, 5, 4, 0, 0, 0, 0, 5, 
	0, 0, 5, 0, 0, 0, 0, 4, 
	0, 0, 4, 0, 0, 0, 0, 4, 
	0, 0, 4, 0, 3, 3, 3, 3, 
	5, 4, 4, 0
};

static const short _pjmsrp_machine_parser_header_content_type_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18, 
	21, 23, 26, 29, 32, 35, 39, 52, 
	54, 57, 69, 82, 87, 89, 92, 96, 
	109, 111, 114, 126, 131, 133, 136, 140, 
	153, 155, 158, 170, 176, 178, 181, 186, 
	199, 201, 204, 216, 218, 222, 226, 230, 
	234, 248, 263, 277
};

static const char _pjmsrp_machine_parser_header_content_type_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 5, 5, 1, 6, 
	6, 1, 7, 7, 1, 8, 1, 9, 
	9, 1, 10, 10, 1, 11, 11, 1, 
	12, 12, 1, 12, 12, 13, 1, 13, 
	14, 13, 15, 15, 15, 15, 15, 15, 
	15, 15, 15, 1, 16, 1, 17, 17, 
	1, 17, 17, 15, 15, 15, 15, 15, 
	15, 15, 15, 15, 1, 18, 19, 18, 
	20, 20, 20, 21, 20, 20, 20, 20, 
	20, 1, 18, 19, 18, 21, 1, 22, 
	1, 23, 23, 1, 23, 23, 21, 1, 
	21, 24, 21, 25, 25, 25, 25, 25, 
	25, 25, 25, 25, 1, 26, 1, 27, 
	27, 1, 27, 27, 25, 25, 25, 25, 
	25, 25, 25, 25, 25, 1, 28, 29, 
	28, 30, 1, 31, 1, 32, 32, 1, 
	32, 32, 30, 1, 30, 33, 30, 34, 
	35, 34, 34, 34, 34, 34, 34, 34, 
	1, 36, 1, 37, 37, 1, 37, 37, 
	34, 35, 34, 34, 34, 34, 34, 34, 
	34, 1, 38, 39, 38, 30, 40, 1, 
	41, 1, 42, 42, 1, 42, 42, 30, 
	40, 1, 40, 43, 40, 44, 45, 44, 
	44, 44, 44, 44, 44, 44, 1, 46, 
	1, 47, 47, 1, 47, 47, 44, 45, 
	44, 44, 44, 44, 44, 44, 44, 1, 
	48, 1, 49, 49, 49, 1, 44, 44, 
	44, 1, 50, 50, 50, 1, 51, 51, 
	51, 1, 52, 53, 52, 25, 25, 25, 
	54, 25, 25, 25, 25, 25, 25, 1, 
	55, 56, 55, 51, 57, 58, 40, 51, 
	51, 51, 51, 51, 51, 51, 1, 59, 
	56, 59, 44, 45, 58, 44, 44, 44, 
	44, 44, 44, 44, 1, 1, 0
};

static const char _pjmsrp_machine_parser_header_content_type_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 15, 18, 
	16, 17, 19, 20, 18, 23, 21, 22, 
	24, 48, 25, 26, 27, 28, 31, 29, 
	30, 32, 49, 46, 33, 34, 35, 36, 
	39, 37, 38, 40, 50, 44, 41, 42, 
	51, 45, 47, 49, 27, 43, 31, 35, 
	43, 46, 31, 27
};

static const char _pjmsrp_machine_parser_header_content_type_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 3, 3, 3, 5, 
	5, 0, 5, 5
};

static const char _pjmsrp_machine_parser_header_content_type_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	3, 5, 5, 0
};

static const int pjmsrp_machine_parser_header_content_type_start = 1;
static const int pjmsrp_machine_parser_header_content_type_first_final = 48;
static const int pjmsrp_machine_parser_header_content_type_error = 0;

static const int pjmsrp_machine_parser_header_content_type_en_main = 1;


/* #line 123 "./ragel/pjmsrp_parser_header_content_type.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_content_type_first_final);
	(void)(pjmsrp_machine_parser_header_content_type_error);
	(void)(pjmsrp_machine_parser_header_content_type_en_main);
	
/* #line 266 "./src/pjmsrp_parser_header_content_type.c" */
	{
	cs = pjmsrp_machine_parser_header_content_type_start;
	}

/* #line 128 "./ragel/pjmsrp_parser_header_content_type.rl" */
	
/* #line 273 "./src/pjmsrp_parser_header_content_type.c" */
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
	_keys = _pjmsrp_machine_parser_header_content_type_trans_keys + _pjmsrp_machine_parser_header_content_type_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_content_type_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_content_type_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_content_type_range_lengths[cs];
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
	_trans = _pjmsrp_machine_parser_header_content_type_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_content_type_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_content_type_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_content_type_actions + _pjmsrp_machine_parser_header_content_type_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 43 "./ragel/pjmsrp_parser_header_content_type.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 47 "./ragel/pjmsrp_parser_header_content_type.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_ctype->value);
	}
	break;
	case 2:
/* #line 51 "./ragel/pjmsrp_parser_header_content_type.rl" */
	{		
		PJMSRP_PARSER_ADD_PARAM(pool, hdr_ctype->params);
	}
	break;
/* #line 365 "./src/pjmsrp_parser_header_content_type.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_content_type_actions + _pjmsrp_machine_parser_header_content_type_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 1:
/* #line 47 "./ragel/pjmsrp_parser_header_content_type.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_ctype->value);
	}
	break;
	case 2:
/* #line 51 "./ragel/pjmsrp_parser_header_content_type.rl" */
	{		
		PJMSRP_PARSER_ADD_PARAM(pool, hdr_ctype->params);
	}
	break;
/* #line 393 "./src/pjmsrp_parser_header_content_type.c" */
		}
	}
	}

	_out: {}
	}

/* #line 129 "./ragel/pjmsrp_parser_header_content_type.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < 48 ){
		PJ_LOG(3, ("pjmsrp_parser_header_content_type.c", "Failed to parse 'Content-Type' header."));
	}
	
	return hdr_ctype;
}
