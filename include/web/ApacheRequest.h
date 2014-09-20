// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ApacheRequest.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_APACHE_REQUEST_H_
#define EMWD_WEB_APACHE_REQUEST_H_

#include "ap_config.h"
#include "apr.h"
#include "apr_lib.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_want.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_request.h"
#include "http_protocol.h"

#include <core/Request.h>

namespace Emwd { namespace web {

/**
 * ApacheRequest class
 * create Request class from request_rec
 */
class ApacheRequest : public Emwd::core::Request
{
private:
    ApacheRequest() {}
    request_rec *_req;
    apr_hash_t *_get;

    static apr_hash_t *parse_form_from_string(request_rec *r, char *args)
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
            values = apr_hash_get(form, pair, APR_HASH_KEY_STRING);
            if (values == NULL) {
                values = apr_array_make(r->pool, 1, sizeof(char*));
                apr_hash_set(form, pair, APR_HASH_KEY_STRING, values);
            }
            *((char **)apr_array_push(values)) = apr_pstrdup(r->pool, eq);
        }

        return form;
    }

    static apr_hash_t *parse_form_from_GET(request_rec *r)
    {
        return parse_form_from_string(r, r->args);
    }

public:
    ApacheRequest(request_rec *r)
    {
        this->_req = r;
        this->_get = NULL;
        this->_get = parse_form_from_GET(this->_req);
    }

	virtual const char* getGet(const char* key)
	{
        return (const char*)apr_hash_get(this-_get, key, APR_HASH_KEY_STRING);
	}

	virtual void setGet(const char* key, const char* value)
	{

	}

	virtual void setGets(std::map <const char*, const char*> gets)
	{

	}

	virtual const char* getPost(const char* key)
	{
		return "empty";
	}

	virtual void setPost(const char* key, const char *value)
	{

	}

	virtual void setContentType(const char* type)
	{

	}

	virtual const char* getContentType()
	{
		return "text/plain";
	}
	
    /**
	 * set response string such as HTML
	 * @param response contents
	 */
	virtual void setResponse(Response* response)
    {
        ;
    }

	/**
	 * get response string
	 * @return response contents like XML
	 */
	virtual Response* getResponse()
    {
        return NULL;
    } 

	/**
	 * set request method
	 * @param method
	 */
	virtual void setRequestMethod(REQUEST_METHOD method)
    {
    }

	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setHeader(const char* key, const char value)
    {
        ;
    } 

	/**
	 *
	 * @param headers
	 */
	virtual void setHeaders(std::map <const char*, const char*> headers)
    {
        ;
    }

	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getHeader(const char* key)
    {
        return NULL;
    }

	/**
	 *
	 * @return
	 */
	virtual std::map <const char*, const char*> getHeaders() 
    {
        return NULL;
    }

	/**
	 * get request method
	 * @return request method enum
	 */
	virtual REQUEST_METHOD getRequestMethod()
    {
        return NULL;
    } 
};

} }

#endif /* APACHEREQUEST_H_ */
