// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * HttpException.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/HttpException.h>

namespace Emwd { namespace web {

/**
 * Constructor
 * @param code
 * @param message
 * @param lineNumber
 * @param fileName
 */
HttpException::HttpException(int code, const char* message, int lineNumber, const char* fileName) :
		Exception(code, message, lineNumber, fileName)
{
	this->_statusCode = code;
}

/**
 * Get Http status code
 * @return http status code
 */
int HttpException::getStatusCode() const throw ()
{
	return this->_statusCode;
}

} }
