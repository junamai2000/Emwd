// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/Connection.h>
#include <db/ar/ActiveRecord.h>
#include <boost/lexical_cast.hpp>

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
    EMWD_ACTIVE_RECORD_MAKE_PK(id, COL_INT);
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

bool World::update()
{
	Emwd::db::Criteria *criteria = new Emwd::db::Criteria();
	Emwd::db::SqlBuilder *builder = Emwd::db::SqlBuilderManager::createSqlBuilder(this->_connection);

    PRIMARY_KEY pk;
    pk.ival = this->id;
    pk.type = COL_INT;
    pk.col = "id";
    std::list<PRIMARY_KEY> pks;
    pks.push_back(pk);
	criteria->condition = this->makePkCondition(pks);

	Emwd::db::SqlBuilder::Attributes attributes;
	attributes["randomNumber"] = boost::lexical_cast<std::string>(this->randomNumber);

	std::string sql = builder->buildUpdateCommand(this, attributes, criteria);

	if (!this->_connection->execute(sql.c_str()))
	{
		std::cerr << "query error: " << sql << std::endl;
	}

	delete criteria;
	delete builder;
	return true;
}
