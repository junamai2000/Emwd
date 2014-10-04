// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * SqlBuilder.cpp
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
// C++ Header
#include <sstream>

// Emwd
#include <core/Connection.h>
#include <db/SqlBuilder.h>
#include <db/mysql/MysqlSqlBuilder.h>
#include <db/Criteria.h>

namespace Emwd { namespace db {

SqlBuilder::SqlBuilder(Emwd::core::Connection *connection)
{
    this->_connection = connection;
}

std::string SqlBuilder::buildFindCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria)
{
    std::string sql = "SELECT ";
    sql += criteria->select;
    sql += " FROM ";
    sql += cc->getComponentName();
    if (criteria->condition != "")
    {
    	sql += " WHERE ";
    	sql += criteria->condition;
    }

    if (criteria->limit > 0)
    {
    	sql += " LIMIT ";
    	std::stringstream ss;
    	ss << criteria->limit;
    	sql += ss.str();
    }
    return sql;
}

std::string SqlBuilder::buildUpdateCommand(Emwd::core::CoreComponent *cc, Attributes attributes, Emwd::db::Criteria *criteria)
{
    std::string sql = "UPDATE ";
    sql += cc->getComponentName();
    sql += " SET ";
    Attributes::iterator it = attributes.begin();
    for (; it != attributes.end(); ++it)
    {
    	sql += "`";
    	sql += it->first;
    	sql += "`";
    	sql += "=";
    	sql += it->second;
    }

    if (criteria->condition != "")
    {
    	sql += " WHERE ";
    	sql += criteria->condition;
    }

    if (criteria->limit > 0)
    {
    	sql += " LIMIT ";
    	std::stringstream ss;
    	ss << criteria->limit;
    	sql += ss.str();
    }
    return sql;
}

std::string SqlBuilder::applyJoin()
{
	return "";
}

std::string SqlBuilder::applyCondition()
{
	return "";
}

std::string SqlBuilder::applyOrder()
{
	return "";
}

std::string SqlBuilder::applyLimit()
{
	return "";
}

std::string SqlBuilder::applyGroup()
{
	return "";
}

std::string SqlBuilder::applyHaving()
{
	return "";
}

Emwd::db::SqlBuilder* SqlBuilderManager::createSqlBuilder(Emwd::core::Connection *connection)
{
    std::string driverName = connection->getDriverName();
    if (driverName == "mysql")
    {
        return new Emwd::db::MysqlSqlBuilder(connection);
    }
    else
        return NULL;
}

} }
