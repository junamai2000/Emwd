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
#include <core/Response.h>
#include <core/Request.h>
#include <core/Configuration.h>
#include <core/Connection.h>

namespace Emwd { namespace core {

/**
* set Request class.
* @param[in] request
*/
void Application::setRequest(Emwd::core::Request *request)
{
    this->_request = request;
}

/**
* set Response class.
* @param[in] request
*/
void Application::setResponse(Emwd::core::Response *response)
{
    this->_response = response;
}

/**
 * set Connection
 * @param response
 */
void Application::setConnection(Emwd::core::Connection *connection)
{
    this->_connection = connection;
}

/**
 * get Request class
 * @return Request Request class set by setRequest()
 */
Emwd::core::Request* Application::getRequest()
{
    return this->_request;
}

/**
 * get Response class
 * @return Request Request class set by setRequest()
 */
Emwd::core::Response* Application::getResponse()
{
    return this->_response;
}

/**
 * get Connection class
 * @return Connection class
 */
Emwd::core::Connection* Application::getConnection()
{
	return this->_connection;
}

/**
 * set Configuration class
 * @param [in] Configuration config
 */
void Application::setConfiguration(Emwd::core::Configuration* configuration)
{
    this->_configuration = configuration;
}

/**
 * get Configuration class
 * @return Configuration class set by setConfig
 */
Emwd::core::Configuration* Application::getConfiguration()
{
    return this->_configuration;
}

} }
