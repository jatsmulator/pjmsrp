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
#ifndef PJMSRP_COMMON_H_
#define PJMSRP_COMMON_H_

#include "pjmsrp/pjmsrp_config.h"

PJMSRP_BEGIN_DECLS

typedef char pj_istr_t[21]; /**< Integer number as string value. */

typedef struct pj_params_s{
    pj_str_t name;/**< The name of the parameter. */
    pj_str_t value;/**< The value of the parameter. */
}pj_param_t;

typedef struct pj_param_list_s{
	PJ_DECL_LIST_MEMBER(struct pj_param_list_s);
	pj_param_t param;
}pj_param_list_t;

#define PJ_BUFFER(self)					((pj_str_t*)self)
#define PJ_BUFFER_DATA(self)				(self ? PJ_BUFFER(self)->ptr : NULL)
#define PJ_BUFFER_SIZE(self)				(self ? PJ_BUFFER(self)->slen : 0)
#define PJ_BUFFER_TO_STRING(self)			(self ? (const char*)PJ_BUFFER_DATA(self) : NULL)
#define PJ_BUFFER_TO_U8(self)				(self ? (uint8_t*)PJ_BUFFER_DATA(self) : NULL)

PJ_DECL(void) 	   pj_strcreate(pj_pool_t* pool, pj_str_t* dest, const pj_str_t *src);
PJ_DECL(pj_str_t*) pj_strcreate_null(pj_pool_t* pool);
PJ_DECL(pj_str_t*) pj_strcreate2(pj_pool_t* pool, const void* data, pj_size_t size);

PJ_DECL(int) pj_strappend2_v(pj_pool_t* pool, pj_str_t* self, const char* format, ...);
PJ_DECL(int) pj_strappend2(pj_pool_t* pool, pj_str_t* self, const void* data, pj_size_t size);
PJ_DECL(int) pj_strappend(pj_pool_t* pool, pj_str_t* self, const pj_str_t *src);
PJ_DECL(int) pj_str_cpy(pj_pool_t* pool, pj_str_t* self, const void* data, pj_size_t size);

PJ_DECL(void) pj_strunquote(pj_str_t *pjstr);
PJ_DECL(void) pj_strunquote2(char **str, char lquote, char rquote);
PJ_DECL(void) pj_itoa(int64_t i, pj_istr_t *result);
PJ_DECL(void) pj_strrandom(pj_pool_t* pool, pj_str_t *result);

PJ_DECL(void) pj_param_init(pj_param_t* param);
PJ_DECL(pj_param_t*) pj_param_create(pj_pool_t *pool);
PJ_DECL(pj_param_t*) pj_param_parse(pj_pool_t *pool, const char* line, pj_size_t size);
PJ_DECL(int) pj_params_tostring(pj_pool_t *pool, const pj_param_list_t *self, const char separator, pj_str_t* output);

#define PJ_STR_INIT_NULL(string)\
	string.ptr = NULL;\
	string.slen = 0;

PJMSRP_END_DECLS

#endif /* PJMSRP_COMMON_H_ */
