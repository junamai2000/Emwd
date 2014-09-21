// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
* RequiredValidator.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_VALIDATOR_REQUIREDVALIDATOR_H_
#define EMWD_VALIDATOR_REQUIREDVALIDATOR_H_

#include <core/Validator.h>
#include <core/Model.h>

namespace Emwd { namespace validator {

/**
 * RequiredValidator
 */
class RequiredValidator: public Emwd::core::Validator
{
private:
	/**
	 * Name of a required parameter
	 */
	const char* _attribute;

	/**
	 * user-defined message when a value is empty
	 */
	const char *_message;

public:
	/**
	 * constructor
	 * @param errorCode
	 * @param attribute
	 * @param message
	 */
	RequiredValidator(int errorCode, const char* attribute, const char *message = "");

	/**
	 * get component name
	 * @return component name
	 */
	virtual const char* getComponentName();

	/**
	 * validate input
	 * @param model
	 * @return true if value is not empty
	 */
	virtual bool validate(Emwd::core::Model* model);
};

} }

#endif /* EMWD_VALIDATOR_REQUIREDVALIDATOR_H_ */
