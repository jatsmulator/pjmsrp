
/* #line 1 "./ragel/pjmsrp_parser_header_message_id.rl" */
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
 
/**@file pjmsrp_parser_header_message_id.rl
 * @brief MSRP "Message-ID" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 
 #include "pjmsrp/pjmsrp_header_message_id.h"
 
 /***********************************
*	Ragel state machine.
*/


/* #line 57 "./ragel/pjmsrp_parser_header_message_id.rl" */



PJ_DEF(pjmsrp_header_message_id_t*) pjmsrp_header_message_id_create(pj_pool_t *pool, const pj_str_t* value)
{
	pjmsrp_header_message_id_t *message_id = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_message_id_t);
	
	message_id->pool = pool;
	if (value && value->ptr){
		pj_strcreate(pool, &message_id->value, value);
	} else {
		pj_str_t* tmp = pj_strcreate_null(pool);
		message_id->value = *tmp;
	}
	
	return message_id;	
}

PJ_DEF(pjmsrp_header_message_id_t*) pjmsrp_header_message_id_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_message_id_create(pool, NULL);
}

PJ_DEF(int) pjmsrp_header_message_id_tostring(const pjmsrp_header_message_id_t *message_id, pj_str_t* output)
{
    if(message_id) {
        if(message_id->value.ptr) {
            return pj_strappend(message_id->pool, output, &message_id->value);
        }
        return 0;
    }

    return -1;	
}

PJ_DEF(pjmsrp_header_message_id_t) *pjmsrp_header_message_id_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	int cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_message_id_t *hdr_Message_Id = pjmsrp_header_message_id_create_default(pool);
	
	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	
/* #line 87 "./src/pjmsrp_parser_header_message_id.c" */
static const char _pjmsrp_machine_parser_header_message_id_actions[] = {
	0, 1, 0, 1, 1
};

static const short _pjmsrp_machine_parser_header_message_id_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	14, 15, 17, 19, 20, 21, 27, 38, 
	49, 60, 61, 73, 73, 85, 97, 109, 
	121, 133, 145, 157, 169, 181, 193, 205, 
	217, 229, 241, 253, 265, 277, 289, 301, 
	313, 325, 337, 349, 361, 373, 385, 397
};

static const char _pjmsrp_machine_parser_header_message_id_trans_keys[] = {
	77, 109, 69, 101, 83, 115, 83, 115, 
	65, 97, 71, 103, 69, 101, 45, 73, 
	105, 68, 100, 58, 32, 48, 57, 65, 
	90, 97, 122, 37, 43, 61, 45, 46, 
	48, 57, 65, 90, 97, 122, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 37, 43, 61, 45, 46, 48, 57, 
	65, 90, 97, 122, 10, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 37, 43, 
	61, 45, 46, 48, 57, 65, 90, 97, 
	122, 13, 37, 43, 61, 45, 46, 48, 
	57, 65, 90, 97, 122, 13, 0
};

static const char _pjmsrp_machine_parser_header_message_id_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 2, 
	1, 2, 2, 1, 1, 0, 3, 3, 
	3, 1, 4, 0, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 1
};

static const char _pjmsrp_machine_parser_header_message_id_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 3, 4, 4, 
	4, 0, 4, 0, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 0
};

static const short _pjmsrp_machine_parser_header_message_id_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18, 
	21, 23, 26, 29, 31, 33, 37, 45, 
	53, 61, 63, 72, 73, 82, 91, 100, 
	109, 118, 127, 136, 145, 154, 163, 172, 
	181, 190, 199, 208, 217, 226, 235, 244, 
	253, 262, 271, 280, 289, 298, 307, 316
};

static const char _pjmsrp_machine_parser_header_message_id_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 5, 5, 1, 6, 
	6, 1, 7, 7, 1, 8, 1, 9, 
	9, 1, 10, 10, 1, 11, 1, 12, 
	1, 13, 13, 13, 1, 14, 14, 14, 
	14, 14, 14, 14, 1, 15, 15, 15, 
	15, 15, 15, 15, 1, 16, 16, 16, 
	16, 16, 16, 16, 1, 17, 1, 18, 
	19, 19, 19, 19, 19, 19, 19, 1, 
	1, 18, 20, 20, 20, 20, 20, 20, 
	20, 1, 18, 21, 21, 21, 21, 21, 
	21, 21, 1, 18, 22, 22, 22, 22, 
	22, 22, 22, 1, 18, 23, 23, 23, 
	23, 23, 23, 23, 1, 18, 24, 24, 
	24, 24, 24, 24, 24, 1, 18, 25, 
	25, 25, 25, 25, 25, 25, 1, 18, 
	26, 26, 26, 26, 26, 26, 26, 1, 
	18, 27, 27, 27, 27, 27, 27, 27, 
	1, 18, 28, 28, 28, 28, 28, 28, 
	28, 1, 18, 29, 29, 29, 29, 29, 
	29, 29, 1, 18, 30, 30, 30, 30, 
	30, 30, 30, 1, 18, 31, 31, 31, 
	31, 31, 31, 31, 1, 18, 32, 32, 
	32, 32, 32, 32, 32, 1, 18, 33, 
	33, 33, 33, 33, 33, 33, 1, 18, 
	34, 34, 34, 34, 34, 34, 34, 1, 
	18, 35, 35, 35, 35, 35, 35, 35, 
	1, 18, 36, 36, 36, 36, 36, 36, 
	36, 1, 18, 37, 37, 37, 37, 37, 
	37, 37, 1, 18, 38, 38, 38, 38, 
	38, 38, 38, 1, 18, 39, 39, 39, 
	39, 39, 39, 39, 1, 18, 40, 40, 
	40, 40, 40, 40, 40, 1, 18, 41, 
	41, 41, 41, 41, 41, 41, 1, 18, 
	42, 42, 42, 42, 42, 42, 42, 1, 
	18, 43, 43, 43, 43, 43, 43, 43, 
	1, 18, 44, 44, 44, 44, 44, 44, 
	44, 1, 18, 45, 45, 45, 45, 45, 
	45, 45, 1, 18, 46, 46, 46, 46, 
	46, 46, 46, 1, 18, 1, 0
};

static const char _pjmsrp_machine_parser_header_message_id_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 15, 16, 
	18, 19, 17, 20, 21, 22, 23, 24, 
	25, 26, 27, 28, 29, 30, 31, 32, 
	33, 34, 35, 36, 37, 38, 39, 40, 
	41, 42, 43, 44, 45, 46, 47
};

static const char _pjmsrp_machine_parser_header_message_id_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 3, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0
};

static const char _pjmsrp_machine_parser_header_message_id_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 3, 0, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3
};

static const int pjmsrp_machine_parser_header_message_id_start = 1;
static const int pjmsrp_machine_parser_header_message_id_first_final = 18;
static const int pjmsrp_machine_parser_header_message_id_error = 0;

static const int pjmsrp_machine_parser_header_message_id_en_main = 1;


/* #line 104 "./ragel/pjmsrp_parser_header_message_id.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_message_id_first_final);
	(void)(pjmsrp_machine_parser_header_message_id_error);
	(void)(pjmsrp_machine_parser_header_message_id_en_main);
	
/* #line 264 "./src/pjmsrp_parser_header_message_id.c" */
	{
	cs = pjmsrp_machine_parser_header_message_id_start;
	}

/* #line 109 "./ragel/pjmsrp_parser_header_message_id.rl" */
	
/* #line 271 "./src/pjmsrp_parser_header_message_id.c" */
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
	_keys = _pjmsrp_machine_parser_header_message_id_trans_keys + _pjmsrp_machine_parser_header_message_id_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_message_id_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_message_id_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_message_id_range_lengths[cs];
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
	_trans = _pjmsrp_machine_parser_header_message_id_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_message_id_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_message_id_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_message_id_actions + _pjmsrp_machine_parser_header_message_id_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 43 "./ragel/pjmsrp_parser_header_message_id.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 47 "./ragel/pjmsrp_parser_header_message_id.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Message_Id->value);
	}
	break;
/* #line 357 "./src/pjmsrp_parser_header_message_id.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_message_id_actions + _pjmsrp_machine_parser_header_message_id_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 1:
/* #line 47 "./ragel/pjmsrp_parser_header_message_id.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Message_Id->value);
	}
	break;
/* #line 379 "./src/pjmsrp_parser_header_message_id.c" */
		}
	}
	}

	_out: {}
	}

/* #line 110 "./ragel/pjmsrp_parser_header_message_id.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < 18 ){
		PJ_LOG(3, ("pjmsrp_parser_header_message_id.c", "Failed to parse 'Message-Id' header."));
	}
	
	return hdr_Message_Id;
}