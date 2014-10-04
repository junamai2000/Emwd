// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// Emwd
#include <core/Response.h>
#include <core/Configuration.h>
#include <web/Controller.h>

#include "actions/JsonAction.h"
#include "vendors/picojson/picojson.h"

using namespace Emwd::core;

const char* JsonAction::getComponentName()
{
    return "JsonAction";
}

bool JsonAction::process()
{
	Response *response = this->getController()->getApplication()->getResponse();
	response->setContentType("application/json; charset=UTF-8");
	picojson::object obj;
    obj.insert(std::make_pair("message", picojson::value(std::string("Hello, World!"))));
	picojson::value val(obj);
    response->setBody(val.serialize().c_str());
    return true;
}
