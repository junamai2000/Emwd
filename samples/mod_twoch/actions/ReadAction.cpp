// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <core/Request.h>
#include <core/Response.h>
#include <web/WebApplication.h>
#include <web/Controller.h>
#include <web/Action.h>
#include <web/Filter.h>

#include "config/JsonConfiguration.h"
#include "actions/ReadAction.h"

using namespace Emwd::core;
using namespace Emwd::web;

const char* ReadAction::getComponentName()
{
    return "ReadAction";
}

bool ReadAction::process()
{
    //JsonConfiguration *conf = (JsonConfiguration*)this->getController()->getConfiguration()->getStorage();
    //Response *response = this->getController()->getApplication()->getRequest()->getResponse();
    //(*response) << "Start Application : " << conf->getApplicationName(); // << std::endl;
    return true;
}