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
	void setHeader(const char* key, const char* value) = 0;
	void setHeaders(std::map<const char*, const char*>) = 0;

	/**
	 *
	 * @param key
	 * @return
	 */
	const char* getHeader(const char* key) = 0;
	std::map<const char*, const char*> getHeaders() = 0;

	/**
	 *
	 */
	void setBody(const char* body) = 0;

	/**
	 *
	 * @return
	 */
	const char* getBody() = 0;
};

} }

#endif /* EMWD_CORE_RESPONSE_H_ */
