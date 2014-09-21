// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * FilterChain.cpp
 *
 *  Created on: 2014/09/07
 *      Author: Junya Namai
 */
#include <web/Filter.h>

namespace Emwd { namespace web {

/**
 * Increment depth each time user adds a filter
 * @param depth
 */
void Filter::incrementDepth(int depth)
{
	this->_filterDepth = depth + 1;
}

/**
 * Constructor
 */
Filter::Filter()
{
	this->_filterNext = NULL;
	this->_filterDepth = 0;
}

/**
 * Set a pointer to a controller
 * @param controller
 */
void Filter::setController(Controller* controller)
{
	this->_controller = controller;
}

/**
 * Get controller class
 * @return a pointer to a controller
 */
Controller* Filter::getController()
{
	return this->_controller;
}

/**
 * Add a filter to a chain
 * @param filter
 */
void Filter::setNextFilter(Filter* filter)
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
bool Filter::run(Controller* controller, Action* action)
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

} }
