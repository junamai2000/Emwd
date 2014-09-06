/*
 * Action.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_ACTION_H_
#define EMWD_WEB_ACTION_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <core/Application.h>
#include <core/Configuration.h>

namespace Emwd { namespace web {

using namespace Emwd::core;

class Controller;

/**
 * Action class
 */
class Action : public CoreComponent
{
private:
	/**
	 * A pointer to a Controller class which invokes this action
	 */
	Controller* _controller;

public:
	/**
	 * get component name
	 * @return component name
	 */
	virtual const char* getComponentName() = 0;

	/**
	 * Set a pointer to a controller
	 * @param controller
	 */
	void setController(Controller* controller)
	{
		this->_controller = controller;
	}

	/**
	 * get a pointer to a controller
	 * @return a pointer to a controller
	 */
	Controller* getController()
	{
		return this->_controller;
	}

	/**
	 * Start action
	 * @param controller
	 * @return true if there is no error
	 */
	virtual bool run(Controller* controller)
	{
		bool retVal;
		this->_controller = controller;
		this->raiseEvent("beforeRun");
		retVal = this->process();
		this->raiseEvent("afterRun");
		return retVal;
	}

	/**
	 * Main logic of action
	 * @return
	 */
	virtual bool process() = 0;
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
