// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Exception.h
 *
 *  Created on: 2014/09/04
 *      Author: Junya Namai
 */

#ifndef EMWD_CORE_EXCEPTION_H_
#define EMWD_CORE_EXCEPTION_H_

#include <exception>

namespace Emwd { namespace core {

/**
 * Exception class
 */
class Exception : public std::exception
{
private:
	/**
	 * can not call constructor without arguments
	 */
	Exception();

protected:
	/**
	 * exception code
	 */
	int _code;

	/**
	 * exception message
	 */
	const char* _message;

	/**
	 * line number
	 */
	int _lineNumber;

	/**
	 * file name
	 */
	const char* _fileName;

public:
	/**
	 * throw exception
	 * @param code
	 * @param message
	 * @param lineNumber
	 * @param fileName
	 */
	Exception(int code, const char* message, int lineNumber = __LINE__,
			const char* fileName = __FILE__)
	{
		this->_code = code;
		this->_message = message;
		this->_lineNumber = lineNumber;
		this->_fileName = fileName;
	}

	/**
	 * get exception code
	 * @return exception code number
	 */
	int getCode() const throw()
	{
		return this->_code;
	}

	/**
	 * get exception message
	 * @return exception message string
	 */
	const char* getMessage() const throw()
	{
		return this->_message;
	}

	/**
	 * get exception message
	 * @return exception message string
	 */
	virtual const char* what() const throw()
	{
		return this->_message;
	}

	/**
	 * get exception line number
	 * @return line number
	 */
	int getLineNumber() const throw()
	{
		return this->_lineNumber;
	}

	/**
	 * get exception file name
	 * @return exception file name
	 */
	const char* getFileName() const throw()
	{
		return this->_fileName;
	}
};

} }

#endif /* EMWD_CORE_EXCEPTION_H_ */
