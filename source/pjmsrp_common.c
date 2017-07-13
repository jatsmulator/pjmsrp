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
#ifndef PJMSRP_COMMON_C_
#define PJMSRP_COMMON_C_

#include "pjmsrp/pjmsrp_common.h"

PJ_DEF(pj_str_t*) pj_strcreate2(pj_pool_t* pool, const void* data, pj_size_t size) {
	pj_str_t *buffer = PJ_POOL_ALLOC_T(pool, pj_str_t);

	if (size > 0 && data){
		buffer->ptr = (char*)pj_pool_alloc(pool, size);
		buffer->slen = size;
		pj_memcpy(buffer->ptr, data, size);
	} else {
		buffer->ptr = NULL;
		buffer->slen = 0;
	}
	return buffer;
}

PJ_DEF(void) pj_strcreate(pj_pool_t* pool, pj_str_t* dest, const pj_str_t *src) {
	if (!src){
		dest = pj_strcreate2(pool, NULL, 0);
	} else {
		dest = pj_strcreate2(pool, src->ptr, src->slen);
	}
}



PJ_DEF(pj_str_t*) pj_strcreate_null(pj_pool_t* pool) {
	return pj_strcreate2(pool, NULL, 0);
}



PJ_DEF(int) pj_strappend2_v(pj_pool_t* pool, pj_str_t* self, const char* format, ...) {
	/*
	* I suppose that sizeof(char) = 1-byte
	*/
	int len = 0;
	va_list ap;
	char *buffer;
	pj_size_t oldsize;
	va_list ap2;
	pj_str_t tmp;

	if (!self) {
		return -1;
	}

	oldsize = self->slen;
	buffer = (char*)PJ_BUFFER_DATA(self);

	if (oldsize > 0){
		tmp.ptr = (char*)pj_pool_alloc(pool, oldsize);
		pj_memcpy(tmp.ptr, buffer, oldsize);
		tmp.slen = oldsize;
	}

	/* initialize variable arguments (needed for 64bit platforms where vsnprintf will change the va_list) */
	va_start(ap, format);
	va_start(ap2, format);

	len = vsnprintf(NULL, 0, format, ap);
	buffer = (char*)pj_pool_alloc(pool, oldsize + len + 1);

	if(oldsize > 0){
		pj_memcpy(buffer, tmp.ptr, tmp.slen);
	}

	vsnprintf((buffer + oldsize), len
#if !defined(_MSC_VER) || defined(__GNUC__)
		+1
#endif
		, format, ap2);

	/* reset variable arguments */
	va_end(ap);
	va_end(ap2);

	self->ptr = buffer;
	self->slen = (oldsize + len);

	return 0;
}

PJ_DEF(int) pj_strappend2(pj_pool_t* pool, pj_str_t* self, const void* data, pj_size_t size)
{
	if (self && size) {
		pj_size_t oldsize = self->slen;
		pj_size_t newsize = oldsize + size;
		pj_str_t tmp;
		char* buffer;

		if (oldsize) {
			tmp.ptr = pj_pool_alloc(pool, oldsize);
			tmp.slen = oldsize;
			pj_memcpy((void*)tmp.ptr, self->ptr, self->slen);

			self->ptr = pj_pool_alloc(pool, newsize);

			pj_memcpy((void*)self->ptr, tmp.ptr, tmp.slen);//restore data

		}
		else {
			buffer = pj_pool_calloc(pool, size, sizeof(uint8_t));
			self->ptr = buffer;
		}

		if (self->ptr) {
			if (data) {
				pj_memcpy((void*)(PJ_BUFFER_TO_U8(self) + oldsize), data, size);
			}
			self->slen = newsize;
			return 0;
		}
	}
	else {

		PJ_LOG(3, (__FILE__, "Invalid parameter"));
	}
	return -1;
}

PJ_DEF(int) pj_strappend(pj_pool_t* pool, pj_str_t* self, const pj_str_t *src)
{
	if (self && src) {
		pj_size_t oldsize = self->slen;
		pj_size_t newsize = oldsize + src->slen;
		pj_str_t tmp;
		char *buffer;

		if (oldsize) {
			tmp.ptr = pj_pool_alloc(pool, oldsize);
			tmp.slen = oldsize;
			pj_memcpy((void*)tmp.ptr, self->ptr, self->slen);

			self->ptr = pj_pool_alloc(pool, newsize);

			pj_memcpy((void*)self->ptr, tmp.ptr, tmp.slen);//restore data

		}
		else {
			buffer = pj_pool_calloc(pool, src->slen, sizeof(uint8_t));
			self->ptr = buffer;
		}

		if (self->ptr) {
			if (src->ptr) {
				pj_memcpy((void*)(PJ_BUFFER_TO_U8(self) + oldsize), src->ptr, src->slen);
			}
			self->slen = newsize;
			return 0;
		}
	}
	else {
		PJ_LOG(3, (__FILE__, "Invalid parameter"));
	}
	return -1;
}

PJ_DECL(int) pj_str_cpy(pj_pool_t* pool, pj_str_t* self, const void* data, pj_size_t size)
{
	if(self){
		self->slen = 0;
		return pj_strappend2(pool, self, data, size);
	}
	else{
		PJ_LOG(3, (__FILE__, "Invalid parameter"));
		return -1;
	}
}

PJ_DEF(void) pj_strunquote(pj_str_t *pjstr)
{
	char** str = &pjstr->ptr;
	char lquote = '"';
	char rquote = '"';

	if (str && *str) {
		pj_size_t size = pjstr->slen;
		if (size >= 2 && **str == lquote && *((*str) + size - 1) == rquote) {
			memmove((*str), (*str) + 1, (size - 2));
			*((*str) + size - 2) = '\0';
			pjstr->slen = size -2;
		}
	}
}

PJ_DEF(void) pj_strunquote2(char **str, char lquote, char rquote)
{
	if (str && *str) {
		pj_size_t size = strlen(*str);
		if (size >= 2 && **str == lquote && *((*str) + size - 1) == rquote) {
			memmove((*str), (*str) + 1, (size - 2));
			*((*str) + size - 2) = '\0';

		}
	}
}

PJ_DEF(void) pj_itoa(int64_t i, pj_istr_t *result)
{
    memset(result, 0, sizeof(*result));
    sprintf(*result, "%lld", i);
}

PJ_DEF(void) pj_strrandom(pj_pool_t* pool, pj_str_t *result)
{
	pj_str_t random;
	char buf[21];
    static uint64_t __counter = 1;
    pj_time_val now;
    pj_uint64_t msec;

    random.ptr = buf;
    random.slen = sizeof(buf);

    pj_bzero(result, 0);
    pj_memset(buf, 0, sizeof(buf));

    /* Mark start of test. */
    pj_gettimeofday(&now);
    msec = PJ_TIME_VAL_MSEC(now);
    sprintf(buf, "%llu", (msec ^ (rand())) ^ ++__counter);
    pj_strdup(pool, result, &random);
}

/**@ingroup tsk_params_group
*/
PJ_DEF(void) pj_param_init(pj_param_t* param)
{
	pj_bzero(param, sizeof(*param));
}

/**@ingroup tsk_params_group
*/
PJ_DEF(pj_param_t*) pj_param_create(pj_pool_t *pool)
{
	pj_param_t *param = PJ_POOL_ZALLOC_T(pool, pj_param_t);
	pj_param_init(param);
	return param;
}

PJ_DEF(pj_param_t*) pj_param_parse(pj_pool_t *pool, const char* line, pj_size_t size)
{
    if(line && size) {
        const char* start = line;
        const char* end = (line + size);
        const char* equal = strstr(line, "=");
        pj_param_t *param = pj_param_create(pool);

        if (param && equal && equal<end) {
            if ((param->name.ptr = (char*)pj_pool_alloc(pool, (pj_size_t)((equal - start) + 1)))) {
                pj_memcpy(param->name.ptr, start, (equal - start));
                param->name.slen = (equal - start);
            }

            if ((param->value.ptr = (char*)pj_pool_alloc(pool, (pj_size_t)((end - equal - 1) + 1)))) {
            	pj_memcpy(param->value.ptr, equal + 1, (end - equal - 1));
                param->value.slen = (end - equal - 1);
            }
        }
        else if (param) {
            if ((param->name.ptr = (char*)pj_pool_alloc(pool, (pj_size_t)((end - start) + 1)))) {
            	pj_memcpy(param->name.ptr, start, (end - start));
                param->name.slen = (end - start);
            }
        }

        return param;
    }
    return NULL;
}

PJ_DEF(int) pj_params_tostring(pj_pool_t *pool, const pj_param_list_t *self, const char separator, pj_str_t* output)
{
    int ret = -1;

    if(self) {
    	pj_param_list_t *item;
    	item = self->next;
    	ret = 0; // for empty lists
    	while(item != self){
    		pj_param_t param = item->param;
			if((ret = pj_strappend2_v(pool, output, param.value.ptr?"%c%s=%s":"%c%s", separator, param.name.ptr, param.value.ptr))) {
				goto bail;
			}
			item = item->next;
    	}
    }

bail:
    return ret;
}

//PJ_DEF(void) pj_str_alloc(pj_pool_t* pool, pj_str_t *dest, pj_size_t len) {
//	if (!dest || !dest->ptr)
//	{
//		dest->ptr = (char*) pj_pool_alloc(pool, len+1);
//		dest->slen = len;
//		pj_memset(dest->ptr, 0, len);
//	}
//}
//
//PJ_DEF(void) pj_strdup_with_null_alloc(pj_pool_t* pool, pj_str_t *dest, const pj_str_t *src) {
//	pj_str_alloc(pool, dest, src->slen);
//	if (src && src->ptr){
//		pj_memcpy(dest->ptr, src->ptr, src->slen);
//	} else{
//		//do nothing
//	}
//}

#endif /* PJMSRP_COMMON_C_ */
