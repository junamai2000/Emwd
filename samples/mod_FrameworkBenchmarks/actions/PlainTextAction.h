// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#ifndef FB_ACTIONS_PLAINTEXTACTION_H_
#define FB_ACTIONS_PLAINTEXTACTION_H_

#include <web/Action.h>

class PlainTextAction : public Emwd::web::Action
{
public:
	virtual const char* getComponentName();
	virtual bool process();
};

#endif
