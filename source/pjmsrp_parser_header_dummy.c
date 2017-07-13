
/* #line 1 "./ragel/pjmsrp_parser_header_dummy.rl" */
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

/* #line 57 "./ragel/pjmsrp_parser_header_dummy.rl" */


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
	
/* #line 75 "./src/pjmsrp_parser_header_dummy.c" */
static const char _pjmsrp_machine_parser_header_dummy_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 2, 
	0, 2
};

static const char _pjmsrp_machine_parser_header_dummy_key_offsets[] = {
	0, 0, 14, 30, 32, 33, 40, 46
};

static const char _pjmsrp_machine_parser_header_dummy_trans_keys[] = {
	33, 37, 39, 126, 42, 43, 45, 46, 
	48, 57, 65, 90, 95, 122, 32, 33, 
	37, 39, 58, 126, 42, 43, 45, 46, 
	48, 57, 65, 90, 95, 122, 32, 58, 
	10, 13, 32, 127, 0, 8, 10, 31, 
	13, 127, 0, 8, 10, 31, 0
};

static const char _pjmsrp_machine_parser_header_dummy_single_lengths[] = {
	0, 4, 6, 2, 1, 3, 2, 0
};

static const char _pjmsrp_machine_parser_header_dummy_range_lengths[] = {
	0, 5, 5, 0, 0, 2, 2, 0
};

static const char _pjmsrp_machine_parser_header_dummy_index_offsets[] = {
	0, 0, 10, 22, 25, 27, 33, 38
};

static const char _pjmsrp_machine_parser_header_dummy_indicies[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 2, 3, 3, 3, 4, 3, 
	3, 3, 3, 3, 3, 1, 5, 6, 
	1, 7, 1, 9, 6, 1, 1, 1, 
	8, 11, 1, 1, 1, 10, 1, 0
};

static const char _pjmsrp_machine_parser_header_dummy_trans_targs[] = {
	2, 0, 3, 2, 5, 3, 5, 7, 
	6, 4, 6, 4
};

static const char _pjmsrp_machine_parser_header_dummy_trans_actions[] = {
	1, 0, 3, 0, 3, 0, 0, 0, 
	1, 7, 0, 5
};

static const char _pjmsrp_machine_parser_header_dummy_eof_actions[] = {
	0, 0, 0, 0, 0, 7, 5, 0
};

static const int pjmsrp_machine_parser_header_dummy_start = 1;
static const int pjmsrp_machine_parser_header_dummy_first_final = 5;
static const int pjmsrp_machine_parser_header_dummy_error = 0;

static const int pjmsrp_machine_parser_header_dummy_en_main = 1;


/* #line 94 "./ragel/pjmsrp_parser_header_dummy.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_dummy_first_final);
	(void)(pjmsrp_machine_parser_header_dummy_error);
	(void)(pjmsrp_machine_parser_header_dummy_en_main);
	
/* #line 141 "./src/pjmsrp_parser_header_dummy.c" */
	{
	cs = pjmsrp_machine_parser_header_dummy_start;
	}

/* #line 99 "./ragel/pjmsrp_parser_header_dummy.rl" */
	
/* #line 148 "./src/pjmsrp_parser_header_dummy.c" */
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
	_keys = _pjmsrp_machine_parser_header_dummy_trans_keys + _pjmsrp_machine_parser_header_dummy_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_dummy_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_dummy_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_dummy_range_lengths[cs];
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
	_trans = _pjmsrp_machine_parser_header_dummy_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_dummy_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_dummy_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_dummy_actions + _pjmsrp_machine_parser_header_dummy_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 39 "./ragel/pjmsrp_parser_header_dummy.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 43 "./ragel/pjmsrp_parser_header_dummy.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Dummy->name);
	}
	break;
	case 2:
/* #line 47 "./ragel/pjmsrp_parser_header_dummy.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Dummy->value);
	}
	break;
/* #line 240 "./src/pjmsrp_parser_header_dummy.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_dummy_actions + _pjmsrp_machine_parser_header_dummy_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
/* #line 39 "./ragel/pjmsrp_parser_header_dummy.rl" */
	{
		tag_start = p;
	}
	break;
	case 2:
/* #line 47 "./ragel/pjmsrp_parser_header_dummy.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Dummy->value);
	}
	break;
/* #line 268 "./src/pjmsrp_parser_header_dummy.c" */
		}
	}
	}

	_out: {}
	}

/* #line 100 "./ragel/pjmsrp_parser_header_dummy.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < 5 ){
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
