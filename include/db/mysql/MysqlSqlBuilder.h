// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * MysqlSqlBuilder.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_DB_MYSQL_SQL_BUILDER_H_
#define EMWD_DB_MYSQL_SQL_BUILDER_H_ 

// Emwd
#include <db/SqlBuilder.h>

namespace Emwd { namespace db {

class Criteria;

class MysqlSqlBuilder : public Emwd::db::SqlBuilder
{
public:
    MysqlSqlBuilder(Emwd::db::Connection *connection) : SqlBuilder(connection) {};
    const char* getComponentName()
    {
    	return "MysqlSqlBuilder";
    }
};
} }

#endif /* EMWD_DB_MYSQL_SQL_BUILDER_H_ */
