// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * validator.h
 *
 *  Created on: 2014/09/05
 *      Author: Junya Namai
 */
#ifndef EMWD_VALIDATOR_VALIDATOR_H_
#define EMWD_VALIDATOR_VALIDATOR_H_

// Emwd
#include <core/CoreComponent.h>

namespace Emwd { namespace core {

class Model;

/**
 * Validator class
 */
class Validator: public CoreComponent
{
protected:
	/**
	 * error code
	 */
	int _errorCode;

public:
	/**
	 * validate function
	 * implement validate logic here
	 * @param model
	 * @return true if input is valid
	 */
	virtual bool validate(Model* model) = 0;
};

} }

#endif /* EMWD_VALIDATOR_VALIDATOR_H_ */
