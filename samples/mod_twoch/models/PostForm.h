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
 * PostForm class
 */
class PostForm : public Model
{
private:
	const char *_name;
	const char *_email;
	const char *_text;

public:
	virtual const char* getComponentName();
	void registerValidators();
	// static int complicatedValidator(Model *model);
	bool processSave();
};
