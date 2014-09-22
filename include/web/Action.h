// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Action.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_WEB_ACTION_H_
#define EMWD_WEB_ACTION_H_

// C++ headers
#include <string>
#include <map>
#include <vector>

// Emwd
#include <core/Application.h>
#include <core/Configuration.h>

namespace Emwd { namespace web {

class Controller;

/**
 * Action class
 */
class Action : public Emwd::core::CoreComponent
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
	void setController(Controller* controller);

	/**
	 * get a pointer to a controller
	 * @return a pointer to a controller
	 */
	Controller* getController();

	/**
	 * Start action
	 * @param controller
	 * @return true if there is no error
	 */
	virtual bool run(Controller* controller);

	/**
	 * Main logic of action
	 * @return
	 */
	virtual bool process() = 0;
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
