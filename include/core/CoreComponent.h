// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * CoreComponent.h
 *
 *  Created on: 2014/09/04
 *      Author: Junya Namai
 */
#ifndef EMWD_CORE_CORE_COMPONENT_H_
#define EMWD_CORE_CORE_COMPONENT_H_

// C++ headers
#include <string>
#include <map>
#include <vector>

namespace Emwd { namespace core {

/**
 * CoreComponent class
 * Classes that need to accept event or raise event should inherit this class
 */
class CoreComponent
{
private:
	/**
	 * event handers
	 */
	std::map<std::string, std::vector<Emwd::core::CoreComponent*> > _events;

public:
	/**
	 * CoreComponent constructor
	 */
	virtual ~CoreComponent() {}

	/**
	 * Add Event into _events
	 * @param componentName string from getComponentName()
	 * @param eventName string from raiseEvent()
	 * @param cc pointer from a class which raised an event
	 * @return true if event finishes successfully
	 */
	virtual bool onEvent(const char* componentName, const char* eventName,	Emwd::core::CoreComponent* cc);

	/**
	 * all classes inherited from this class need to set component name
	 * @return string componentName, this should be unique
	 */
	virtual const char* getComponentName() = 0;

	/**
	 * attach event with event name
	 * @param eventName
	 * @param event
	 */
	void attachEvent(const char *eventName, Emwd::core::CoreComponent *event);

	/**
	 * raise events which attached with specific event name
	 * @param eventName
	 */
	void raiseEvent(const char *eventName);
};

} }

#endif /* EMWD_CORE_CORE_COMPONENT_H_ */
