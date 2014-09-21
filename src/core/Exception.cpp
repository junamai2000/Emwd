// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Exception.cpp
 *
 *  Created on: 2014/09/04
 *      Author: Junya Namai
 */

#include <core/Exception.h>

namespace Emwd { namespace core {

/**
* throw exception
* @param code
* @param message
* @param lineNumber
* @param fileName
*/
Exception::Exception(int code, const char* message, int lineNumber, const char* fileName)
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
int Exception::getCode() const throw()
{
    return this->_code;
}

/**
* get exception message
* @return exception message string
*/
const char* Exception::getMessage() const throw()
{
    return this->_message;
}

/**
* get exception message
* @return exception message string
*/
const char* Exception::what() const throw()
{
    return this->_message;
}

/**
* get exception line number
* @return line number
*/
int Exception::getLineNumber() const throw()
{
    return this->_lineNumber;
}

/**
* get exception file name
* @return exception file name
*/
const char* Exception::getFileName() const throw()
{
    return this->_fileName;
}

} }
