// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Configuration.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#include <core/Configuration.h>

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

} }
