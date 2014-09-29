// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ApacheResponse.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/ApacheResponse.h>

namespace Emwd { namespace web {

/**
 * Contructor
 * @param r
 */
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
	apr_table_setn(this->_req->headers_out, key, value);
}

void ApacheResponse::setHeaders(std::map<const char*, const char*> header)
{
	this->_header = header;
}

void ApacheResponse::setContentType(const char* contentType)
{
	this->_req->content_type = contentType;
}

const char* ApacheResponse::getContentType()
{
	return this->_req->content_type;
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
	ap_rputs(body, this->_req);
}

void ApacheResponse::appendBody(const char* body)
{
	ap_rputs(body, this->_req);
}

/**
 * Clear response body
 */
void ApacheResponse::clearBody()
{
	;
}

/**
 *
 * @return
 */
const char* ApacheResponse::getBody()
{
	return "";
}

ApacheResponse::~ApacheResponse()
{

}

} }
