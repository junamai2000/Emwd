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
    EMWD_ACTIVE_RECORD_MAKE_COLUMN(id, Connection::COL_INT);
    EMWD_ACTIVE_RECORD_MAKE_COLUMN(message, Connection::COL_STRING);
    EMWD_ACTIVE_RECORD_MAKE_PK(id, Connection::COL_INT);
}

Fortune* Fortune::findByPk(int id, Emwd::core::Connection *con)
{
    PRIMARY_KEY pk;
    pk.ival = id;
    pk.type = Connection::COL_INT;
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
	Emwd::core::Connection::Records::iterator it;
	int index = 0;
	for (it = results.records.begin(); it != results.records.end(); ++it)
	{
		Fortune* fortune = new Fortune(con);
		Emwd::core::Connection::Record::iterator rIt2;
		int index2 = 0;
		for (rIt2 = (*it).begin(); rIt2 != (*it).end(); ++rIt2)
		{
			fortune->restoreRecord(results.fields[index2].c_str(), (*rIt2).c_str(), fortune->getMeta());
			index2++;
		}
		fortunes->push_back(fortune);
		index++;
	}

	delete criteria;
	delete builder;
	return fortunes;
}
