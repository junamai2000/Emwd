// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * WebApplication.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_WEB_APPLICATION_H_
#define EMWD_WEB_APPLICATION_H_

#include <string>
#include <map>
#include <vector>

#include <core/Application.h>
#include <core/Configuration.h>
#include <core/Request.h>
#include <web/Controller.h>
#include <web/HttpException.h>

namespace Emwd { namespace web {

/**
 * WebApplication class
 */
class WebApplication : public Emwd::core::Application
{
private:
	/**
	 * A pair of controller and action
	 */
	typedef struct
	{
		const char* controller;
		const char* action;
	} PROCESSOR;

	/**
	 * Typedef of a router config
	 */
	typedef std::map <const char*, PROCESSOR> PROCESS_MAP;

	/**
	 * Router
	 */
	PROCESS_MAP _processMap;

	/**
	 * Controllers with a name
	 */
	std::map <const char*, Controller*> _controllers;

public:
	/**
	 * Get component name
	 * @return component name
	 */
	virtual const char* getComponentName()
	{
		return "WebApplication";
	}

	/**
	 * Run application
	 * @return
	 */
	virtual bool run()
	{
		bool retval;
		try
		{
			this->raiseEvent("beforeRun");
			retval = this->invoke();
			this->raiseEvent("afterRun");
		}
		catch (const HttpException& e)
		{
			this->_request->setStatusCode(e.getStatusCode());
			// this->_request->setResponse(e.getMessage());
		}
		return retval;
	}

	/**
	 * Start controller
	 * @throw HttpException if there is no controller and action
	 * @return
	 */
	virtual bool invoke()
	{
		PROCESS_MAP::iterator it = this->_processMap.begin();

		for (; it != this->_processMap.end(); it++)
		{
			// need to think algorithm
			// too simple
			if (std::string(this->_request->getRequestUrl()) == it->first)
			{
				const char *controllerName = it->second.controller;
				if (controllerName == NULL)
					throw HttpException(404, "Requested Controller Is Not Found");

				if (this->_controllers[controllerName] == NULL)
					throw HttpException(404, "Requested Action Is Not Found");

				return this->_controllers[controllerName]->run(this, it->second.action);
			}
		}
		throw HttpException(404, "Requested Controller Is Not Found");
	}

	/**
	 * Register Controller with a name
	 * @param controllerName
	 * @param controller
	 */
	void registerController(const char* controllerName, Controller* controller)
	{
		this->_controllers[controllerName] = controller;
	}

	/**
	 * Has controller
	 * @param controllerName
	 * @return true if exists
	 */
	bool hasController(const char* controllerName)
	{
		return this->_controllers[controllerName]==NULL? false:true;
	}

	/**
	 * Register route to a controller and an action
	 * @param path
	 * @param controller
	 * @param action
	 */
	virtual bool registerRoute(const char* path, const char* controllerName, const char *actionName)
	{
		if (this->hasController(controllerName))
		{
			if (this->_controllers[controllerName]->hasAction(actionName))
			{
				PROCESSOR tmp;
				tmp.controller = controllerName;
				tmp.action = actionName;
				this->_processMap[path] = tmp;
				return true;
			}
		}
		return false;

	}
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
