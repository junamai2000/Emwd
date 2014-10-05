// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Connection.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_CORE_CONNECTION_H_
#define EMWD_CORE_CONNECTION_H_
// C Header
#include <pthread.h>

// C++ header
#include <map>
#include <list>
#include <string>

// Emwd
#include <core/CoreComponent.h>


namespace Emwd { namespace core {

class Connection : public Emwd::core::CoreComponent
{
private:

protected:
	pthread_mutex_t _connectionMutex;

public:
	enum COLUMN_TYPE {COL_BOOL=1, COL_INT, COL_LONG, COL_FLOAT, COL_DOUBLE, COL_DATE, COL_BIN, COL_CHAR, COL_STRING};

	typedef std::vector<std::string> Fields;
	typedef std::vector<std::string> Record;
	typedef std::vector<Record> Records;
	typedef struct _Results
	{
		Fields fields;
		Records records;
	} Results;

	virtual const char* getDriverName() = 0;
	virtual bool connect(const char* host, int port, const char* user, const char* passwd, const char* db) = 0;
	virtual bool disconnect() = 0;
	virtual bool isConnected() = 0;
	virtual bool startTransaction() = 0;
	virtual bool inTransaction() = 0;
	virtual bool rollback() = 0;
	virtual bool commit() = 0;

	// For Normal SQL execution
	virtual bool execute(const char* query, Results &results) = 0;
	virtual bool execute(const char* query) = 0;

	// For Prepared Statement
	virtual bool prepare(const char* name, const char* query) = 0;
	virtual bool executePreparedStatement(const char* name, Results &results) = 0;
	virtual bool executePreparedStatement(const char* name) = 0;
	virtual bool bindParams() = 0;

	enum CHAR_SET {UTF_8, CP932, EUC_JP};
	virtual bool setCharset(CHAR_SET charset) = 0;

	Connection()
	{
		pthread_mutex_init(&(this->_connectionMutex), NULL);
	}

	virtual ~Connection()
	{
		pthread_mutex_destroy(&(this->_connectionMutex));
	}
};

class ConnectionManager
{
public:
	static Emwd::core::Connection* loadDriver(const char* path, const char* driver);
};
} }

#endif /* EMWD_CORE_CONNECTION_H_ */
