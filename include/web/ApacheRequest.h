// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ApacheRequest.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_WEB_APACHE_REQUEST_H_
#define EMWD_WEB_APACHE_REQUEST_H_

// Apache headers
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

// Emwd
#include <core/Request.h>
#include <core/Response.h>

namespace Emwd { namespace web {

/**
 * ApacheRequest class
 * create Request class from request_rec
 */
class ApacheRequest : public Emwd::core::Request
{
private:
	std::map <const char*, const char *> _getMap;
	REQUEST_METHOD _method;

	/**
	 * Do not need. Always requires request_req
	 */
    ApacheRequest();

    /**
     * Apache request_rec
     */
    request_rec *_req;

    /**
     * Get parameters
     */
    apr_hash_t *_get;

    /**
     * @param r
     * @param args
     * @return
     */
    apr_hash_t *parse_form_from_string(request_rec *r, char *args);

    /**
     * @param r
     * @return
     */
    apr_hash_t *parse_form_from_GET(request_rec *r);

public:
    ApacheRequest(request_rec *r);

	virtual const char* getGet(const char* key);

	virtual std::map<const char*, const char*> getGets();

	virtual void setGet(const char* key, const char* value);

	virtual void setGets(std::map <const char*, const char*> gets);

	virtual const char* getPost(const char* key);

	virtual std::map<const char*, const char*> getPosts();

	virtual void setPost(const char* key, const char *value);

	virtual void setPosts(std::map<const char*, const char*> posts);

	virtual void setContentType(const char* type);

	virtual const char* getContentType();
	
	virtual void setRequestUrl(const char* url);

	virtual const char* getRequestUrl();

	virtual void setStatusCode(int code);

	virtual void setRequestMethod(REQUEST_METHOD method);

	virtual void setHeader(const char* key, const char value);

	virtual void setHeaders(std::map <const char*, const char*> headers);

	virtual const char* getHeader(const char* key);

	virtual std::map <const char*, const char*> getHeaders();

	virtual REQUEST_METHOD getRequestMethod();
};

} }

#endif /* APACHEREQUEST_H_ */
