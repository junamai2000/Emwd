// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <core/Request.h>
#include <core/Response.h>
#include <web/WebApplication.h>
#include <web/Controller.h>
#include <web/Action.h>
#include <web/Filter.h>

#include "actions/PlainTextAction.h"

using namespace Emwd::core;
using namespace Emwd::web;

const char* PlainTextAction::getComponentName()
{
    return "PlainTextAction";
}

bool PlainTextAction::process()
{
	Response *response = this->getController()->getApplication()->getResponse();
	response->setContentType("text/plain");
	response->setBody("Hello, World");
    return true;
}
