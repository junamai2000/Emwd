// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Connection.cpp
 *
 *  Created on: 2014/09/23
 *      Author: junya
 */
// C header
#include <dlfcn.h>

// C++ header
#include <string>

// Emwd
#include <db/Connection.h>

namespace Emwd { namespace db {

Emwd::db::Connection* ConnectionManager::loadDriver(const char* path, const char* driverName)
{
	std::string soName = path;
	soName += "libemwd";
	soName += driverName;
	soName += "driver";

	std::string symbol = "get_emwd_";
	symbol += driverName;
	symbol += "_driver";

	void* handle = dlopen(soName.c_str(), RTLD_LAZY);
	if (!handle)
	{
		return NULL;
	}

	Emwd::db::Connection* (*getEmwdDatabaseDriver)(void);
	getEmwdDatabaseDriver = (Emwd::db::Connection* (*)(void))dlsym(handle, symbol.c_str());
	if (getEmwdDatabaseDriver == 0)
	{
		return NULL;
	}
	return getEmwdDatabaseDriver();
}

} }
