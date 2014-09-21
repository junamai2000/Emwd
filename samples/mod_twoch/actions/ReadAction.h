// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <web/Action.h>

class ReadAction : public Emwd::web::Action
{
public:
	virtual const char* getComponentName();

	bool process();
};
