// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * WebApplication.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/WebApplication.h>
#include <web/Controller.h>

namespace Emwd { namespace web {

/**
 * Get component name
 * @return component name
 */
const char* WebApplication::getComponentName()
{
	return "WebApplication";
}

/**
 * Run application
 * @return
 */
bool WebApplication::run()
{
	bool retval;
	try
	{
		this->raiseEvent("beforeRun");
		retval = this->invoke();
		this->raiseEvent("afterRun");
	} catch (const  Emwd::web::HttpException& e)
	{
		this->setErrorResponse(e);
		retval = false;
	}
	return retval;
}

/**
 * Set error response
 */
void WebApplication::setErrorResponse(const Emwd::web::HttpException e)
{
	this->_response->setStatus(e.getStatusCode());
	this->_response->setBody(e.getMessage());
}

/**
 * Start controller
 * @throw HttpException if there is no controller and action
 * @return
 */
bool WebApplication::invoke()
{
	PROCESS_MAP::iterator it = this->_processMap.begin();

	for (; it != this->_processMap.end(); it++)
	{
		if (std::string(this->_request->getRequestUrl()).find(it->first, 0) != std::string::npos)
		{
			const char *controllerName = it->second.controller;
			if (controllerName == NULL)
				throw Emwd::web::HttpException(404, "Requested Url Is Not Registered");

			if (this->_controllers[controllerName] == NULL)
				throw Emwd::web::HttpException(404, "Requested Controller Is Not Found");

			return this->_controllers[controllerName]->run(this,
					it->second.action);
		}
	}
	throw Emwd::web::HttpException(404, "Requested Controller Is Not Found");
}

/**
 * Register Controller with a name
 * @param controllerName
 * @param controller
 */
void WebApplication::registerController(const char* controllerName,
		Controller* controller)
{
	this->_controllers[controllerName] = controller;
}

/**
 * Has controller
 * @param controllerName
 * @return true if exists
 */
bool WebApplication::hasController(const char* controllerName)
{
	return this->_controllers[controllerName] == NULL ? false : true;
}

/**
 * Register route to a controller and an action
 * @param path
 * @param controller
 * @param action
 */
bool WebApplication::registerRoute(const char* path, const char* controllerName,
		const char *actionName)
{
	if (this->hasController(controllerName))
	{
		PROCESSOR tmp;
		tmp.controller = controllerName;
		tmp.action = actionName;
		this->_processMap[path] = tmp;
		return true;
	}
	return false;
}

} }
