// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Response.h
 *
 *  Created on: 2014/09/07
 *      Author: Junya Namai
 */

#ifndef EMWD_CORE_RESPONSE_H_
#define EMWD_CORE_RESPONSE_H_

#include <map>
#include <string>

namespace Emwd { namespace core {

/**
 * Response class
 */
class Response
{
public:
	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setHeader(const char* key, const char* value) = 0;
	virtual void setHeaders(std::map<const char*, const char*>) = 0;

	/**
	 *
	 * @param code
	 */
	virtual void setStatus(int code) = 0;
	virtual int getStatus(void) = 0;

	/**
	 *
	 * @param key
	 * @return
	 */
	virtual const char* getHeader(const char* key) = 0;
	virtual std::map<const char*, const char*> getHeaders() = 0;

	/**
	 *
	 */
	virtual void setBody(const char* body) = 0;

	/**
	 * Clear response body
	 */
	virtual void clearBody() = 0;

	/**
	 *
	 * @param content
	 */
	virtual void appendBody(const char* content) = 0;

	/**
	 * Append contents to response buffer
	 * @param content
	 * @return
	 */
	Response &operator << (const char* content)
	{
		this->appendBody(content);
		return *this;
	}


	/**
	 *
	 * @return
	 */
	virtual const char* getBody() = 0;

	/**
	 * destructor
	 */
	virtual ~Response()
	{
	}
};

} }

#endif /* EMWD_CORE_RESPONSE_H_ */
