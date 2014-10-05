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
	pthread_mutex_lock(&(this->_connectionMutex));
	this->_connection = mysql_init(NULL);
	pthread_mutex_unlock(&(this->_connectionMutex));
}

const char* MysqlConnection::getDriverName()
{
	return "mysql";
}

bool MysqlConnection::connect(const char* host, int port, const char* user, const char* passwd, const char* db)
{
	pthread_mutex_lock(&(this->_connectionMutex));
	if (!mysql_real_connect(this->_connection, host, user, passwd, db, port, NULL, 0))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::disconnect()
{
	pthread_mutex_lock(&(this->_connectionMutex));
	mysql_close(this->_connection);
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::isConnected()
{
	return true;
}

bool MysqlConnection::startTransaction()
{
	pthread_mutex_lock(&(this->_connectionMutex));
	if (mysql_query(this->_connection, "START TRANSACTION"))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
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
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::commit()
{
	if (mysql_query(this->_connection, "COMMIT"))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::execute(const char* query, Results &results)
{
	pthread_mutex_lock(&(this->_connectionMutex));
	if (mysql_query(this->_connection, query))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
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
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::execute(const char* query)
{
	pthread_mutex_lock(&(this->_connectionMutex));
	if (mysql_query(this->_connection, query))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::prepare(const char* name, const char* query)
{
	pthread_mutex_lock(&(this->_connectionMutex));
	MYSQL_STMT *stmt = mysql_stmt_init(this->_connection);
	if (!stmt)
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	if (mysql_stmt_prepare(stmt, query, strlen(query)))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	this->_statements[name] = stmt;
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

bool MysqlConnection::executePreparedStatement(const char* name, Results &results)
{
	return false;
}

/**
 * executePreparedStatement
 * @param name
 * @return
 */
bool MysqlConnection::executePreparedStatement(const char* name)
{
	/*
	MYSQL_STMT *stmt = this->_statements[name];
	if (!stmt)
	{
		return false;
	}
	pthread_mutex_lock(&(this->_connectionMutex));
	if (mysql_stmt_execute(stmt))
		{
			pthread_mutex_unlock(&(this->_connectionMutex));
			return false;
		}

		MYSQL_RES *res;
		MYSQL_ROW row;
		MYSQL_FIELD *field;

		res = mysql_stmt_result_metadata(stmt);
		int numOfRows = mysql_stmt_num_rows(stmt);
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
	pthread_mutex_unlock(&(this->_connectionMutex));
	*/
}

bool MysqlConnection::bindParams()
{
	return true;
}

bool MysqlConnection::setCharset(CHAR_SET charset)
{
	pthread_mutex_lock(&(this->_connectionMutex));
	std::string query = "SET NAMES ";
	if (charset == UTF_8)
	{
		query += "UTF8";
	}

	if (mysql_query(this->_connection, query.c_str()))
	{
		pthread_mutex_unlock(&(this->_connectionMutex));
		return false;
	}
	pthread_mutex_unlock(&(this->_connectionMutex));
	return true;
}

} }
