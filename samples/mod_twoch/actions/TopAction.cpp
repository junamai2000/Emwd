// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// Emwd
#include <core/Response.h>
#include <web/Controller.h>

#include "actions/TopAction.h"
#include "models/Category.h"

using namespace Emwd::core;

const char* TopAction::getComponentName()
{
    return "TopAction";
}

bool TopAction::process()
{
	Response *response = this->getController()->getApplication()->getResponse();
	response->setContentType("text/xml");

    XmlSerializableComposite output;
    output.setHeader("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
    output.setElementName("ResultSet");

    Category *category = new Category;
    category->name = "News";
    category->id = 1; 
    category->explanation = "Real time news"; 
    output.add(new XmlSerializableObject<Category*>("Category", category));
    response->setBody(output.serialize().c_str());

    return true;
}
