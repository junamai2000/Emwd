// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <web/Controller.h>

class Filter;
class Action;

/**
 * TwoChController class
 */
class TwoChController : public Emwd::web::Controller
{
private:
	Emwd::web::Filter* filter;
	Emwd::web::Filter* filter2;
	Emwd::web::Filter* timer;
	Emwd::web::Action* action;

	/**
	 * Init and register action and filters
	 */
	virtual void init();

public:
	virtual const char* getComponentName();

	~TwoChController();
};
