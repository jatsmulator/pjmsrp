
/* #line 1 "./ragel/pjmsrp_parser_header_expires.rl" */
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

/* #line 58 "./ragel/pjmsrp_parser_header_expires.rl" */



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
	
/* #line 85 "./src/pjmsrp_parser_header_expires.c" */
static const char _pjmsrp_machine_parser_header_expires_actions[] = {
	0, 1, 0, 1, 1
};

static const char _pjmsrp_machine_parser_header_expires_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	14, 15, 16, 18, 19, 22
};

static const char _pjmsrp_machine_parser_header_expires_trans_keys[] = {
	69, 101, 88, 120, 80, 112, 73, 105, 
	82, 114, 69, 101, 83, 115, 58, 32, 
	48, 57, 10, 13, 48, 57, 0
};

static const char _pjmsrp_machine_parser_header_expires_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 2, 
	1, 1, 0, 1, 1, 0
};

static const char _pjmsrp_machine_parser_header_expires_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 1, 0
};

static const char _pjmsrp_machine_parser_header_expires_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18, 
	21, 23, 25, 27, 29, 32
};

static const char _pjmsrp_machine_parser_header_expires_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 5, 5, 1, 6, 
	6, 1, 7, 7, 1, 8, 1, 9, 
	1, 10, 1, 11, 1, 12, 13, 1, 
	1, 0
};

static const char _pjmsrp_machine_parser_header_expires_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	9, 10, 12, 13, 11, 12
};

static const char _pjmsrp_machine_parser_header_expires_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 3, 0
};

static const char _pjmsrp_machine_parser_header_expires_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 3, 0
};

static const int pjmsrp_machine_parser_header_expires_start = 1;
static const int pjmsrp_machine_parser_header_expires_first_final = 12;
static const int pjmsrp_machine_parser_header_expires_error = 0;

static const int pjmsrp_machine_parser_header_expires_en_main = 1;


/* #line 100 "./ragel/pjmsrp_parser_header_expires.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_expires_first_final);
	(void)(pjmsrp_machine_parser_header_expires_error);
	(void)(pjmsrp_machine_parser_header_expires_en_main);
	
/* #line 152 "./src/pjmsrp_parser_header_expires.c" */
	{
	cs = pjmsrp_machine_parser_header_expires_start;
	}

/* #line 105 "./ragel/pjmsrp_parser_header_expires.rl" */
	
/* #line 159 "./src/pjmsrp_parser_header_expires.c" */
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
	_keys = _pjmsrp_machine_parser_header_expires_trans_keys + _pjmsrp_machine_parser_header_expires_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_expires_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_expires_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_expires_range_lengths[cs];
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
	_trans = _pjmsrp_machine_parser_header_expires_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_expires_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_expires_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_expires_actions + _pjmsrp_machine_parser_header_expires_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 44 "./ragel/pjmsrp_parser_header_expires.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 48 "./ragel/pjmsrp_parser_header_expires.rl" */
	{
		PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Expires->value, int64_t, atoi64)
	}
	break;
/* #line 245 "./src/pjmsrp_parser_header_expires.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_expires_actions + _pjmsrp_machine_parser_header_expires_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 1:
/* #line 48 "./ragel/pjmsrp_parser_header_expires.rl" */
	{
		PJMSRP_PARSER_SET_INTEGER_EX(pool, hdr_Expires->value, int64_t, atoi64)
	}
	break;
/* #line 267 "./src/pjmsrp_parser_header_expires.c" */
		}
	}
	}

	_out: {}
	}

/* #line 106 "./ragel/pjmsrp_parser_header_expires.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < 12 ){
		PJ_LOG(3, ("pjmsrp_parser_header_expires.c", "Failed to parse 'expires' header."));
	}
	
	return hdr_Expires;
}