
/* #line 1 "./ragel/pjmsrp_parser_header_failure_report.rl" */
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


/* #line 60 "./ragel/pjmsrp_parser_header_failure_report.rl" */


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
	
/* #line 77 "./src/pjmsrp_parser_header_failure_report.c" */
static const char _pjmsrp_machine_parser_header_failure_report_actions[] = {
	0, 1, 0, 1, 1, 1, 2
};

static const char _pjmsrp_machine_parser_header_failure_report_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	14, 15, 17, 19, 21, 23, 25, 27, 
	28, 29, 35, 37, 38, 40, 42, 44, 
	46, 48, 50, 52, 54, 55, 55, 56
};

static const char _pjmsrp_machine_parser_header_failure_report_trans_keys[] = {
	70, 102, 65, 97, 73, 105, 76, 108, 
	85, 117, 82, 114, 69, 101, 45, 82, 
	114, 69, 101, 80, 112, 79, 111, 82, 
	114, 84, 116, 58, 32, 78, 80, 89, 
	110, 112, 121, 79, 111, 10, 65, 97, 
	82, 114, 84, 116, 73, 105, 65, 97, 
	76, 108, 69, 101, 83, 115, 13, 13, 
	13, 0
};

static const char _pjmsrp_machine_parser_header_failure_report_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 2, 
	1, 2, 2, 2, 2, 2, 2, 1, 
	1, 6, 2, 1, 2, 2, 2, 2, 
	2, 2, 2, 2, 1, 0, 1, 1
};

static const char _pjmsrp_machine_parser_header_failure_report_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0
};

static const char _pjmsrp_machine_parser_header_failure_report_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18, 
	21, 23, 26, 29, 32, 35, 38, 41, 
	43, 45, 52, 55, 57, 60, 63, 66, 
	69, 72, 75, 78, 81, 83, 84, 86
};

static const char _pjmsrp_machine_parser_header_failure_report_indicies[] = {
	0, 0, 1, 2, 2, 1, 3, 3, 
	1, 4, 4, 1, 5, 5, 1, 6, 
	6, 1, 7, 7, 1, 8, 1, 9, 
	9, 1, 10, 10, 1, 11, 11, 1, 
	12, 12, 1, 13, 13, 1, 14, 14, 
	1, 15, 1, 16, 1, 17, 18, 19, 
	17, 18, 19, 1, 20, 20, 1, 21, 
	1, 22, 22, 1, 23, 23, 1, 24, 
	24, 1, 25, 25, 1, 26, 26, 1, 
	27, 27, 1, 28, 28, 1, 29, 29, 
	1, 30, 1, 1, 31, 1, 32, 1, 
	0
};

static const char _pjmsrp_machine_parser_header_failure_report_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 15, 16, 
	17, 18, 20, 26, 28, 29, 21, 22, 
	23, 24, 25, 30, 27, 31, 19, 19, 
	19
};

static const char _pjmsrp_machine_parser_header_failure_report_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 3, 5, 
	1
};

static const char _pjmsrp_machine_parser_header_failure_report_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 3, 0, 5, 1
};

static const int pjmsrp_machine_parser_header_failure_report_start = 1;
static const int pjmsrp_machine_parser_header_failure_report_first_final = 28;
static const int pjmsrp_machine_parser_header_failure_report_error = 0;

static const int pjmsrp_machine_parser_header_failure_report_en_main = 1;


/* #line 97 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_failure_report_first_final);
	(void)(pjmsrp_machine_parser_header_failure_report_error);
	(void)(pjmsrp_machine_parser_header_failure_report_en_main);
	
/* #line 172 "./src/pjmsrp_parser_header_failure_report.c" */
	{
	cs = pjmsrp_machine_parser_header_failure_report_start;
	}

/* #line 102 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	
/* #line 179 "./src/pjmsrp_parser_header_failure_report.c" */
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
	_keys = _pjmsrp_machine_parser_header_failure_report_trans_keys + _pjmsrp_machine_parser_header_failure_report_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_failure_report_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_failure_report_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_failure_report_range_lengths[cs];
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
	_trans = _pjmsrp_machine_parser_header_failure_report_indicies[_trans];
	cs = _pjmsrp_machine_parser_header_failure_report_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_failure_report_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_failure_report_actions + _pjmsrp_machine_parser_header_failure_report_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 42 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	{
		hdr_Failure_Report->type = freport_yes;
	}
	break;
	case 1:
/* #line 46 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	{
		hdr_Failure_Report->type = freport_no;
	}
	break;
	case 2:
/* #line 50 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	{
		hdr_Failure_Report->type = freport_partial;
	}
	break;
/* #line 271 "./src/pjmsrp_parser_header_failure_report.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_failure_report_actions + _pjmsrp_machine_parser_header_failure_report_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
/* #line 42 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	{
		hdr_Failure_Report->type = freport_yes;
	}
	break;
	case 1:
/* #line 46 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	{
		hdr_Failure_Report->type = freport_no;
	}
	break;
	case 2:
/* #line 50 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	{
		hdr_Failure_Report->type = freport_partial;
	}
	break;
/* #line 305 "./src/pjmsrp_parser_header_failure_report.c" */
		}
	}
	}

	_out: {}
	}

/* #line 103 "./ragel/pjmsrp_parser_header_failure_report.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < 28 ){
		PJ_LOG(3, ("pjmsrp_parser_header_failure_report.c", "Failed to parse 'failure-Report' header."));
	}
	
	return hdr_Failure_Report;
}