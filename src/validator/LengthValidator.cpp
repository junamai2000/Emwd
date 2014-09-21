// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * LengthValidator.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <validator/LengthValidator.h>

namespace Emwd { namespace validator {

/**
 * Constructor
 * @param errorCode
 * @param attribute
 * @param max
 * @param min
 * @param tooLong
 * @param tooShort
 */
LengthValidator::LengthValidator(int errorCode, const char* attribute, int max, int min, const char *tooLong, const char *tooShort)
{
	this->_errorCode = errorCode;
	this->_attribute = attribute;
	this->_max = max;
	this->_min = min;
	this->_tooLong = tooLong;
	this->_tooShort = tooShort;
}

/**
 * get component name
 * @return component name
 */
const char* LengthValidator::getComponentName()
{
	return "LengthValidator";
}

/**
 * validate string length
 * @param model
 * @return true if a string is within specification
 */
bool LengthValidator::validate(Emwd::core::Model* model)
{
	int length = model->getParam(this->_attribute).length();
	if (length < this->_min)
	{
		model->addError(this->_errorCode, this->_tooShort);
		return false;
	}
	if (this->_max < length)
	{
		model->addError(this->_errorCode, this->_tooLong);
		return false;
	}
	return true;
}

} }
