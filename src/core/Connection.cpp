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
#include <iostream>

// Emwd
#include <core/Connection.h>

namespace Emwd { namespace core {

Emwd::core::Connection* ConnectionManager::loadDriver(const char* path, const char* driverName)
{
	std::string soName = path;
	soName += "libemwd";
	soName += driverName;
	soName += "driver.so";

	void* handle = dlopen(soName.c_str(), RTLD_LAZY);
	if (!handle)
	{
		std::cerr << "case 1:" << soName << dlerror() << std::endl;
		return NULL;
	}

	std::string symbol = "get_emwd_";
	symbol += driverName;
	symbol += "_driver";

	Emwd::core::Connection* (*getEmwdDatabaseDriver)(void);
	getEmwdDatabaseDriver = (Emwd::core::Connection* (*)(void))dlsym(handle, symbol.c_str());
	if (getEmwdDatabaseDriver == 0)
	{
		std::cerr << "case 2" << std::endl;
		return NULL;
	}
	return getEmwdDatabaseDriver();
}

} }
