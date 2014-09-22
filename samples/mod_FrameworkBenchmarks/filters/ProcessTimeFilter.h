// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <web/Filter.h>

/**
 * ProcessTimeFilter class
 */
class ProcessTimeFilter : public Emwd::web::Filter
{
private:
	double _start;
	double _end;
public:
	virtual const char* getComponentName();
	virtual bool preFilter(Emwd::web::Controller* controller, Emwd::web::Action* action);
	virtual bool postFilter(Emwd::web::Controller* controller, Emwd::web::Action* action);
    double getTimeofDaySec();
};
