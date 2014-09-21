// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/CoreComponent.h>

/**
 * Email class
 */
class Email : public Emwd::core::CoreComponent
{
public:
	virtual const char* getComponentName();
	virtual bool onEvent(const char *conponentName, const char* eventName, CoreComponent *obj);
};
