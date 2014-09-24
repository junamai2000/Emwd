// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * MysqlConnection.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
// C header

// Emwd
#include <db/mysql/MysqlConnection.h>

extern "C"
{
	Emwd::db::Connection* get_emwd_mysql_driver()
	{
		return new Emwd::db::MysqlConnection();
	}
}

namespace Emwd { namespace db {

const char* MysqlConnection::getComponentName()
{
	return "MysqlConnection";
}

MysqlConnection::MysqlConnection()
{
	this->_connection = mysql_init(NULL);
}

const char* MysqlConnection::getDriverName()
{
	return "mysql";
}

bool MysqlConnection::connect(const char* host, int port, const char* user, const char* passwd, const char* db)
{
	if (!mysql_real_connect(this->_connection, host, user, passwd, db, port, NULL, 0))
	{
		return false;
	}
	return true;
}

bool MysqlConnection::disconnect()
{
	mysql_close(this->_connection);
	return true;
}

bool MysqlConnection::isConnected()
{
	return true;
}

bool MysqlConnection::startTransaction()
{
	if (mysql_query(this->_connection, "START TRANSACTION"))
	{
		return false;
	}
	return true;
}

bool MysqlConnection::inTransaction()
{
	return true;
}

bool MysqlConnection::rollback()
{
	if (mysql_query(this->_connection, " ROLLBACK"))
	{
		return false;
	}
	return true;
}

bool MysqlConnection::commit()
{
	if (mysql_query(this->_connection, "COMMIT"))
	{
		return false;
	}
	return true;
}

bool MysqlConnection::execute(const char* query)
{
	if (mysql_query(this->_connection, query))
	{
		return false;
	}
	return true;
}

bool MysqlConnection::prepare(const char* query)
{
	return true;
}

bool MysqlConnection::bindParams()
{
	return true;
}

} }
