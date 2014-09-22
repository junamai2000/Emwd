// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ApacheResponse.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_APACHE_RESPONSE_H_
#define EMWD_WEB_APACHE_RESPONSE_H_

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

// C++ headers
#include <string>
#include <map>

// Emwd
#include <core/Response.h>

namespace Emwd { namespace web {

/**
 * ApacheResponse class
 */
class ApacheResponse : public Emwd::core::Response
{
private:
	request_rec *_req;

	/**
	 * Http response header
	 */
	std::map <const char*, const char *> _header;

	/**
	 * Http Status Code
	 */
	int _statusCode;

	/**
	 * Output string
	 */
	std::string _output;

public:
	ApacheResponse(request_rec *r);
	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setHeader(const char* key, const char* value);
	virtual void setHeaders(std::map<const char*, const char*> header);

	virtual void setContentType(const char* contentType);
	virtual const char* getContentType();

	/**
	 *
	 * @param code
	 */
	virtual void setStatus(int code);
	virtual int getStatus(void);

	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getHeader(const char* key);

	virtual std::map<const char*, const char*> getHeaders();

	/**
	 *
	 */
	virtual void setBody(const char* body);

	virtual void appendBody(const char* body);

	/**
	 * Clear response body
	 */
	virtual void clearBody();

	/**
	 *
	 * @return
	 */
	virtual const char* getBody();

	virtual  ~ApacheResponse();
};

} }

#endif /* EMWD_WEB_APACHE_RESPONSE_H_ */
