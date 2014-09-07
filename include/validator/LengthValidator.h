// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * LenghtValidator.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_VALIDATOR_LENGHTVALIDATOR_H_
#define EMWD_VALIDATOR_LENGHTVALIDATOR_H_

#include <core/Validator.h>
#include <core/Model.h>

namespace Emwd { namespace validator {

/**
 * LengthValidator class
 * check if string length is valid
 */
class LengthValidator: public Emwd::core::Validator
{
private:
	/**
	 * input name which is validated
	 */
	const char* _attribute;

	/**
	 * max acceptable length of a string
	 */
	int _max;

	/**
	 * minimun acceptable length of a string
	 */
	int _min;

	/**
	 * error message if a string is too long
	 */
	const char *_tooLong;

	/**
	 * error message if a string is too short
	 */
	const char *_tooShort;

public:
	/**
	 * Constructor
	 * @param errorCode
	 * @param attribute
	 * @param max
	 * @param min
	 * @param tooLong
	 * @param tooShort
	 */
	LengthValidator(int errorCode, const char* attribute, int max = 0, int min = 0,
			const char *tooLong = "", const char *tooShort = "")
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
	virtual const char* getComponentName()
	{
		return "LengthValidator";
	}

	/**
	 * validate string length
	 * @param model
	 * @return true if a string is within specification
	 */
	virtual bool validate(Emwd::core::Model* model)
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
};

} }

#endif /* EMWD_VALIDATOR_LENGHTVALIDATOR_H_ */
