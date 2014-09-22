// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// C Header
#include <stdio.h>

#include <core/Response.h>
#include <web/Controller.h>

#include "actions/DbAction.h"
#include "models/World.h"
#include "vendors/picojson/picojson.h"

using namespace Emwd::core;

DbAction::DbAction()
{
	srand((unsigned int)time(NULL));
}

const char* DbAction::getComponentName()
{
    return "DbAction";
}

bool DbAction::process()
{
	// int id = rand() % 10000 + 1;
	// World* world = World::findByPk(id);

	Response *response = this->getController()->getApplication()->getResponse();

	response->setContentType("application/json; charset=UTF-8");

    /*
	picojson::object obj;
	obj.insert(
			std::make_pair("id", picojson::value((double)world->id))
    );
	obj.insert(
			std::make_pair("randomNumber", picojson::value((double)world->randomNumber))
    );
	picojson::value val(obj);
    }
	response->setBody(val.serialize().c_str());
    */

    return true;
}
