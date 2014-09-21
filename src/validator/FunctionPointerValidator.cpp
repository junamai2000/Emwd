// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * FunctionPointerValidator.cpp
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#include <validator/FunctionPointerValidator.h>

namespace Emwd { namespace validator {

/**
 * get component name
 * @return component name
 */
const char* FunctionPointerValidator::getComponentName()
{
	return "FunctionPointerValidator";
}

FunctionPointerValidator::FunctionPointerValidator(
		int (*pointerToFunction)(Emwd::core::Model*))
{
	this->_pointerToFunction = pointerToFunction;
}

bool FunctionPointerValidator::validate(Emwd::core::Model * model)
{
	if (this->_pointerToFunction(model))
		return true;
	return false;
}

} }
