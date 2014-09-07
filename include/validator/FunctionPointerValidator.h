// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * FunctionPointerValidator.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */

#ifndef EMWD_VALIDATOR_FUNCTIONPOINTERVALIDATOR_H_
#define EMWD_VALIDATOR_FUNCTIONPOINTERVALIDATOR_H_

#include <core/Validator.h>
#include <core/Model.h>

namespace Emwd { namespace validator {

/**
 *
 */
class FunctionPointerValidator: public Emwd::core::Validator
{
public:
	/**
	 * get component name
	 * @return component name
	 */
	virtual const char* getComponentName()
	{
		return "FunctionPointerValidator";
	}

	int (*_pointerToFunction)(Emwd::core::Model*);

	FunctionPointerValidator(int (*pointerToFunction)(Emwd::core::Model*))
	{
		this->_pointerToFunction = pointerToFunction;
	}

	virtual bool validate(Emwd::core::Model * model)
	{
		if (this->_pointerToFunction(model))
			return true;
		return false;
	}
};
} }

#endif /* EMWD_VALIDATOR_FUNCTIONPOINTERVALIDATOR_H_ */
