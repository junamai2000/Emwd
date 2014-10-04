// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * MysqlConnection.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_CORE_MYSQL_CONNECTION_H_
#define EMWD_CORE_MYSQL_CONNECTION_H_
// C header
#include <mysql/mysql.h>
// Emwd
#include <core/Connection.h>
#include <mysql/mysql.h>

namespace Emwd { namespace core {

class MysqlConnection : public Connection
{
private:
	MYSQL* _connection;
	std::map<std::string, MYSQL_STMT *> _statements;

public:
	MysqlConnection();
	virtual const char* getComponentName();
	virtual const char* getDriverName();
	virtual bool connect(const char* host, int port, const char* user, const char* passwd, const char* db);
	virtual bool disconnect();
	virtual bool isConnected();
	virtual bool startTransaction();
	virtual bool inTransaction();
	virtual bool rollback();
	virtual bool commit();
	virtual bool execute(const char* query);
	virtual bool execute(const char* query, Results &results);
	virtual bool prepare(const char* name, const char* query);
	virtual bool bindParams();
	virtual bool setCharset(CHAR_SET charset);
};

} }

#endif /* EMWD_CORE_CONNECTION_H_ */
