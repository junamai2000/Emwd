// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Application.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_CORE_APPLICATION_H_
#define EMWD_CORE_APPLICATION_H_

#include <string>
#include <map>
#include <vector>

#include <core/CoreComponent.h>
#include <core/Request.h>
#include <core/Configuration.h>

namespace Emwd { namespace core {

/**
 * Application class
 */
class Application : public CoreComponent
{
private:

protected:
	/**
	 * Request class
	 */
	Request* _request;

	/**
	 * Configuration class
	 */
	Configuration* _config;

public:
	/**
	 * start application
	 * @return if application finish successfully it returns true
	 */
	virtual bool run() = 0;

	/**
	 * set Request class.
	 * @param[in] request
	 */
	virtual void setRequest(Request *request)
	{
		this->_request = request;
	}

	/**
	 * get Request class
	 * @return Request Request class set by setRequest()
	 */
	virtual Request* getRequest()
	{
		return this->_request;
	}

	/**
	 * set Configuration class
	 * @param [in] Configuration config
	 */
	virtual void setConfig(Configuration* config)
	{
		this->_config = config;
	}

	/**
	 * get Configuration class
	 * @return Configuration class set by setConfig
	 */
	Configuration* getConfig()
	{
		return this->_config;
	}
};

} }

#endif /* EMWD_CORE_APPLICATION_H_ */
