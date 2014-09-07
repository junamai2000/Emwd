// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * FilterChain.h
 *
 *  Created on: 2014/09/07
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_FILTER_CHAIN_H_
#define EMWD_WEB_FILTER_CHAIN_H_

#include <string>
#include <list>

#include <core/Application.h>
#include <core/Configuration.h>
#include <web/Action.h>

namespace Emwd { namespace web {

/**
 * Filter class
 * This class is a chain of responsibility
 * execute filters before and after action class
 * this can be used for authorization before user enters action class
 */
class Filter : public Emwd::core::CoreComponent
{
protected:
	/**
	 * A next filter
	 */
	Filter* _filterNext;

	/**
	 * Controller which invoke this filter
	 */
	Controller* _controller;

	/**
	 * depth of filter chain
	 */
	int _filterDepth;

	/**
	 * Increment depth each time user adds a filter
	 * @param depth
	 */
	void incrementDepth(int depth)
	{
		this->_filterDepth = depth+1;
	}

public:
	/**
	 * Constructor
	 */
	Filter()
	{
		this->_filterNext = NULL;
		this->_filterDepth = 0;
	}

	/**
	 * Get component name
	 * Not implemented here
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
	 * Get controller class
	 * @return a pointer to a controller
	 */
	Controller* getController()
	{
		return this->_controller;
	}

	/**
	 * Add a filter to a chain
	 * @param filter
	 */
	void setNextFilter(Filter* filter)
	{
		filter->incrementDepth(this->_filterDepth);
		this->_filterNext = filter;
	}

	/**
	 * run filters with an action class
	 * @param controller
	 * @param action
	 * @return
	 */
	virtual bool run(Controller* controller, Action* action)
	{
		this->preFilter(controller, action);
		if (this->_filterNext)
		{
			this->_filterNext->run(controller, action);
		}
		else
		{
			action->run(controller);
		}
		this->postFilter(controller, action);
		return false;
	}

	/**
	 * User has to implement pre filter in a concreate class
	 * @param controller
	 * @param action
	 * @return true if filter finishes successfully
	 */
	virtual bool preFilter(Controller* controller, Action* action) = 0;

	/**
	 * User has to implement post filter in a concreate class
	 * @param controller
	 * @param action
	 * @return
	 */
	virtual bool postFilter(Controller* controller, Action* action) = 0;
};

} }

#endif /* EMWD_WEB_APPLICATION_H_ */
