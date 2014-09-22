// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Configuration.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_CORE_CONFIGURATION_H_
#define EMWD_CORE_CONFIGURATION_H_

#include <boost/property_tree/ptree.hpp>

namespace Emwd { namespace core {

/**
 * Configuration class
 */
class Configuration
{
private:
	/**
	 * Storage pointer
	 */
	void* _storage;

	/**
	 * Boost property tree
	 */
	boost::property_tree::ptree _ptree;

public:
	/**
	 * @param storage
	 */
	void setStorage(void* storage);

	/**
	 * @return Storage pointer
	 */
	void* getStorage();

	/**
	 * Config file parser
	 * @param fileName
	 */
	void readJson(const char* fileName);
	void readXml(const char* fileName);
	void readIni(const char* fileName);
	boost::property_tree::ptree& getPropertyTree();

	/**
	 * Get settings
	 * @return
	 */
	const char* getApplicationName();

	const char* getDatabaseDriver();
	const char* getDatabaseDriverPath();
	const char* getDatabaseHost();
	const char* getDatabaseUser();
	const char* getDatabasePassword();
	const char* getDatabaseName();
	int getDatabasePort();
};

} }

#endif /* EMWD_CORE_CONFIGURATION_H_ */
