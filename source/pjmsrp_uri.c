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

#include "pjmsrp/pjmsrp_uri.h"


PJ_DEF(void) pjmsrp_uri_init(pjmsrp_uri_t* uri)
{
	PJ_STR_INIT_NULL(uri->scheme);
	PJ_STR_INIT_NULL(uri->scheme);
	PJ_STR_INIT_NULL(uri->session_id);
	uri->authority.port = -1;
	uri->authority.host_type = pjmsrp_host_unknown;
	PJ_STR_INIT_NULL(uri->authority.host);
	PJ_STR_INIT_NULL(uri->authority.userinfo);

	pj_list_init(&uri->params);
}

PJ_DEF(pjmsrp_uri_t*) pjmsrp_uri_create(pj_pool_t *pool)
{
	pjmsrp_uri_t *uri = PJ_POOL_ALLOC_T(pool, pjmsrp_uri_t);

	uri->pool = pool;
	pjmsrp_uri_init(uri);

	return uri;
}

PJ_DEF(pjmsrp_uri_t*) pjmsrp_uri_clone(pj_pool_t *pool, const pjmsrp_uri_t *uri)
{

	pjmsrp_uri_t *new_uri;
	pj_status_t status;

	new_uri = pjmsrp_uri_create(pool);
	//PJ_ASSERT_RETURN(new_uri, NULL);

	status = pjmsrp_uri_assign(pool, new_uri, uri);

	return (status==PJ_SUCCESS) ? new_uri : NULL;
}

PJ_DEF(pj_status_t) pjmsrp_uri_assign(pj_pool_t *pool, pjmsrp_uri_t *uri,
		const pjmsrp_uri_t *rhs)
{
	uri->pool = rhs->pool;

	if (rhs->scheme.slen > 0)
		pj_strcreate(pool, &uri->scheme, &rhs->scheme);

	if (rhs->authority.host.slen > 0)
		pj_strcreate(pool, &uri->authority.host, &rhs->authority.host);

	uri->authority.host_type = rhs->authority.host_type;
	uri->authority.port = rhs->authority.port;

	if (rhs->authority.userinfo.slen > 0)
		pj_strcreate(pool, &uri->authority.userinfo, &rhs->authority.userinfo);

	if (rhs->session_id.slen > 0)
		pj_strcreate(pool, &uri->session_id, &rhs->session_id);
	
	if (rhs->transport.slen > 0)
		pj_strcreate(pool, &uri->transport, &rhs->transport);

	pjmsrp_uri_param_clone(pool, &uri->params, &rhs->params);

	return PJ_SUCCESS;
}

PJ_DEF(void) pjmsrp_uri_param_clone(pj_pool_t *pool, pj_param_list_t *dst_list,
	const pj_param_list_t *src_list)
{
	const pj_param_list_t *p = src_list->next;

	pj_list_init(dst_list);
	while (p && p != src_list)
	{
		pj_param_t *new_param = PJ_POOL_ALLOC_T(pool, pj_param_t);
		pj_strdup(pool, &new_param->name, &p->param.name);
		pj_strdup(pool, &new_param->value, &p->param.value);
		pj_list_insert_before(dst_list, new_param);
		p = p->next;
	}
}

PJ_DEF(void) pjmsrp_uri_param_shallow_clone(pj_pool_t *pool, pj_param_list_t *dst_list,
	const pj_param_list_t *src_list)
{
	const pj_param_list_t *p = src_list->next;

	pj_list_init(dst_list);
	while (p != src_list)
	{
		pj_param_t *new_param = PJ_POOL_ALLOC_T(pool, pj_param_t);
		new_param->name = p->param.name;
		new_param->value = p->param.value;
		pj_list_insert_before(dst_list, new_param);
		p = p->next;
	}
}

PJ_DEF(void) pjmsrp_uri_list_clone(pj_pool_t *pool, pjmsrp_uris_list_t *dst_uris,
	const pjmsrp_uris_list_t *src_uris)
{
	const pjmsrp_uris_list_t *p = src_uris->next;

	pj_list_init(dst_uris);
	while (p && p != src_uris)
	{
		pjmsrp_uri_t *new_uri = pjmsrp_uri_clone(pool, &p->uri);
		pj_list_insert_before(dst_uris, new_uri);
		p = p->next;
	}
}

PJ_DEF(int) pjmsrp_uri_serialize(const pjmsrp_uri_t *uri, pj_str_t *output)
{
    pj_istr_t port;
    if(!uri || !output) {
        return -1;
    }

    if(uri->authority.port >= 0) {
        pj_itoa(uri->authority.port, &port);
    }

    /* msrp://atlanta.example.com:7654/jshA7weztas;tcp
    * msrp-scheme  "://" authority  ["/" session-id] ";" transport  *( ";" URI-parameter)
    * authority	=  	[ userinfo  "@" ]   host    [ ":"   port ]
    */
    pj_strappend2_v(uri->pool, output, "%s://%s%s%s%s%s%s%s%s%s;%s",
                        // scheme
                        uri->scheme.ptr,
                        // authority
                        uri->authority.userinfo.ptr ? uri->authority.userinfo.ptr : "",
                        uri->authority.userinfo.ptr ? "@" : "",
                        uri->authority.host_type == pjmsrp_host_ipv6 ? "[" : "",
                        uri->authority.host.ptr,
                        uri->authority.host_type == pjmsrp_host_ipv6 ? "]" : "",
                        uri->authority.port >= 0 ? ":" : "",
                        uri->authority.port >= 0 ? port : "",

                        // session-id
                        uri->session_id.ptr ? "/" : "",
                        uri->session_id.ptr ? uri->session_id.ptr : "",

                        // transport
                        uri->transport.ptr
                       );

    /* Params */
    if(!pj_list_empty(&uri->params)) {
        pj_params_tostring(uri->pool, &uri->params, ';', output);
    }

    return 0;
}

PJ_DEF(pj_str_t*) pjmsrp_uri_tostring(const pjmsrp_uri_t *uri)
{
    pj_str_t* output = pj_strcreate_null(uri->pool);
    pj_str_t* ret = pj_strcreate_null(uri->pool);

    if(!pjmsrp_uri_serialize(uri, output)) {
    	pj_strdup(uri->pool, ret, output);
    }
    else {
        //PJ_DEBUG_ERROR("Failed to serialize URI.");
    }

    return ret;
}

//PJ_DEF(int) pjmsrp_uri_tostring(const pjmsrp_uri_t *uri, char *buf, pj_size_t len) {
//	int printed;
//	char port[6];
//	char *p = buf;
//	pj_param_list_t *it;
//
//	if(!uri || !buf || !len){
//		return 0;
//	}
//
//    if(uri->authority.port >= 0) {
//    	pj_utoa(uri->authority.port, port);
//    }
//
//    pj_memcpy(p, uri->scheme.ptr, uri->scheme.slen);
//    p += uri->scheme.slen;
//    *p++ = ':';
//    *p++ = '/';
//    *p++ = '/';
//
//	if (uri->authority.userinfo.slen >0){
//		pj_memcpy(p, uri->authority.userinfo.ptr, uri->authority.userinfo.slen);
//	    p += uri->authority.userinfo.slen;
//	    *p++ = '@';
//	}
//
//	if (uri->authority.host_type == pjmsrp_host_ipv6){
//		*p++ = '[';
//		pj_memcpy(p, uri->authority.host.ptr, uri->authority.host.slen);
//	    p += uri->authority.host.slen;
//	    *p++ = ']';
//	} else {
//		pj_memcpy(p, uri->authority.host.ptr, uri->authority.host.slen);
//	    p += uri->authority.host.slen;
//	}
//
//	if(uri->authority.port >= 0) {
//		*p++ = ':';
//		pj_memcpy(p, port, strlen(port));
//	    p += strlen(port);;
//	}
//
//	if(uri->session_id.slen > 0) {
//		*p++ = '/';
//		pj_memcpy(p, uri->session_id.ptr, uri->session_id.slen);
//	    p += uri->session_id.slen;
//	}
//
//	*p++ = ';';
//	pj_memcpy(p, uri->transport.ptr, uri->transport.slen);
//    p += uri->transport.slen;
//    *p++ = ';';
//
//    if (!pj_list_empty(&uri->params)){
//    	it = uri->params.next;
//    	 while (it != &uri->params) {
//    		 pj_memcpy(p, it->param.name.ptr, it->param.name.slen);
//			 p += it->param.name.slen;
//    		 *p++ = '=';
//    		 pj_memcpy(p, it->param.value.ptr, it->param.value.slen);
//			 p += it->param.value.slen;
//    		 *p++ = ';';
//    		 it = it->next;
//    	 }
//    }
//
//    printed = p-buf;
//
//    if (printed > 0 && len-printed >= 1) {
//    	buf[printed++] = '\0';
//    }
//
//    return printed;
//}
