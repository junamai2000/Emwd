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
#include <db/SqlBuilder.h>
#include <db/Connection.h>
#include <db/Criteria.h>

namespace Emwd { namespace db {

SqlBuilder::SqlBuilder(Emwd::db::Connection *connection)
{
    this->_connection = connection;
}

std::string SqlBuilder::buildFindCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria)
{
    std::string sql = "SELECT ";
    sql += criteria->select;
    sql += " FROM ";
    sql += cc->getComponentName();
    sql += " WHERE ";
    sql += criteria->condition;
    sql += " LIMIT ";
    std::stringstream ss;
    ss << criteria->limit;
    sql += ss.str();
    return sql;
}

std::string SqlBuilder::applyJoin()
{
}

std::string SqlBuilder::applyCondition()
{
}

std::string SqlBuilder::applyOrder()
{
}

std::string SqlBuilder::applyLimit()
{
}

std::string SqlBuilder::applyGroup()
{
}

std::string SqlBuilder::applyHaving()
{
}

} }
