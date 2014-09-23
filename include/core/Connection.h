// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Connection.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_CORE_CONNECTION_H_
#define EMWD_CORE_CONNECTION_H_
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

public:
	typedef std::map<std::string, std::string> Result;
	typedef std::list<Result> Results;

	virtual const char* getDriverName() = 0;
	virtual bool connect(const char* host, int port, const char* user, const char* passwd, const char* db) = 0;
	virtual bool disconnect() = 0;
	virtual bool isConnected() = 0;
	virtual bool startTransaction() = 0;
	virtual bool inTransaction() = 0;
	virtual bool rollback() = 0;
	virtual bool commit() = 0;
	virtual bool execute(const char* query, Results &results) = 0;
	virtual bool execute(const char* query) = 0;
	virtual bool prepare(const char* name, const char* query) = 0;
	virtual bool bindParams() = 0;
};

class ConnectionManager
{
public:
	static Emwd::core::Connection* loadDriver(const char* path, const char* driver);
};
} }

#endif /* EMWD_CORE_CONNECTION_H_ */
