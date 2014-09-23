// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/Connection.h>
#include <db/ar/ActiveRecord.h>

#include "models/World.h"

using namespace Emwd::core;

const char* World::getComponentName()
{
	return "World";
}

World::World(Emwd::core::Connection *connection) : ActiveRecord(connection)
{
	this->setTableSchema();
}

void World::setTableSchema()
{
    EMWD_ACTIVE_RECORD_MAKE_COLUMN(id, COL_INT);
    EMWD_ACTIVE_RECORD_MAKE_COLUMN(randomNumber, COL_INT);
    this->makePrimaryKey("id", COL_INT);
}

World* World::findByPk(int id, Emwd::core::Connection *con)
{
    PRIMARY_KEY pk;
    pk.ival = id;
    pk.type = COL_INT;
    pk.col = "id";
    std::list<PRIMARY_KEY> pks;
    pks.push_back(pk);
    World *world= new World(con);
    world->findByPrimaryKey(pks);
    return world;
}
