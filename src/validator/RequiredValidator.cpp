// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
* RequiredValidator.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <validator/RequiredValidator.h>

namespace Emwd { namespace validator {

/**
 * constructor
 * @param errorCode
 * @param attribute
 * @param message
 */
RequiredValidator::RequiredValidator(int errorCode, const char* attribute, const char *message)
{
	this->_errorCode = errorCode;
	this->_attribute = attribute;
	this->_message = message;
}

/**
 * get component name
 * @return component name
 */
const char* RequiredValidator::getComponentName()
{
	return "RequiredValidator";
}

/**
 * validate input
 * @param model
 * @return true if value is not empty
 */
bool RequiredValidator::validate(Emwd::core::Model* model)
{
	std::string tmp = model->getParam(this->_attribute);
	if (tmp.size() == 0)
	{
		model->addError(this->_errorCode, this->_message);
		return false;
	}
	return true;
}

} }
