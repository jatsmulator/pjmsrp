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
 
/**@file pjmsrp_parser_header_Use_Path.rl
 * @brief MSRP "Use-Path" header.
 *
 * @author John Li <jatsmulator(at)gmail.com>
 *
 */
 
 #include "pjmsrp/pjmsrp_header_use_path.h"
 
 /***********************************
*	Ragel state machine.
*/

%%{

	machine pjmsrp_machine_parser_header_use_path;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	
	action tag{
		tag_start = p;
	}

	action parse_uri{
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
		
	MSRP_URI = (any -- SP)* >tag %parse_uri;

	#//"Use-Path:" SP MSRP-URI  *( SP MSRP-URI ) 
	Use_Path = "Use-Path:"i SP MSRP_URI (SP <:MSRP_URI)*;
	
	# Entry point
	main := Use_Path :>CRLF?;
	
}%%

PJ_DEF(pjmsrp_header_use_path_t*) pjmsrp_header_use_path_create_default(pj_pool_t *pool)
{
	return pjmsrp_header_use_path_create(pool, NULL, NULL);
}

PJ_DEF(pjmsrp_header_use_path_t*) pjmsrp_header_use_path_create(pj_pool_t *pool,const pjmsrp_uri_t* uri, const pjmsrp_uris_list_t* otherURIs)
{
	pjmsrp_header_use_path_t *use_path = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_use_path_t);
	
	use_path->uri = PJ_POOL_ZALLOC_T(pool, pjmsrp_uri_t);
	use_path->pool = pool;
	
	if(uri){
		pjmsrp_header_use_path_assign(pool, &use_path->uri, uri);
	}
	
	pj_list_init(&use_path->otherURIs);
	if (otherURIs){
		use_path->otherURIs = *otherURIs;
	}

	return use_path;	
}

PJ_DEF(pjmsrp_header_use_path_t*) pjmsrp_header_use_path_clone(pj_pool_t *pool, const pjmsrp_header_use_path_t *use_path)
{
	pjmsrp_header_use_path_t *new_use_path;
	pj_status_t status;
	
	if (!use_path)	{
		return NULL;
	}

	new_use_path = pjmsrp_header_use_path_create_default(pool);
	status = pjmsrp_header_use_path_assign(pool, new_use_path, use_path);

	return (status==PJ_SUCCESS) ? new_use_path : NULL;	
}

PJ_DEF(pj_status_t) pjmsrp_header_use_path_assign(pj_pool_t *pool, pjmsrp_header_use_path_t *newFromPath, const pjmsrp_header_use_path_t *rhs)
{
	
	pjmsrp_uri_assign(pool, newFromPath->uri, rhs->uri);
	
	
	return PJ_SUCCESS;
}

PJ_DEF(int) pjmsrp_header_use_path_tostring(const pjmsrp_header_use_path_t* use_path, pj_str_t* output)
{
	if(use_path){
		if(use_path->uri){
			pjmsrp_uri_serialize(use_path->uri, output);
		}
		
		if (!pj_list_empty(&use_path->otherURIs)){
			pj_strappend2(use_path->pool, output, " ", 1);
			pjmsrp_uri_serialize(PJMSRP_URI(&use_path->otherURIs), output);
		}
	}

	return -1;
}

PJ_DEF(pjmsrp_header_use_path_t*) pjmsrp_header_use_path_parse(pj_pool_t *pool, const char *data, pj_size_t size)
{
	pj_int32_t cs = 0;
	const char *p = data;
	const char *pe = p + size;
	const char *eof = pe;
	pjmsrp_header_use_path_t *header = pjmsrp_header_use_path_create_default(pool);

	const char *tag_start = NULL;

	PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_use_path_first_final);
	(void)(pjmsrp_machine_parser_header_use_path_error);
	(void)(pjmsrp_machine_parser_header_use_path_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()
	
	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_use_path.c", "Failed to parse MSRP/MSRPS header."));
	}
	
	return header;
}