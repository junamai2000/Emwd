/*
 * Controller.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_CONTROLLER_H_
#define EMWD_WEB_CONTROLLER_H_

#include <map>
#include <vector>
#include <list>

#include <core/Application.h>
#include <core/Configuration.h>
#include <web/Action.h>
#include <web/Filter.h>

namespace Emwd { namespace web {

using namespace Emwd::core;

/**
 * Controller class
 */
class Controller : public CoreComponent
{
private:
	/**
	 * all actions which is attached to this controller
	 */
	std::map <const char*, Action*> _actions;

	/**
	 * all filters which is attached to this controller
	 */
	std::map <const char*, Filter*> _filters;

	/**
	 * A pointer to Application class
	 */
	Application* _app;

public:
	/**
	 * Get component name
	 * @return component name
	 */
	virtual const char* getComponentName()
	{
		return "Controller";
	}

	/**
	 * Get Application class
	 * @return a pointer to Application class
	 */
	Application* getApplication()
	{
		return this->_app;
	}

	/**
	 * Register Action with a name
	 * @param name
	 * @param action
	 */
	void registerAction(const char* name, Action* action)
	{
		action->setController(this);
		this->_actions[name] = action;
	}

	/**
	 * Register Filters
	 * all filters will be executed before and after action class
	 * @param actionName
	 * @param filters
	 */
	void registerFilter(const char* actionName, Filter* filters)
	{
		this->_filters[actionName] = filters;
	}

	/**
	 * RUn Action with filters
	 * @param app
	 * @param action
	 * @return true if action finishes successfully
	 */
	virtual bool run(Application* app, const char* action)
	{
		this->_app = app;
		if (this->_filters.size() > 0)
		{
			Filter* filters = this->_filters[action];
			if (filters)
			{
				return filters->run(this, this->_actions[action]);
			}
		}
		return this->_actions[action]->run(this);
	}
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
