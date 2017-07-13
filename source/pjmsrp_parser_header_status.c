
/* #line 1 "./ragel/pjmsrp_parser_header_status.rl" */
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

/* #line 68 "./ragel/pjmsrp_parser_header_status.rl" */



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
	
/* #line 84 "./src/pjmsrp_parser_header_status.c" */
static const char _pjmsrp_machine_parser_header_status_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 2, 0, 3
};

static const char _pjmsrp_machine_parser_header_status_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	13, 14, 16, 18, 20, 21, 23, 25, 
	27, 28, 30, 30, 36
};

static const char _pjmsrp_machine_parser_header_status_trans_keys[] = {
	83, 115, 84, 116, 65, 97, 84, 116, 
	85, 117, 83, 115, 58, 32, 48, 57, 
	48, 57, 48, 57, 32, 48, 57, 48, 
	57, 48, 57, 10, 13, 32, 13, 127, 
	0, 8, 10, 31, 13, 127, 0, 8, 
	10, 31, 0
};

static const char _pjmsrp_machine_parser_header_status_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 1, 
	1, 0, 0, 0, 1, 0, 0, 0, 
	1, 2, 0, 2, 2
};

static const char _pjmsrp_machine_parser_header_status_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 1, 0, 1, 1, 1, 
	0, 0, 0, 2, 2
};

static const char _pjmsrp_machine_parser_header_status_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18, 
	20, 22, 24, 26, 28, 30, 32, 34, 
	36, 38, 41, 42, 47
};

static const char _pjmsrp_machine_parser_header_status_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 5, 5, 1, 6, 
	6, 1, 7, 1, 8, 1, 9, 1, 
	10, 1, 11, 1, 12, 1, 13, 1, 
	14, 1, 15, 1, 16, 1, 17, 18, 
	1, 1, 20, 1, 1, 1, 19, 22, 
	1, 1, 1, 21, 0
};

static const char _pjmsrp_machine_parser_header_status_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 15, 17, 
	18, 16, 19, 20, 16, 20, 16
};

static const char _pjmsrp_machine_parser_header_status_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 3, 1, 0, 0, 
	0, 5, 5, 1, 9, 0, 7
};

static const char _pjmsrp_machine_parser_header_status_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 5, 0, 9, 7
};

static const int pjmsrp_machine_parser_header_status_start = 1;
static const int pjmsrp_machine_parser_header_status_first_final = 17;
static const int pjmsrp_machine_parser_header_status_error = 0;

static const int pjmsrp_machine_parser_header_status_en_main = 1;


/* #line 109 "./ragel/pjmsrp_parser_header_status.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_status_first_final);
	(void)(pjmsrp_machine_parser_header_status_error);
	(void)(pjmsrp_machine_parser_header_status_en_main);
	
/* #line 164 "./src/pjmsrp_parser_header_status.c" */
	{
	cs = pjmsrp_machine_parser_header_status_start;
	}

/* #line 114 "./ragel/pjmsrp_parser_header_status.rl" */
	
/* #line 171 "./src/pjmsrp_parser_header_status.c" */
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
	_keys = _pjmsrp_machine_parser_header_status_trans_keys + _pjmsrp_machine_parser_header_status_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_status_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_status_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_status_range_lengths[cs];
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
	_trans = _pjmsrp_machine_parser_header_status_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_status_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_status_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_status_actions + _pjmsrp_machine_parser_header_status_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 44 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 48 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		PJMSRP_PARSER_SET_INT(pool, hdr_Status->_namespace);
	}
	break;
	case 2:
/* #line 52 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		PJMSRP_PARSER_SET_INT(pool, hdr_Status->code);
	}
	break;
	case 3:
/* #line 56 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Status->reason);
	}
	break;
/* #line 269 "./src/pjmsrp_parser_header_status.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_status_actions + _pjmsrp_machine_parser_header_status_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
/* #line 44 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		tag_start = p;
	}
	break;
	case 2:
/* #line 52 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		PJMSRP_PARSER_SET_INT(pool, hdr_Status->code);
	}
	break;
	case 3:
/* #line 56 "./ragel/pjmsrp_parser_header_status.rl" */
	{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Status->reason);
	}
	break;
/* #line 303 "./src/pjmsrp_parser_header_status.c" */
		}
	}
	}

	_out: {}
	}

/* #line 115 "./ragel/pjmsrp_parser_header_status.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < 17 ){
		PJ_LOG(3, ("pjmsrp_parser_header_status.c", "Failed to parse 'Status' header."));
	}
	
	return hdr_Status;
}