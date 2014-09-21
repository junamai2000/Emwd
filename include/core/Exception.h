// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Exception.h
 *
 *  Created on: 2014/09/04
 *      Author: Junya Namai
 */

#ifndef EMWD_CORE_EXCEPTION_H_
#define EMWD_CORE_EXCEPTION_H_

// C++ headers
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
	 * line number
	 */
	int _lineNumber;

	/**
	 * exception message
	 */
	const char* _message;

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
			const char* fileName = __FILE__);

	/**
	 * get exception code
	 * @return exception code number
	 */
	int getCode() const throw();

	/**
	 * get exception message
	 * @return exception message string
	 */
	const char* getMessage() const throw();

	/**
	 * get exception message
	 * @return exception message string
	 */
	const char* what() const throw();

	/**
	 * get exception line number
	 * @return line number
	 */
	int getLineNumber() const throw();

	/**
	 * get exception file name
	 * @return exception file name
	 */
	const char* getFileName() const throw();
};

} }

#endif /* EMWD_CORE_EXCEPTION_H_ */
