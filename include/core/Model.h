// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Model.h
 *
 *  Created on: 2014/09/05
 *      Author: Junya Namai
 */
#ifndef EMWD_MODEL_MODEL_H_
#define EMWD_MODEL_MODEL_H_

// C++ headers
#include <string>
#include <iostream>
#include <vector>

// Emwd
#include <core/CoreComponent.h>
#include <core/Validator.h>
#include <core/Error.h>

namespace Emwd { namespace core {

/**
 * Model class
 * this class validates inputs values with Validator class
 */
class Model : public Emwd::core::CoreComponent
{
private:
	/**
	 * parameter which will be validated with _validators
	 */
	std::map <std::string, const char*> _params;

	/**
	 * registered validators
	 */
	std::map <std::string, std::vector <Emwd::core::Validator*> > _validators;

	/**
	 * scenario to change validate action
	 */
	std::string _scenario;

	/**
	 * error objects
	 * if any errors occur, this contains error with messages from validators
	 */
	std::vector<Emwd::core::Error *> _errors;

public:
	/**
	 * destructor
	 * free validators and errors
	 */
	~Model();

	/**
	 * set scenario to change behavior of validator
	 * @param scenario name
	 */
	void setScenario(const char* scenario);

	/**
	 * get scenario string
	 */
	const char* getScenario();

	/**
	 * clean up all errors
	 */
	void clearErrors();

	/**
	 * set request parameters
	 * @param params
	 */
	void setParams(std::map<std::string, const char*> params);

	/**
	 * get request parameters
	 * @param name
	 * @return string
	 */
	std::string getParam(const char* name);

	/**
	 * attach validator with scenario
	 * @param validator
	 */
	void attachValidator(const char* scenario, Emwd::core::Validator *validator);

	/**
	 * validate inputs
	 * @return true if input is valid
	 */
	virtual bool validate();

	/**
	 * add error into an error list
	 * @param errorCode
	 * @param message
	 */
	void addError(int errorCode, const char* message);

	/**
	 * check error
	 * @return true if there is an error
	 */
	bool hasError();

	/**
	 * return all errors in this model
	 * @return error classes
	 */
	std::vector<Emwd::core::Error *> getErrors();

	/**
	 * save data
	 * raise default events: beforeSave, afterSave
	 * @param doValidate set false if you already check inputs
	 * @return
	 */
	bool save(bool doValidate = true);

	/**
	 * login to save not implemented here
	 * @return true if save finishes successfully
	 */
	virtual bool processSave() = 0;

	/**
	 * register validates
	 */
	virtual void registerValidators() = 0;
};

} }

#endif /* MODEL_H_ */
