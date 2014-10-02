// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/Connection.h>
#include <db/ar/ActiveRecord.h>
#include <db/SqlBuilder.h>

#include "models/Fortune.h"

using namespace Emwd::core;

const char* Fortune::getComponentName()
{
    return "Fortune";
}

Fortune::Fortune(Emwd::core::Connection *connection) : ActiveRecord(connection)
{
    this->setTableSchema();
}

void Fortune::setTableSchema()
{
    EMWD_ACTIVE_RECORD_MAKE_COLUMN(id, COL_INT);
    EMWD_ACTIVE_RECORD_MAKE_COLUMN(message, COL_CHAR);
    this->makePrimaryKey("id", COL_INT);
}

Fortune* Fortune::findByPk(int id, Emwd::core::Connection *con)
{
    PRIMARY_KEY pk;
    pk.ival = id;
    pk.type = COL_INT;
    pk.col = "id";
    std::list<PRIMARY_KEY> pks;
    pks.push_back(pk);
    Fortune *fortune = new Fortune(con);
    fortune->findByPrimaryKey(pks);
    return fortune;
}

Fortune::Fortunes* Fortune::findAll(Emwd::core::Connection *con)
{
	Emwd::db::Criteria *criteria = new Emwd::db::Criteria();
	criteria->select = "*";

	Emwd::core::Connection::Results results;
	Emwd::db::SqlBuilder *builder = Emwd::db::SqlBuilderManager::createSqlBuilder(con);

	Fortune* fortune = new Fortune(con);
	std::string sql = builder->buildFindCommand(fortune, criteria);
	if (!con->execute(sql.c_str(), results))
	{
		std::cerr << "query error: " << sql << std::endl;
	}
	delete fortune;

	Fortunes *fortunes = new Fortunes();
	Emwd::core::Connection::Results::iterator it;
	for (it = results.begin(); it != results.end(); ++it)
	{
		Fortune* fortune = new Fortune(con);
		Emwd::core::Connection::Result::iterator it2;
		for (it2 = (*it).begin(); it2 != (*it).end(); ++it2)
		{
			fortune->restoreRecord((*it2).first.c_str(), (*it2).second.c_str(), fortune->getMeta());
		}
		fortunes->push_back(fortune);
	}

	delete criteria;
	return fortunes;
}
