// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <web/Action.h>

class FortuneAction : public Emwd::web::Action
{
public:
	virtual const char* getComponentName();

	virtual bool process();
};
