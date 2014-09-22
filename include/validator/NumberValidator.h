// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
* NumberValidator.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_VALIDATOR_NUMBERVALIDATOR_H_
#define EMWD_VALIDATOR_NUMBERVALIDATOR_H_

// Emwd
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
	 * max acceptable number
	 */
	int _max;

	/**
	 * minimum acceptable number
	 */
	int _min;

	/**
	 * parameter name to be checked
	 */
	const char* _attribute;

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
			const char *tooBig = "", const char *tooSmall = "");

	/**
	 * get component name
	 * @return component name
	 */
	virtual const char* getComponentName();

	/**
	 * validate inputs
	 * @param model
	 * @return true if input is valid
	 */
	virtual bool validate(Emwd::core::Model* model);
};

} }

#endif /* NUMBERVALIDATOR_H_ */
