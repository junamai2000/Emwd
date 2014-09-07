// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
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

/**
 * Controller class
 */
class Controller : public Emwd::core::CoreComponent
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
	Emwd::core::Application* _app;

public:
	/**
	 * Get component name
	 * @return component name
	 */
	virtual const char* getComponentName() = 0;

	/**
	 * Init function
	 * Add actions
	 */
	virtual void init() = 0;

	/**
	 * Get Application class
	 * @return a pointer to Application class
	 */
	Emwd::core::Application* getApplication()
	{
		return this->_app;
	}

	/**
	 * Register Action with a name
	 * @param name
	 * @param action
	 */
	void registerAction(const char* actionName, Action* action)
	{
		action->setController(this);
		this->_actions[actionName] = action;
	}

	/**
	 * Check action class is registered or not
	 * @param name
	 * @return true if registered
	 */
	bool hasAction(const char* actionName)
	{
		return this->_actions[actionName]==NULL? false:true;
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
	virtual bool run(Emwd::core::Application* app, const char* action)
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

	/**
	 *
	 */
	~Controller()
	{
		;
	}
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
