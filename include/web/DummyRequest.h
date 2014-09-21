// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * DummyResponse.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_DUMMY_REQUEST_H_
#define EMWD_WEB_DUMMY_REQUEST_H_

#include <core/Request.h>
#include <core/Response.h>

#include <string>
#include <map>

namespace Emwd { namespace web {

/**
 * DummyRequest class
 * Use this class to emulate Http request
 */
class DummyRequest : public Emwd::core::Request
{
private:
	/**
	 * Get parameters
	 */
	std::map <const char*, const char *> _get;

	/**
	 * Post parameters
	 */
	std::map <const char*, const char *> _post;

	/**
	 * Content type
	 */
	std::string _contentType;

	/**
	 * Url
	 */
	std::string _url;

	/**
	 * http status code
	 */
	int _statusCode;

	/**
	 * request method
	 */
	REQUEST_METHOD _method;

public:
	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getGet(const char* key);

	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setGet(const char* key, const char* value);

	virtual std::map<const char*, const char*> getGets();

	/**
	 *
	 * @param gets
	 */
	virtual void setGets(std::map <const char*, const char*> gets);

	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getPost(const char* key);

	/**
	 *
	 * @return
	 */
	virtual std::map<const char*, const char*> getPosts();

	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setPost(const char* key, const char *value);

	/**
	 *
	 * @param posts
	 */
	virtual void setPosts(std::map<const char*, const char*> posts);

	/**
	 *
	 * @param type
	 */
	virtual void setContentType(const char* type);

	/**
	 *
	 * @return
	 */
	virtual const char* getContentType();

	/**
	 *
	 * @param url
	 */
	virtual void setRequestUrl(const char* url);

	/**
	 *
	 * @return
	 */
	virtual const char* getRequestUrl();

	/**
	 *
	 * @param code
	 */
	virtual void setStatusCode(int code);

	/**
	 *
	 * @param method
	 */
	virtual void setRequestMethod(REQUEST_METHOD method);

	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setHeader(const char* key, const char value);

	/**
	 *
	 * @param headers
	 */
	virtual void setHeaders(std::map<const char*, const char*> headers);

	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getHeader(const char* key);

	/**
	 *
	 * @return
	 */
	virtual std::map<const char*, const char*> getHeaders();

	/**
	 *
	 * @return request method such as POST, GET
	 */
	virtual REQUEST_METHOD getRequestMethod();

	~DummyRequest();
};

} }

#endif /* EMWD_WEB_DUMMY_REQUEST_H_ */
