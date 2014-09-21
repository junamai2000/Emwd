// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Action.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/Action.h>

namespace Emwd { namespace web {

/**
 * Set a pointer to a controller
 * @param controller
*/
void Action::setController(Controller* controller)
{
    this->_controller = controller;
}

/**
 * get a pointer to a controller
 * @return a pointer to a controller
 */
Controller* Action::getController()
{
    return this->_controller;
}

/**
 * Start action
 * @param controller
 * @return true if there is no error
 */
bool Action::run(Controller* controller)
{
    bool retVal;
    this->_controller = controller;
    this->raiseEvent("beforeRun");
    retVal = this->process();
    this->raiseEvent("afterRun");
    return retVal;
}

} }
