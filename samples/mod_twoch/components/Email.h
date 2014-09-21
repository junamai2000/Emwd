// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <core/Configuration.h>
#include <core/Model.h>
#include <core/XmlSerializable.h>
#include <web/WebApplication.h>
#include <web/DummyRequest.h>
#include <web/DummyResponse.h>
#include <web/Filter.h>
#include <validator/NumberValidator.h>
#include <validator/LengthValidator.h>
#include <validator/RequiredValidator.h>
#include <validator/FunctionPointerValidator.h>

#include <picojson/picojson.h>
// #include <kozaiku/Kozaiku.h>

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::validator;
// using namespace Emwd::kozaiku;

/**
 * Email class
 */
class Email : public CoreComponent
{
public:
	virtual const char* getComponentName();
	virtual bool onEvent(const char *conponentName, const char* eventName, CoreComponent *obj);
};
