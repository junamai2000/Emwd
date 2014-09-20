// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Model.h
 *
 *  Created on: 2014/09/05
 *      Author: Junya Namai
 */

#ifndef EMWD_MODEL_MODEL_H_
#define EMWD_MODEL_MODEL_H_

#include <string.h>

#include <iostream>
#include <vector>

#include <core/CoreComponent.h>
#include <core/Validator.h>
#include <core/Error.h>

namespace Emwd { namespace core {

struct char_cmp { bool operator () (const char *a,const char *b) const
{
    return strcmp(a,b)<0;}
};

/**
 * Model class
 * this class validates inputs values with Validator class
 */
class Model : public CoreComponent
{
private:
	/**
	 * parameter which will be validated with _validators
	 */
	std::map <const char*, const char*> _params;

	/**
	 * registered validators
	 */
	std::map <const char*, std::vector <Validator*>, char_cmp> _validators;

	/**
	 * scenario to change validate action
	 */
	std::string _scenario;

	/**
	 * error objects
	 * if any errors occur, this contains error with messages from validators
	 */
	std::vector<Error *> _errors;

public:
	/**
	 * destructor
	 * free validators and errors
	 */
	~Model()
	{
		// clean up validators
		std::map <const char*, std::vector <Validator*> >::iterator mvIt= _validators.begin();
		while (mvIt != this->_validators.end())
		{
			std::vector<Validator *>::iterator vIt = mvIt->second.begin();
			while (vIt != mvIt->second.end())
			{
				delete *vIt;
				++vIt;
			}
			++mvIt;
		}

		// clean up errors
		std::vector<Error *>::iterator eIt = this->_errors.begin();
		while (eIt != this->_errors.end())
		{
			delete *eIt;
			++eIt;
		}
	}

	/**
	 * set scenario to change behavior of validator
	 * @param scenario name
	 */
	void setScenario(const char* scenario)
	{
		this->_scenario = scenario;
	}

	/**
	 * get scenario string
	 */
	const char* getScenario()
	{
		return this->_scenario.c_str();
	}

	/**
	 * clean up all errors
	 */
	void clearErrors()
	{
		this->_errors.clear();
	}

	/**
	 * set request parameters
	 * @param params
	 */
	void setParams(std::map<const char*, const char*> params)
	{
		this->_params = params;
	}

	/**
	 * get request parameters
	 * @param name
	 * @return string
	 */
	std::string getParam(const char* name)
	{
		const char* tmp = this->_params[name];
		if (tmp == NULL)
			return "";
		return tmp;
	}

	/**
	 * attach validator with scenario
	 * @param validator
	 */
	void attachValidator(const char* scenario, Validator *validator)
	{
		this->_validators[scenario].push_back(validator);
	}

	/**
	 * validate inputs
	 * @return true if input is valid
	 */
	virtual bool validate()
	{
		// No validator
		if (this->_validators[this->_scenario.c_str()].size()==0)
		{
			return true;
		}

		std::vector<Validator *>::iterator it = this->_validators[this->_scenario.c_str()].begin();
		while (it != this->_validators[this->_scenario.c_str()].end())
		{
			(*it)->validate(this);
			++it;
		}
		if (this->hasError())
		{
			return false;
		}
		return true;
	}

	/**
	 * add error into an error list
	 * @param errorCode
	 * @param message
	 */
	void addError(int errorCode, const char* message)
	{
		Error* err = new Error(errorCode, message);
		this->_errors.push_back(err);
	}

	/**
	 * check error
	 * @return true if there is an error
	 */
	bool hasError()
	{
		return this->_errors.size() > 0 ? (true) : (false);
	}

	/**
	 * return all errors in this model
	 * @return error classes
	 */
	std::vector<Error *> getErrors()
	{
		return this->_errors;
	}

	/**
	 * save data
	 * raise default events: beforeSave, afterSave
	 * @param doValidate set false if you already check inputs
	 * @return
	 */
	bool save(bool doValidate = true)
	{
		if (doValidate)
		{
			this->clearErrors();
			bool retVal = this->validate();
			if (!retVal)
				return false;
		}

		this->raiseEvent("beforeSave");
		this->processSave();
		this->raiseEvent("afterSave");
		return (true);
	}

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
