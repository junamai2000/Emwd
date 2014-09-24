// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * MysqlConnection.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_DB_MYSQL_CONNECTION_H_
#define EMWD_DB_MYSQL_CONNECTION_H_

// Emwd
#include <db/Connection.h>
#include <mysql/mysql.h>

namespace Emwd { namespace db {


class MysqlConnection : public Connection
{
private:
	MYSQL* _connection;

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
	virtual bool prepare(const char* query);
	virtual bool bindParams();

};

} }

#endif /* EMWD_DB_MYSQL_CONNECTION_H_ */
