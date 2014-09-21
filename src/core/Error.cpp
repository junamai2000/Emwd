// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Error.cpp
 *
 *  Created on: 2014/09/05
 *      Author: Junya Namai
 */

#include <core/Error.h>

namespace Emwd { namespace core {

/**
* create Error object
* @param errorCode
* @param message
* @param lineNumber
* @param fileName
*/
Error::Error(int errorCode, const char* message, int lineNumber, const char* fileName)
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
int Error::getErrorCode()
{
    return this->_errorCode;
}

/**
* get error message
* @return error message
*/
const char* Error::getMessage()
{
    return this->_message;
}

} }
