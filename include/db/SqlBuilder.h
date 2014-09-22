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
class Connection;
/**
 *
 */
class SqlBuilder : public Emwd::core::CoreComponent
{
private:
    SqlBuilder() {};

protected:
    Emwd::db::Connection *_connection;

public:
    SqlBuilder(Emwd::db::Connection *connection);

    std::string buildFindCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria);
    std::string buildCountCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) {} ;
    std::string buildDeleteCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) {} ;
    std::string buildInsertCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) {} ;
    std::string buildUpdateCommand(Emwd::core::CoreComponent *cc, Emwd::db::Criteria *criteria) {} ;

    std::string applyJoin();
    std::string applyCondition();
    std::string applyOrder();
    std::string applyLimit();
    std::string applyGroup();
    std::string applyHaving();
};
} }

#endif /* EMWD_DB_SQL_BUILDER_H_ */
