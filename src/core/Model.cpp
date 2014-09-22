// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Model.cpp
 *
 *  Created on: 2014/09/05
 *      Author: Junya Namai
 */
#include <core/Model.h>

namespace Emwd { namespace core {

/**
* destructor
* free validators and errors
*/
Model::~Model()
{
    // clean up validators
    std::map <std::string, std::vector <Emwd::core::Validator*> >::iterator mvIt= _validators.begin();
    while (mvIt != this->_validators.end())
    {
        std::vector<Emwd::core::Validator *>::iterator vIt = mvIt->second.begin();
        while (vIt != mvIt->second.end())
        {
            delete *vIt;
            ++vIt;
        }
        ++mvIt;
    }

    // clean up errors
    std::vector<Emwd::core::Error *>::iterator eIt = this->_errors.begin();
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
void Model::setScenario(const char* scenario)
{
    this->_scenario = scenario;
}

/**
 * get scenario string
 */
const char* Model::getScenario()
{
    return this->_scenario.c_str();
}

/**
* clean up all errors
*/
void Model::clearErrors()
{
    this->_errors.clear();
}

/**
 * set request parameters
 * @param params
 */
void Model::setParams(std::map<std::string, const char*> params)
{
    this->_params = params;
}

/**
 * get request parameters
 * @param name
 * @return string
 */
std::string Model::getParam(const char* name)
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
void Model::attachValidator(const char* scenario, Emwd::core::Validator *validator)
{
    this->_validators[scenario].push_back(validator);
}

/**
 * validate inputs
 * @return true if input is valid
 */
bool Model::validate()
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
void Model::addError(int errorCode, const char* message)
{
	Emwd::core::Error* err = new Emwd::core::Error(errorCode, message);
    this->_errors.push_back(err);
}

/**
 * check error
 * @return true if there is an error
 */
bool Model::hasError()
{
    return this->_errors.size() > 0 ? (true) : (false);
}

/**
 * return all errors in this model
 * @return error classes
 */
std::vector<Emwd::core::Error *> Model::getErrors()
{
    return this->_errors;
}

/**
 * save data
 * raise default events: beforeSave, afterSave
 * @param doValidate set false if you already check inputs
 * @return
 */
bool Model::save(bool doValidate)
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

} }
