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

%%{

	machine pjmsrp_machine_parser_header_message_id;

	# Includes
	include pjmsrp_machine_utils "pjmsrp_machine_utils.rl";
	
	
	action tag{
		tag_start = p;
	}

	action parse_id{
		PJMSRP_PARSER_SET_STRING(pool, hdr_Message_Id->value);
	}
	
	#// "Message-ID:" SP ident  
	Message_Id = "Message-ID:"i SP ident>tag %parse_id;
	
	# Entry point
	main := Message_Id :>CRLF?;
	
}%%


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
	%%write data;
	(void)(eof);
	(void)(pjmsrp_machine_parser_header_message_id_first_final);
	(void)(pjmsrp_machine_parser_header_message_id_error);
	(void)(pjmsrp_machine_parser_header_message_id_en_main);
	%%write init;
	%%write exec;
	PJMSRP_RAGEL_DISABLE_WARNINGS_END()

	if( cs < %%{ write first_final; }%% ){
		PJ_LOG(3, ("pjmsrp_parser_header_message_id.c", "Failed to parse 'Message-Id' header."));
	}
	
	return hdr_Message_Id;
}