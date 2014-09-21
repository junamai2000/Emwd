// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Application.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <string>
#include <map>
#include <vector>

#include <core/Application.h>

namespace Emwd { namespace core {

/**
* set Request class.
* @param[in] request
*/
void Application::setRequest(Request *request)
{
    this->_request = request;
}

/**
* set Response class.
* @param[in] request
*/
void Application::setResponse(Response *response)
{
    this->_response = response;
}

/**
 * get Request class
 * @return Request Request class set by setRequest()
 */
Request* Application::getRequest()
{
    return this->_request;
}

/**
 * get Response class
 * @return Request Request class set by setRequest()
 */
Response* Application::getResponse()
{
    return this->_response;
}

/**
 * set Configuration class
 * @param [in] Configuration config
 */
void Application::setConfiguration(Configuration* configuration)
{
    this->_configuration = configuration;
}

/**
 * get Configuration class
 * @return Configuration class set by setConfig
 */
Configuration* Application::getConfiguration()
{
    return this->_configuration;
}

} }
