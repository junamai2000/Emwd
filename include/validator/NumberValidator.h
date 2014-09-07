// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
* NumberValidator.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_VALIDATOR_NUMBERVALIDATOR_H_
#define EMWD_VALIDATOR_NUMBERVALIDATOR_H_

#include <core/Validator.h>
#include <core/Model.h>

namespace Emwd { namespace validator {

/**
 * NumberValidator class
 * check if an input is within specific range
 */
class NumberValidator: public Emwd::core::Validator
{
private:
	/**
	 * parameter name to be checked
	 */
	const char* _attribute;

	/**
	 * max acceptable number
	 */
	int _max;

	/**
	 * minimum acceptable number
	 */
	int _min;

	/**
	 * user-defined error message when value is too big
	 */
	const char *_tooBig;

	/**
	 * user-defined error message when value is too small
	 */
	const char *_tooSmall;

public:
	/**
	 * constructor
	 * @param errorCode
	 * @param attribute
	 * @param max
	 * @param min
	 * @param tooBig
	 * @param tooSmall
	 */
	NumberValidator(int errorCode, const char* attribute, int max = 0, int min = 0,
			const char *tooBig = "", const char *tooSmall = "")
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
	virtual const char* getComponentName()
	{
		return "NumberValidator";
	}

	/**
	 * validate inputs
	 * @param model
	 * @return true if input is valid
	 */
	virtual bool validate(Emwd::core::Model* model)
	{
		long num = std::stoi(model->getParam(this->_attribute));
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
};

} }

#endif /* NUMBERVALIDATOR_H_ */
