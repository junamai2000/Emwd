// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Configuration.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_CORE_CONFIGURATION_H_
#define EMWD_CORE_CONFIGURATION_H_

namespace Emwd { namespace core {

/**
 * Configuration class
 */
class Configuration
{
private:
	/**
	 *
	 */
	void* _storage;

public:
	/**
	 *
	 * @param storage
	 */
	void setStorage(void* storage);

	/**
	 *
	 */
	void* getStorage();
};

} }

#endif /* EMWD_CORE_CONFIGURATION_H_ */
