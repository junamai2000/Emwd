// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * FunctionPointerValidator.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_VALIDATOR_FUNCTIONPOINTERVALIDATOR_H_
#define EMWD_VALIDATOR_FUNCTIONPOINTERVALIDATOR_H_

// Emwd
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
	virtual const char* getComponentName();

	int (*_pointerToFunction)(Emwd::core::Model*);

	FunctionPointerValidator(int (*pointerToFunction)(Emwd::core::Model*));

	virtual bool validate(Emwd::core::Model * model);
};
} }

#endif /* EMWD_VALIDATOR_FUNCTIONPOINTERVALIDATOR_H_ */
