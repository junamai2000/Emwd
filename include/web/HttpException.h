// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
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

/**
 * HttpException class
 */
class HttpException : public Emwd::core::Exception
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
	int getStatusCode() const throw()
	{
		return this->_statusCode;
	}
};

} }

#endif /* EMWD_WEB_HTTP_EXCEPTION_H_ */
