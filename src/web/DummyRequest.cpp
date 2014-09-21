// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * DummyResponse.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/DummyRequest.h>

namespace Emwd { namespace web {

/**
 *
 * @param key
 * @return
 */
const char* DummyRequest::getGet(const char* key)
{
	return this->_get[key];
}

/**
 *
 * @param key
 * @param value
 */
void DummyRequest::setGet(const char* key, const char* value)
{
	this->_get[key] = value;
}

std::map<const char*, const char*> DummyRequest::getGets()
{
	return this->_get;
}

/**
 *
 * @param gets
 */
void DummyRequest::setGets(std::map<const char*, const char*> gets)
{
	this->_get = gets;
}

/**
 *
 * @param key
 * @return
 */
const char* DummyRequest::getPost(const char* key)
{
	return this->_post[key];
}

/**
 *
 * @return
 */
std::map<const char*, const char*> DummyRequest::getPosts()
{
	return this->_post;
}

/**
 *
 * @param key
 * @param value
 */
void DummyRequest::setPost(const char* key, const char *value)
{
	this->_post[key] = value;
}

/**
 *
 * @param posts
 */
void DummyRequest::setPosts(std::map<const char*, const char*> posts)
{
	this->_post = posts;
}

/**
 *
 * @param type
 */
void DummyRequest::setContentType(const char* type)
{
	this->_contentType = type;
}

/**
 *
 * @return
 */
const char* DummyRequest::getContentType()
{
	return this->_contentType.c_str();
}

/**
 *
 * @param url
 */
void DummyRequest::setRequestUrl(const char* url)
{
	this->_url = url;
}

/**
 *
 * @return
 */
const char* DummyRequest::getRequestUrl()
{
	return this->_url.c_str();
}

/**
 *
 * @param code
 */
void DummyRequest::setStatusCode(int code)
{
	this->_statusCode = code;
}

/**
 *
 * @param method
 */
void DummyRequest::setRequestMethod(REQUEST_METHOD method)
{
	this->_method = method;
}

/**
 *
 * @param key
 * @param value
 */
void DummyRequest::setHeader(const char* key, const char value)
{
	;
}

/**
 *
 * @param headers
 */
void DummyRequest::setHeaders(std::map<const char*, const char*> headers)
{
	;
}

/**
 *
 * @param key
 * @return
 */
const char* DummyRequest::getHeader(const char* key)
{
	return "not implemented yet";
}

/**
 *
 * @return
 */
std::map<const char*, const char*> DummyRequest::getHeaders()
{
	std::map<const char*, const char*> dummy;
	dummy["not implemented yet"] = "not implemented yet";
	return dummy;
}

/**
 *
 * @return request method such as POST, GET
 */
Emwd::core::Request::REQUEST_METHOD DummyRequest::getRequestMethod()
{
	return this->_method;
}

DummyRequest::~DummyRequest()
{

}

} }
