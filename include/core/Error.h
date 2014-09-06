// vim:set noet ts=2 st=2 sw=2 ft=cpp fenc=utf-8 ff=unix:
/*
 * Error.h
 *
 *  Created on: 2014/09/05
 *      Author: Junya Namai
 */
#ifndef EMWD_CORE_ERROR_H_
#define EMWD_CORE_ERROR_H_

namespace Emwd { namespace core {

/**
 * Error class
 */
class Error
{
private:
	/**
	 * can not call constructor without arguments
	 */
	Error();

protected:
	/**
	 * error code
	 */
	int _errorCode;

	/**
	 * error message
	 */
	const char* _message;

	/**
	 * line number of error
	 */
	int _lineNumber;

	/**
	 * file name which raised error
	 */
	const char* _fileName;

public:
	/**
	 * create Error object
	 * @param errorCode
	 * @param message
	 * @param lineNumber
	 * @param fileName
	 */
	Error(int errorCode, const char* message, int lineNumber = __LINE__, const char* fileName = __FILE__)
	{
		this->_errorCode = errorCode;
		this->_message = message;
		this->_lineNumber = lineNumber;
		this->_fileName = fileName;
	}

	/**
	 * get error code
	 * @return error code
	 */
	int getErrorCode()
	{
		return this->_errorCode;
	}

	/**
	 * get error message
	 * @return error message
	 */
	const char* getMessage()
	{
		return this->_message;
	}
};

} }

#endif /* EMWD_CORE_ERROR_H_ */
