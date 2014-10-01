// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#ifndef FB_CONTROLLERS_FBC_H_
#define FB_CONTROLLERS_FBC_H_

#include <web/Controller.h>

class Filter;
class Action;

/**
 * TwoChController class
 */
class FrameworkBenchmarksController : public Emwd::web::Controller
{
private:
	Emwd::web::Filter* _timer;
	Emwd::web::Action* _jsonAction;
	Emwd::web::Action* _dbAction;
	Emwd::web::Action* _queriesAction;
	Emwd::web::Action* _fortunesAction;
	Emwd::web::Action* _plaintextAction;

	/**
	 * Init and register action and filters
	 */
	virtual void init();

public:
	virtual const char* getComponentName();

	~FrameworkBenchmarksController();
};

#endif
