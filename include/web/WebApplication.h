// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * WebApplication.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_WEB_APPLICATION_H_
#define EMWD_WEB_APPLICATION_H_

// C++ headers
#include <string>
#include <map>
#include <vector>

// Emwd
#include <core/Application.h>
#include <core/Configuration.h>
#include <core/Request.h>
#include <core/Response.h>
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
	std::map <std::string, Controller*> _controllers;

public:
	/**
	 * Get component name
	 * @return component name
	 */
	virtual const char* getComponentName();

	/**
	 * Run application
	 * @return
	 */
	virtual bool run();

	/**
	 * Set error response
	 */
	virtual void setErrorResponse(const HttpException e);

	/**
	 * Start controller
	 * @throw HttpException if there is no controller and action
	 * @return
	 */
	virtual bool invoke();

	/**
	 * Register Controller with a name
	 * @param controllerName
	 * @param controller
	 */
	void registerController(const char* controllerName, Controller* controller);

	/**
	 * Has controller
	 * @param controllerName
	 * @return true if exists
	 */
	bool hasController(const char* controllerName);

	/**
	 * Register route to a controller and an action
	 * @param path
	 * @param controller
	 * @param action
	 */
	virtual bool registerRoute(const char* path, const char* controllerName, const char *actionName);
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
