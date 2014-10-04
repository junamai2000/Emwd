// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// C++ header
// C++ Header
#include <string>
#include <algorithm>

// EMWD Header
#include <core/Response.h>
#include <core/Connection.h>
#include <web/Controller.h>
#include <kozaiku/Kozaiku.h>

// FWB
#include "actions/FortunesAction.h"
#include "models/Fortune.h"
#include "views/View.h"

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::kozaiku;

const char* FortunesAction::getComponentName()
{
    return "FortuneAction";
}

static bool compare_nocase (const Fortune* first, const Fortune* second)
{
  return first->message < second->message;
}

bool FortunesAction::process()
{
	Response *response = this->getController()->getApplication()->getResponse();
	Connection *connection= this->getController()->getApplication()->getConnection();
	Kozaiku *kozaiku = new Kozaiku("/home/junya/Emwd/samples/mod_FrameworkBenchmarks/views/libfwb.so");

	FortuneTmplArgs args;
	args.fortunes = Fortune::findAll(connection);
	args.fortunes->sort(compare_nocase);

	kozaiku->display("fortunes", &args);
	response->setContentType("text/html");
	response->setBody(args.output.c_str());
    return true;
}
