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

} }
