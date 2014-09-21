// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ApacheRequest.app
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/ApacheRequest.h>

namespace Emwd { namespace web {

ApacheRequest::ApacheRequest()
{
    ;
}

apr_hash_t* ApacheRequest::parse_form_from_string(request_rec *r, char *args)
{
    apr_hash_t *form;
    apr_array_header_t *values;
    char *pair;
    char *eq;
    const char *delim = "&";
    char *last;
    if (args == NULL) {
        return NULL;
    }

    form = apr_hash_make(r->pool);

    for (pair = apr_strtok(args, delim, &last);
            pair != NULL;
            pair = apr_strtok(NULL, delim, &last)){
        for (eq = pair; *eq; ++eq){
            if(*eq == '+'){
                *eq = ' ';
            }
        }
        eq = strchr(pair, '=');
        if (eq) {
            *eq++ = '\0';
            ap_unescape_url(pair);
            ap_unescape_url(eq);
        }
        else {
            eq = "";
            ap_unescape_url(pair);
        }
        values = (apr_array_header_t*)apr_hash_get(form, pair, APR_HASH_KEY_STRING);
        if (values == NULL) {
            values = apr_array_make(r->pool, 1, sizeof(char*));
            apr_hash_set(form, pair, APR_HASH_KEY_STRING, values);
        }
        *((char **)apr_array_push(values)) = apr_pstrdup(r->pool, eq);
    }

    return form;
}

apr_hash_t * ApacheRequest::parse_form_from_GET(request_rec *r)
{
    return parse_form_from_string(r, r->args);
}

ApacheRequest::ApacheRequest(request_rec *r)
{
    this->_req = r;
    this->_get = NULL;
    this->_get = parse_form_from_GET(this->_req);
}

const char* ApacheRequest::getGet(const char* key)
{
    return (const char*)apr_hash_get(this->_get, key, APR_HASH_KEY_STRING);
}

std::map<const char*, const char*> ApacheRequest::getGets()
{
    return this->_getMap;
}

void ApacheRequest::setGet(const char* key, const char* value)
{
    ;
}

void ApacheRequest::setGets(std::map <const char*, const char*> gets)
{

}

const char* ApacheRequest::getPost(const char* key)
{
    return "empty";
}

std::map<const char*, const char*> ApacheRequest::getPosts()
{
    return this->_getMap;
}

void ApacheRequest::setPost(const char* key, const char *value)
{

}

void ApacheRequest::setPosts(std::map<const char*, const char*> posts)
{
    ;
}

void ApacheRequest::setContentType(const char* type)
{

}

const char* ApacheRequest::getContentType()
{
    return "text/plain";
}

void ApacheRequest::setRequestUrl(const char* url)
{
	;
}

/**
 *
 * @return
 */
const char* ApacheRequest::getRequestUrl()
{
    return this->_req->uri;
}

void ApacheRequest::setStatusCode(int code)
{
    ;
}

/**
 * set request method
 * @param method
 */
void ApacheRequest::setRequestMethod(REQUEST_METHOD method)
{
}

/**
 *
 * @param key
 * @param value
 */
void ApacheRequest::setHeader(const char* key, const char value)
{
    ;
} 

/**
 *
 * @param headers
 */
void ApacheRequest::setHeaders(std::map <const char*, const char*> headers)
{
    ;
}

/**
 *
 * @param key
 * @return
 */
const char* ApacheRequest::getHeader(const char* key)
{
    return NULL;
}

/**
 *
 * @return
 */
std::map <const char*, const char*> ApacheRequest::getHeaders() 
{
    return this->_getMap;
}

/**
 * get request method
 * @return request method enum
 */
Emwd::core::Request::REQUEST_METHOD ApacheRequest::getRequestMethod()
{
    return this->_method;
} 

} }
