// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
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

class Response;

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

	virtual void setResponse(Emwd::core::Response* response)
	{
		;
	}

	/**
	 *
	 * @return
	 */
	virtual Emwd::core::Response* getResponse()
	{
		return NULL;
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
	virtual void setHeaders(std::map<const char*, const char*> headers)
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
		return "not implemented yet";
	}

	/**
	 *
	 * @return
	 */
	virtual std::map<const char*, const char*> getHeaders()
	{
		std::map<const char*, const char*> dummy;
		dummy["not implemented yet"] = "not implemented yet";
		return dummy;
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
