// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// C Header
#include <stdio.h>

// Emwd
#include <core/Response.h>
#include <core/Request.h>
#include <web/Controller.h>

// Framework Bench
#include "actions/UpdatesAction.h"
#include "models/World.h"
#include "vendors/picojson/picojson.h"

using namespace Emwd::core;

UpdatesAction::UpdatesAction()
{
}

const char* UpdatesAction::getComponentName()
{
    return "UpdatesAction";
}

bool UpdatesAction::process()
{
    Request *request = this->getController()->getApplication()->getRequest();
    Response *response = this->getController()->getApplication()->getResponse();
    Connection *connection= this->getController()->getApplication()->getConnection();
    
    srand((unsigned int)time(NULL));

    const char* requestCount = request->getGet("queries");
    int count = 0;
    if (requestCount)
    {
        count = atoi(requestCount);
        if (count <= 0)
        {
            count = 1;
        }
        else if(count > 500)
        {
            count = 500;
        }
    }
    else
    {
        count = 1;
    }

    picojson::array elements;
    response->setContentType("application/json; charset=UTF-8");
    for (int i = 0; i < count; i++)
    {
        int id = rand() % 10000 + 1;
        World* world = World::findByPk(id, connection);

        picojson::object obj;
        obj.insert(
                std::make_pair("id", picojson::value((double)world->id))
                );
        obj.insert(
                std::make_pair("randomNumber", picojson::value((double)world->randomNumber))
                );
        picojson::value val(obj);
        elements.push_back(val);

        world->randomNumber = rand() % 10000 + 1;
        world->update();

        delete world;
    }
    picojson::value result(elements);
    response->setBody(result.serialize().c_str());
    return true;
}
