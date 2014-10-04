// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Configuration.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#include <core/Configuration.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

namespace Emwd { namespace core {

/**
* @param storage
*/
void Configuration::setStorage(void* storage)
{
    this->_storage = storage;
}

/**
*
*/
void* Configuration::getStorage()
{
    return this->_storage;
}

void Configuration::readJson(const char* fileName)
{
	boost::property_tree::read_json(fileName, this->_ptree);
}

void Configuration::readXml(const char* fileName)
{
	boost::property_tree::read_xml(fileName, this->_ptree);
}

void Configuration::readIni(const char* fileName)
{
	boost::property_tree::read_ini(fileName, this->_ptree);
}

boost::property_tree::ptree& Configuration::getPropertyTree()
{
	return this->_ptree;
}

const char* Configuration::getApplicationName()
{
	if (boost::optional < std::string > str = this->_ptree.get_optional
			< std::string > ("web.name"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}

const char* Configuration::getDatabaseDriver()
{
	if (boost::optional < std::string > str = this->_ptree.get_optional
			< std::string > ("web.db.driver"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}

const char* Configuration::getDatabaseDriverPath()
{
	if (boost::optional < std::string > str = this->_ptree.get_optional
			< std::string > ("web.db.driverPath"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}

const char* Configuration::getDatabaseHost()
{
	if (boost::optional < std::string > str = this->_ptree.get_optional
			< std::string > ("web.db.host"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}

const char* Configuration::getDatabaseUser()
{
	if (boost::optional<std::string> str =
			this->_ptree.get_optional<std::string>("web.db.user"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}
const char* Configuration::getDatabasePassword()
{
	if (boost::optional<std::string> str =
			this->_ptree.get_optional<std::string>("web.db.password"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}

const char* Configuration::getDatabaseName()
{
	if (boost::optional<std::string> str =
			this->_ptree.get_optional<std::string>("web.db.database"))
	{
		return str.get().c_str();
	}
	else
	{
		return "";
	}
}

int Configuration::getDatabasePort()
{
	if (boost::optional<int> port =
			this->_ptree.get_optional<int>("web.db.port"))
	{
		return port.get();
	}
	else
	{
		return 0;
	}
}

int Configuration::getPreparedStatementCount()
{
	return this->_ptree.count("web.db.prepared");
}

const char* Configuration::getPreparedStatementByIndex(int index)
{
	int counter = 0;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, this->_ptree.get_child("web.db.prepared"))
	{
		if (counter == index)
		{
			const boost::property_tree::ptree &pt2 = v.second;
			return pt2.get<std::string>("query").c_str();
		}
	}
	return "";
}

const char* Configuration::getPreparedStatementNameByIndex(int index)
{
	int counter = 0;
	BOOST_FOREACH(boost::property_tree::ptree::value_type &v, this->_ptree.get_child("web.db.prepared"))
	{
		if (counter == index)
		{
			const boost::property_tree::ptree &pt2 = v.second;
			return pt2.get<std::string>("name").c_str();
		}
	}
	return "";
}

} }
