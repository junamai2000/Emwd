// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * DummyResponse.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_DUMMY_RESPONSE_H_
#define EMWD_WEB_DUMMY_RESPONSE_H_

#include <core/Response.h>

#include <string>
#include <map>

namespace Emwd { namespace web {

/**
 * DummyResponse class
 */
class DummyResponse : public Emwd::core::Response
{
private:
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
	/**
	 *
	 * @param key
	 * @param value
	 */
	virtual void setHeader(const char* key, const char* value);

	virtual void setHeaders(std::map<const char*, const char*> header);

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

	virtual void appendBody(const char* content);

	/**
	 * Clear response body
	 */
	virtual void clearBody();

	/**
	 *
	 * @return
	 */
	virtual const char* getBody();

	virtual  ~DummyResponse();
};

} }

#endif /* EMWD_WEB_DUMMY_RESPONSE_H_ */
