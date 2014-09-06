/*
 * HttpException.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_WEB_HTTP_EXCEPTION_H_
#define EMWD_WEB_HTTP_EXCEPTION_H_

#include <core/CoreComponent.h>
#include <core/Exception.h>

namespace Emwd { namespace web {

using namespace Emwd::core;

/**
 * HttpException class
 */
class HttpException : public Exception
{
private:
	/**
	 * Is not callable
	 */
	HttpException();

	/**
	 * Http status code
	 */
	int _statusCode;

public:
	/**
	 * Constructor
	 * @param code
	 * @param message
	 * @param lineNumber
	 * @param fileName
	 */
	HttpException(int code, const char* message,
			int lineNumber = __LINE__,
			const char* fileName = __FILE__)
			: Exception(code, message, lineNumber, fileName)
	{
		this->_statusCode = code;
	}

	/**
	 * Get Http status code
	 * @return http status code
	 */
	int getStatusCode()
	{
		return this->_statusCode;
	}
};

} }

#endif /* EMWD_WEB_HTTP_EXCEPTION_H_ */
