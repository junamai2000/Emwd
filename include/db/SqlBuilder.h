// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * SqlBuilder.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_DB_SQL_BUILDER_H_
#define EMWD_DB_SQL_BUILDER_H_ 

// Emwd
#include <core/CoreComponent.h>

namespace Emwd { namespace db {

class Criteria;

/**
 *
 */
class SqlBuilder : public Emwd::core::CoreComponent
{
private:
    SqlBuilder() {};

protected:
    Emwd::core::Connection *_connection;

public:
    SqlBuilder(Emwd::core::Connection *connection);
    typedef std::map<std::string, std::string> Attributes;

    std::string buildFindCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria);
    std::string buildCountCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) { return ""; }
    std::string buildDeleteCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) { return ""; }
    std::string buildInsertCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) {return ""; }
    std::string buildUpdateCommand(Emwd::core::CoreComponent *cc, Attributes attributes, Emwd::db::Criteria *criteria);

    std::string applyJoin();
    std::string applyCondition();
    std::string applyOrder();
    std::string applyLimit();
    std::string applyGroup();
    std::string applyHaving();
};

class SqlBuilderManager
{
public:
	static Emwd::db::SqlBuilder* createSqlBuilder(Emwd::core::Connection* connection);
};

} }

#endif /* EMWD_DB_SQL_BUILDER_H_ */
