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
%%{
	machine pjmsrp_machine_parser_header_content_type;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	action tag{
		tag_start = p;
	}

	action parse_value{
		PJMSRP_PARSER_SET_STRING(pool, hdr_ctype->value);
	}

	action parse_param{		
		PJMSRP_PARSER_ADD_PARAM(pool, hdr_ctype->params);
	}	

	m_parameter = (pname (EQUAL pvalue)?)>tag %parse_param;

	m_type = token;
	m_subtype = token;

	media_type = (m_type SLASH m_subtype)@1 >tag %parse_value ((SEMI m_parameter)*)@0;

	Content_Type = ( "Content-Type"i ) HCOLON media_type;
	
	# Entry point
	main := Content_Type :>CRLF?;

}%%


PJ_DEF(pjmsrp_header_content_type_t*) pjmsrp_header_content_type_create(pj_pool_t *pool, pj_str_t* value, pj_param_list_t* params)
{
	pjmsrp_header_content_type_t *contentType = PJ_POOL_ZALLOC_T(pool, pjmsrp_header_content_type_t);
	
	contentType->pool = pool;
	
	if (value == NULL){
		//pj_bzero(&contentType->value, 0);//Allocate memory only
	} else {
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
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_content_type_first_final);
	(void)(pjmsrp_machine_parser_header_content_type_error);
	(void)(pjmsrp_machine_parser_header_content_type_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_content_type.c", "Failed to parse 'Content-Type' header."));
	}
	
	return hdr_ctype;
}