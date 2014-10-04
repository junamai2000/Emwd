// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * MysqlConnection.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
// C header
#include <string.h>

// C++ Header
#include <string>

// Emwd
#include <core/mysql/MysqlConnection.h>

extern "C"
{
	Emwd::core::Connection* get_emwd_mysql_driver()
	{
		return new Emwd::core::MysqlConnection();
	}
}

namespace Emwd { namespace core {

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

bool MysqlConnection::execute(const char* query, Results &results)
{
	if (mysql_query(this->_connection, query))
	{
		return false;
	}

	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	res = mysql_store_result(this->_connection);
	int numOfRows = mysql_num_rows(res);
	int numOfFields = mysql_num_fields(res);

	while((field = mysql_fetch_field(res)))
	{
		results.fields.push_back(field->name);
	}

	for (int i = 0; i < numOfRows; i++)
	{
		Connection::Record record;
		row = mysql_fetch_row(res);
		for (int j = 0; j < numOfFields; j++)
		{
			if (row[j] != NULL)
			{
				record.push_back(row[j]);
			}
			else
			{
				record.push_back("");
			}
		}
		results.records.push_back(record);
	}
	mysql_free_result(res);
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

bool MysqlConnection::prepare(const char* name, const char* query)
{
	MYSQL_STMT *stmt = mysql_stmt_init(this->_connection);
	if (!stmt)
	{
		return false;
	}
	if (mysql_stmt_prepare(stmt, query, strlen(query)))
	{
		return false;
	}
	this->_statements[name] = stmt;
	return true;
}

bool MysqlConnection::bindParams()
{
	return true;
}

bool MysqlConnection::setCharset(CHAR_SET charset)
{
	std::string query = "SET NAMES ";
	if (charset == UTF_8)
	{
		query += "UTF8";
	}

	if (mysql_query(this->_connection, query.c_str()))
	{
		return false;
	}
	return true;
}

} }
