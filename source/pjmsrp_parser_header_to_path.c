
/* #line 1 "./ragel/pjmsrp_parser_header_to_path.rl" */
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
 
/**@file pjmsrp_parser_header_to_path.rl
 * @brief MSRP "To-Path" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 #include "pjmsrp/pjmsrp_header_to_path.h"
 
 /***********************************
*	Ragel state machine.
*/


/* #line 71 "./ragel/pjmsrp_parser_header_to_path.rl" */


PJ_DEF(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_to_path_create(pool, NULL, NULL);
}

PJ_DEF(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_create(pj_pool_t *pool,const pjmsrp_uri_t* uri, const pjmsrp_uris_list_t* otherURIs)
{
	pjmsrp_header_to_path_t *to_path = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_to_path_t);
	
	to_path->uri = PJ_POOL_ZALLOC_T(pool, pjmsrp_uri_t);
	to_path->pool = pool;
	
	if(uri){
		pjmsrp_header_to_path_assign(pool, &to_path->uri, uri);
	}
	
	pj_list_init(&to_path->otherURIs);
	if (otherURIs){
		to_path->otherURIs = *otherURIs;
	}

	return to_path;
}

PJ_DEF(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_clone(pj_pool_t *pool, const pjmsrp_header_to_path_t *to_path)
{
	pjmsrp_header_to_path_t *new_to_path;
	pj_status_t status;
	
	if (!to_path)	{
		return NULL;
	}

	new_to_path = pjmsrp_header_to_path_create_default(pool);
	status = pjmsrp_header_to_path_assign(pool, new_to_path, to_path);

	return (status==PJ_SUCCESS) ? new_to_path : NULL;	
}

PJ_DEF(pj_status_t) pjmsrp_header_to_path_assign(pj_pool_t *pool, pjmsrp_header_to_path_t *newFromPath, const pjmsrp_header_to_path_t *rhs)
{
	
	pjmsrp_uri_assign(pool, newFromPath->uri, rhs->uri);
	
	
	return PJ_SUCCESS;
}

PJ_DEF(int) pjmsrp_header_to_path_tostring(const pjmsrp_header_to_path_t* to_path, pj_str_t* output)
{
	if(to_path){
		if(to_path->uri){
			pjmsrp_uri_serialize(to_path->uri, output);
		}
		
		if (!pj_list_empty(&to_path->otherURIs)){
			pj_strappend2(to_path->pool, output, " ", 1);
			pjmsrp_uri_serialize(PJMSRP_URI(&to_path->otherURIs), output);
		}
	}

	return -1;
}


PJ_DEF(pjmsrp_header_to_path_t*) pjmsrp_header_to_path_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	pj_int32_t cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_to_path_t *header = pjmsrp_header_to_path_create_default(pool);

	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	
/* #line 118 "./src/pjmsrp_parser_header_to_path.c" */
static const char _pjmsrp_machine_parser_header_to_path_actions[] = {
	0, 1, 0, 1, 1, 2, 0, 1
	
};

static const char _pjmsrp_machine_parser_header_to_path_key_offsets[] = {
	0, 0, 2, 4, 5, 7, 9, 11, 
	13, 14, 15, 16, 18, 20
};

static const char _pjmsrp_machine_parser_header_to_path_trans_keys[] = {
	84, 116, 79, 111, 45, 80, 112, 65, 
	97, 84, 116, 72, 104, 58, 32, 10, 
	13, 32, 13, 32, 0
};

static const char _pjmsrp_machine_parser_header_to_path_single_lengths[] = {
	0, 2, 2, 1, 2, 2, 2, 2, 
	1, 1, 1, 2, 2, 0
};

static const char _pjmsrp_machine_parser_header_to_path_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const char _pjmsrp_machine_parser_header_to_path_index_offsets[] = {
	0, 0, 3, 6, 8, 11, 14, 17, 
	20, 22, 24, 26, 29, 32
};

static const char _pjmsrp_machine_parser_header_to_path_trans_targs[] = {
	2, 2, 0, 3, 3, 0, 4, 0, 
	5, 5, 0, 6, 6, 0, 7, 7, 
	0, 8, 8, 0, 9, 0, 11, 0, 
	13, 0, 10, 11, 12, 10, 11, 12, 
	0, 0
};

static const char _pjmsrp_machine_parser_header_to_path_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 5, 5, 1, 3, 3, 0, 
	0, 0
};

static const char _pjmsrp_machine_parser_header_to_path_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 5, 3, 0
};

static const int pjmsrp_machine_parser_header_to_path_start = 1;
static const int pjmsrp_machine_parser_header_to_path_first_final = 11;
static const int pjmsrp_machine_parser_header_to_path_error = 0;

static const int pjmsrp_machine_parser_header_to_path_en_main = 1;


/* #line 150 "./ragel/pjmsrp_parser_header_to_path.rl" */
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_to_path_first_final);
	(void)(pjmsrp_machine_parser_header_to_path_error);
	(void)(pjmsrp_machine_parser_header_to_path_en_main);
	
/* #line 184 "./src/pjmsrp_parser_header_to_path.c" */
	{
	cs = pjmsrp_machine_parser_header_to_path_start;
	}

/* #line 155 "./ragel/pjmsrp_parser_header_to_path.rl" */
	
/* #line 191 "./src/pjmsrp_parser_header_to_path.c" */
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
	_keys = _pjmsrp_machine_parser_header_to_path_trans_keys + _pjmsrp_machine_parser_header_to_path_key_offsets[cs];
	_trans = _pjmsrp_machine_parser_header_to_path_index_offsets[cs];

	_klen = _pjmsrp_machine_parser_header_to_path_single_lengths[cs];
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

	_klen = _pjmsrp_machine_parser_header_to_path_range_lengths[cs];
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
	cs = _pjmsrp_machine_parser_header_to_path_trans_targs[_trans];

	if ( _pjmsrp_machine_parser_header_to_path_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _pjmsrp_machine_parser_header_to_path_actions + _pjmsrp_machine_parser_header_to_path_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 42 "./ragel/pjmsrp_parser_header_to_path.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 46 "./ragel/pjmsrp_parser_header_to_path.rl" */
	{
		pj_int32_t len = (pj_int32_t)(p  - tag_start);
		pjmsrp_uri_t* uri;
		pjmsrp_uris_list_t* uriList;
		if((uri = pjmsrp_uri_parse(pool, tag_start, (pj_size_t)len))){
			//TODO check if uri is NULL, may be incorrect now.
			if(header->uri->scheme.slen <= 0){
				header->uri = uri;
			}
			else{
				uriList = PJ_POOL_ZALLOC_T(pool, pjmsrp_uris_list_t);
				uriList->uri = *uri;
				pj_list_push_back(&header->otherURIs, uriList);
			}
		}
	}
	break;
/* #line 289 "./src/pjmsrp_parser_header_to_path.c" */
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
	const char *__acts = _pjmsrp_machine_parser_header_to_path_actions + _pjmsrp_machine_parser_header_to_path_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
/* #line 42 "./ragel/pjmsrp_parser_header_to_path.rl" */
	{
		tag_start = p;
	}
	break;
	case 1:
/* #line 46 "./ragel/pjmsrp_parser_header_to_path.rl" */
	{
		pj_int32_t len = (pj_int32_t)(p  - tag_start);
		pjmsrp_uri_t* uri;
		pjmsrp_uris_list_t* uriList;
		if((uri = pjmsrp_uri_parse(pool, tag_start, (pj_size_t)len))){
			//TODO check if uri is NULL, may be incorrect now.
			if(header->uri->scheme.slen <= 0){
				header->uri = uri;
			}
			else{
				uriList = PJ_POOL_ZALLOC_T(pool, pjmsrp_uris_list_t);
				uriList->uri = *uri;
				pj_list_push_back(&header->otherURIs, uriList);
			}
		}
	}
	break;
/* #line 330 "./src/pjmsrp_parser_header_to_path.c" */
		}
	}
	}

	_out: {}
	}

/* #line 156 "./ragel/pjmsrp_parser_header_to_path.rl" */
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < 11 ){
		PJ_LOG(3, ("pjmsrp_parser_header_to_path.c", "Failed to parse MSRP/MSRPS header."));
	}
	
	return header;
}