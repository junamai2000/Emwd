// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
* NumberValidator.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <validator/NumberValidator.h>

namespace Emwd { namespace validator {

/**
 * constructor
 * @param errorCode
 * @param attribute
 * @param max
 * @param min
 * @param tooBig
 * @param tooSmall
 */
NumberValidator::NumberValidator(int errorCode, const char* attribute, int max, int min, const char *tooBig, const char *tooSmall)
{
	this->_errorCode = errorCode;
	this->_attribute = attribute;
	this->_max = max;
	this->_min = min;
	this->_tooBig = tooBig;
	this->_tooSmall = tooSmall;
}

/**
 * get component name
 * @return component name
 */
const char* NumberValidator::getComponentName()
{
	return "NumberValidator";
}

/**
 * validate inputs
 * @param model
 * @return true if input is valid
 */
bool NumberValidator::validate(Emwd::core::Model* model)
{
	long num = atoi(model->getParam(this->_attribute).c_str());
	if (num < this->_min)
	{
		model->addError(this->_errorCode, this->_tooSmall);
		return false;
	}
	if (this->_max < num)
	{
		model->addError(this->_errorCode, this->_tooBig);
		return false;
	}
	return true;
}

} }
