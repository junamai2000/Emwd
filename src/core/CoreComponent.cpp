// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * CoreComponent.cpp
 *
 *  Created on: 2014/09/04
 *      Author: Junya Namai
 */
#include <core/CoreComponent.h>

namespace Emwd { namespace core {

/**
* Add Event into _events
* @param componentName string from getComponentName()
* @param eventName string from raiseEvent()
* @param cc pointer from a class which raised an event
* @return true if event finishes successfully
*/
bool CoreComponent::onEvent(const char* componentName, const char* eventName,	CoreComponent* cc)
{
    return true;
}

/**
* attach event with event name
* @param eventName
* @param event
*/
void CoreComponent::attachEvent(const char *eventName, CoreComponent *event)
{
    if (eventName == NULL || event == NULL)
        return;
    this->_events[eventName].push_back(event);
}

/**
* raise events which attached with specific event name
* @param eventName
*/
void CoreComponent::raiseEvent(const char *eventName)
{
    std::vector<CoreComponent *> event = this->_events[eventName];
    std::vector<CoreComponent *>::iterator it = event.begin();
    while (it != event.end())
    {
        (*it)->onEvent(this->getComponentName(), eventName, this);
        ++it;
    }
}

} }
