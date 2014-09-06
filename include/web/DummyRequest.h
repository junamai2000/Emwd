/*
 * ApacheRequest.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_DUMMY_REQUEST_H_
#define EMWD_WEB_DUMMY_REQUEST_H_

#include <core/Request.h>

#include <string>
#include <map>

namespace Emwd { namespace web {

/**
 * DummyRequest class
 * Use this class to emulate Http request
 */
class DummyRequest : public Request
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
	 * response contents
	 */
	std::string _response;

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
	virtual const char* getGet(const char* key)
	{
		return this->_get[key];
	}

	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setGet(const char* key, const char* value)
	{
		this->_get[key] = value;
	}

	virtual std::map<const char*, const char*> getGets()
	{
		return this->_get;
	}

	/**
	 *
	 * @param gets
	 */
	virtual void setGets(std::map <const char*, const char*> gets)
	{
		this->_get = gets;
	}

	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getPost(const char* key)
	{
		return this->_post[key];
	}

	/**
	 *
	 * @return
	 */
	virtual std::map<const char*, const char*> getPosts()
	{
		return this->_post;
	}

	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setPost(const char* key, const char *value)
	{
		this->_post[key] = value;
	}

	/**
	 *
	 * @param posts
	 */
	virtual void setPosts(std::map<const char*, const char*> posts)
	{
		this->_post = posts;
	}

	/**
	 *
	 * @param type
	 */
	virtual void setContentType(const char* type)
	{
		this->_contentType = type;
	}

	/**
	 *
	 * @return
	 */
	virtual const char* getContentType()
	{
		return this->_contentType.c_str();
	}

	/**
	 *
	 * @param url
	 */
	virtual void setRequestUrl(const char* url)
	{
		this->_url = url;
	}

	/**
	 *
	 * @return
	 */
	virtual const char* getRequestUrl()
	{
		return this->_url.c_str();
	}

	/**
	 *
	 * @param code
	 */
	virtual void setStatusCode(int code)
	{
		this->_statusCode = code;
	}

	virtual void setResponse(const char* response)
	{
		this->_response = response;
	}

	/**
	 *
	 * @return
	 */
	virtual const char* getResponse()
	{
		return this->_response.c_str();
	}

	/**
	 *
	 * @param method
	 */
	virtual void setRequestMethod(REQUEST_METHOD method)
	{
		this->_method = method;
	}

	/**
	 *
	 * @return request method such as POST, GET
	 */
	virtual REQUEST_METHOD getRequestMethod()
	{
		return this->_method;
	}
};

} }

#endif /* EMWD_WEB_DUMMY_REQUEST_H_ */
