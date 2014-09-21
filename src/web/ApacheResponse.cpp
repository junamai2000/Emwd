// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ApacheResponse.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/ApacheResponse.h>

namespace Emwd { namespace web {

ApacheResponse::ApacheResponse(request_rec *r)
{
	this->_req = r;
}

/**
 *
 * @param key
 * @param value
 */
void ApacheResponse::setHeader(const char* key, const char* value)
{
	this->_header[key] = value;
}

void ApacheResponse::setHeaders(std::map<const char*, const char*> header)
{
	this->_header = header;
}

/**
 *
 * @param code
 */
void ApacheResponse::setStatus(int code)
{
	this->_statusCode = code;
}

int ApacheResponse::getStatus(void)
{
	return this->_statusCode;
}

/**
 *
 * @param key
 * @return
 */
const char* ApacheResponse::getHeader(const char* key)
{
	return this->_header[key];
}

std::map<const char*, const char*> ApacheResponse::getHeaders()
{
	return this->_header;
}

/**
 *
 */
void ApacheResponse::setBody(const char* body)
{
	this->_output = body;
}

void ApacheResponse::appendBody(const char* content)
{
	this->_output.append(content);
}

/**
 * Clear response body
 */
void ApacheResponse::clearBody()
{
	this->_output.clear();
}

/**
 *
 * @return
 */
const char* ApacheResponse::getBody()
{
	return this->_output.c_str();
}

ApacheResponse::~ApacheResponse()
{

}

} }
