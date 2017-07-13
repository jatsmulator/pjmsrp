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

#ifndef PJMSRP_RAGEL_STATE_H_
#define PJMSRP_RAGEL_STATE_H_

#include "pjmsrp/pjmsrp_config.h"
#include "pjmsrp/pjmsrp_common.h"

PJMSRP_BEGIN_DECLS

#if defined(_MSC_VER)
#	define atoi64	_atoi64
#else
#	define atoi64	atoll
#endif

#if defined(_MSC_VER)
#	define PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN() \
		__pragma(warning( push )) \
		__pragma(warning( disable : 4267 4244 ))
#	define PJMSRP_RAGEL_DISABLE_WARNINGS_END() \
		__pragma(warning( pop ))
#else
#	define PJMSRP_RAGEL_DISABLE_WARNINGS_BEGIN()
#	define PJMSRP_RAGEL_DISABLE_WARNINGS_END()
#endif /* _MSC_VER */

/**@ingroup PJMSRP_ragel_state_group
*/
#define PJMSRP_SCANNER_SET_STRING(pool, string) \
	if(!string) \
		{ \
		int len = (int)(te  - ts);  \
		if(len >0) \
				{ \
			string.ptr = (char*)pj_pool_alloc(pool, len+1);\
			string.slen = len;\
			pj_memcpy(string.ptr, ts, len); \
			string.ptr[len] = '\0'; \
				} \
		}

#define PJMSRP_PARSER_SET_STRING(pool, string) \
	{  \
		int len = (int)(p  - tag_start);  \
		if(len && tag_start){ \
			string.ptr = (char*)pj_pool_alloc(pool, len+1);\
			string.slen = len;\
			pj_memcpy(string.ptr, tag_start, len); \
			string.ptr[len] = '\0'; \
				}  \
	}

/**@ingroup PJMSRP_ragel_state_group, no need to free memory when use fast memory pool
*/
#define PJMSRP_SCANNER_SET_INTEGER(pool, integer) \
	{ \
		int len = (int)(te  - ts); \
		if(len>=0) \
				{ \
			char* tmp = (char*)pj_pool_alloc(pool, len+1); \
			pj_memcpy(tmp, ts, len); \
			integer = atoi(tmp); \
				} \
	}

/**@ingroup PJMSRP_ragel_state_group
*/
#define PJMSRP_PARSER_SET_INTEGER_EX(pool, retval, type, func) \
	{ \
		int len = (int)(p  - tag_start); \
		if(len>=0) \
				{ \
			char* tmp = (char*)pj_pool_alloc(pool, len+1); \
			pj_memcpy(tmp, tag_start, len); \
			retval = (type) func(tmp); \
				} \
	}
/**@ingroup pjmsrp_ragel_state_group
* @def PJMSRP_PARSER_SET_INTEGER
*/
/**@ingroup pjmsrp_ragel_state_group
* @def PJMSRP_PARSER_SET_INT
*/
/**@ingroup pjmsrp_ragel_state_group
* @def PJMSRP_PARSER_SET_UINT
*/
/**@ingroup pjmsrp_ragel_state_group
* @def PJMSRP_PARSER_SET_FLOAT
*/
/**@ingroup pjmsrp_ragel_state_group
* @def PJMSRP_PARSER_SET_DOUBLE
*/
#define PJMSRP_PARSER_SET_INTEGER(pool, retval) PJMSRP_PARSER_SET_INTEGER_EX(pool, retval, int, atoi)
#define PJMSRP_PARSER_SET_INT(pool, retval) PJMSRP_PARSER_SET_INTEGER(pool, retval)
#define PJMSRP_PARSER_SET_UINT(pool, retval) PJMSRP_PARSER_SET_INTEGER_EX(pool, retval, pj_uint32_t, atoi64)
#define PJMSRP_PARSER_SET_FLOAT(pool, retval) PJMSRP_PARSER_SET_INTEGER_EX(pool, retval, float, atof)
#define PJMSRP_PARSER_SET_DOUBLE(pool, retval) PJMSRP_PARSER_SET_INTEGER_EX(pool, retval, double, atof)

/**@ingroup PJMSRP_ragel_state_group
*/
#define PJMSRP_PARSER_ADD_PARAM(pool, dest) \
	{ \
		pj_param_list_t *node; \
		pj_size_t len = (pj_size_t)(p  - tag_start); \
		pj_param_t* param = pj_param_parse(pool, tag_start, len); \
		if(param) \
				{ \
			node = (pj_param_list_t*) PJ_POOL_ZALLOC_T(pool, pj_param_list_t);\
			pj_strdup_with_null(pool, &node->param.name, &param->name);\
			pj_strdup_with_null(pool, &node->param.value, &param->value);\
			pj_list_push_back(&dest, node); \
				} \
	}

/**@ingroup PJMSRP_ragel_state_group
*/
#define PJMSRP_SACANNER_ADD_PARAM(pool, dest) \
	{ \
	    pj_param_list_t *node;\
		int len = (int)(te  - ts); \
		if(len >0) \
				{ \
			pj_param_t *param = pj_param_parse(pool, ts, len); \
			if(param) \
						{ \
			node = (pj_param_list_t*) PJ_POOL_ZALLOC_T(pool, pj_param_list_t);\
			pj_strdup_with_null(pool, &node->param.name, &param->name);\
			pj_strdup_with_null(pool, &node->param.value, &param->value);\
			pj_list_push_back(&dest, &node); \
						} \
				} \
	}

/**@ingroup PJMSRP_ragel_state_group
*/
#define PJMSRP_PARSER_ADD_STRING(pool, dest) \
	{ \
		pj_size_t len = (pj_size_t)(p  - tag_start); \
		pj_str_t str; \
		str.ptr = (char*)pj_pool_calloc(pool, len+1, sizeof(char)), memcpy(str.ptr, tag_start, len); \
		str.slen = len; \
		pj_list_push_back(&dest, ((void**) &str)); \
	}

/**@ingroup PJMSRP_ragel_state_group
* Ragel state.
*/
typedef struct pjmsrp_ragel_state_s {
    pj_int32_t cs; /**< Ragel current state. */
    const pj_char_t *p; /**< Data pointing to the buffer to parse. */
    const pj_char_t *pe; /**< Data end pointer. */
    const pj_char_t *eof; /**< End of the file (in our case data) pointer. */
    const pj_char_t *eoh; /**< End of the headers. */

    const pj_char_t* tag_start; /**< Last tag start position set by ragel machine. */
    const pj_char_t* tag_end; /**< The end of the ragel tag. */
}
pjmsrp_ragel_state_t;


PJ_DECL(void) pjmsrp_ragel_state_init(pjmsrp_ragel_state_t *state, const pj_char_t *data, pj_size_t size);


PJMSRP_END_DECLS

#endif /* PJMSRP_RAGEL_STATE_H_ */
