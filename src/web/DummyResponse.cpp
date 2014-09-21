// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * DummyResponse.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/DummyResponse.h>

namespace Emwd { namespace web {

/**
 *
 * @param key
 * @param value
 */
void DummyResponse::setHeader(const char* key, const char* value)
{
	this->_header[key] = value;
}

void DummyResponse::setHeaders(std::map<const char*, const char*> header)
{
	this->_header = header;
}

/**
 *
 * @param code
 */
void DummyResponse::setStatus(int code)
{
	this->_statusCode = code;
}

int DummyResponse::getStatus(void)
{
	return this->_statusCode;
}

/**
 *
 * @param key
 * @return
 */
const char* DummyResponse::getHeader(const char* key)
{
	return this->_header[key];
}

std::map<const char*, const char*> DummyResponse::getHeaders()
{
	return this->_header;
}

/**
 *
 */
void DummyResponse::setBody(const char* body)
{
	this->_output = body;
}

void DummyResponse::appendBody(const char* content)
{
	this->_output.append(content);
}

/**
 * Clear response body
 */
void DummyResponse::clearBody()
{
	this->_output.clear();
}

/**
 *
 * @return
 */
const char* DummyResponse::getBody()
{
	return this->_output.c_str();
}

DummyResponse::~DummyResponse()
{

}

} }
