// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Request.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_CORE_REQUEST_H_
#define EMWD_CORE_REQUEST_H_

#include <map>

namespace Emwd { namespace core {

/**
 * Request class
 */
class Request
{
public:
	/**
	 * Request Method
	 * do not use string, converts into enum under a oncrete class
	 */
	enum REQUEST_METHOD {R_GET=1, R_POST, R_PUT, R_DELETE, R_UPDATE};

	/**
	 * get a Get param from http request
	 * @param key
	 * @return value
	 */
	virtual const char* getGet(const char* key) = 0;

	/**
	 * set Get requests
	 * @return get parameters by using std::map
	 */
	virtual std::map <const char*, const char*> getGets() = 0;

	/**
	 * set a Get param from http request
	 * @param key get name
	 * @param value get value
	 */
	virtual void setGet(const char* key, const char* value) = 0;

	/**
	 * set Get parameters
	 * @param gets map object which contains all get parameters
	 */
	virtual void setGets(std::map <const char*, const char*> gets) = 0;

	/**
	 * get a Post param from http request
	 * @param key
	 * @return value
	 */
	virtual const char* getPost(const char* key) = 0;

	/**
	 * set Posts requests
	 * @return post parameters with std::map
	 */
	virtual std::map <const char*, const char*> getPosts() = 0;

	/**
	 * set a Post param from http request
	 * @param key get name
	 * @param value get value
	 */
	virtual void setPost(const char* key, const char *value) = 0;

	/**
	 * set Post parameters
	 * @param Posts map object which contains all Post parameters
	 */
	virtual void setPosts(std::map <const char*, const char*> gets) = 0;

	/**
	 * set content type
	 * @param type ex: text/plain
	 */
	virtual void setContentType(const char* type) = 0;

	/**
	 * get contents type
	 * @return content type header
	 */
	virtual const char* getContentType() = 0;

	/**
	 * set request url
	 * @param url
	 */
	virtual void setRequestUrl(const char* url) = 0;

	/**
	 * get request url
	 * @return
	 */
	virtual const char* getRequestUrl() = 0;

	/**
	 * set status code
	 * ex: 404, 503 etc....
	 * @param http status code
	 */
	virtual void setStatusCode(int code) = 0;

	/**
	 * set response string such as HTML
	 * @param response contents
	 */
	virtual void setResponse(const char* response) = 0;

	/**
	 * get response string
	 * @return response contents like XML
	 */
	virtual const char* getResponse() = 0;

	/**
	 * set request method
	 * @param method
	 */
	virtual void setRequestMethod(REQUEST_METHOD method) = 0;

	/**
	 * get request method
	 * @return request method enum
	 */
	virtual REQUEST_METHOD getRequestMethod() = 0;

	/**
	 * destructor
	 */
	virtual ~Request()
	{
	}
};

} }

#endif /* EMWD_CORE_REQUEST_H_ */
