// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Application.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#ifndef EMWD_CORE_APPLICATION_H_
#define EMWD_CORE_APPLICATION_H_

// C++ headers
#include <string>
#include <map>
#include <vector>

// Emwd
#include <core/CoreComponent.h>
#include <core/Request.h>
#include <core/Response.h>
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
	 * Response class
	 */
	Response* _response;

	/**
	 * Configuration class
	 */
	Configuration* _configuration;

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
	virtual void setRequest(Request *request);

	/**
	 * set Response class.
	 * @param[in] request
	 */
	virtual void setResponse(Response *response);

	/**
	 * get Request class
	 * @return Request Request class set by setRequest()
	 */
	virtual Request* getRequest();

	/**
	 * get Response class
	 * @return Request Request class set by setRequest()
	 */
	virtual Response* getResponse();

	/**
	 * set Configuration class
	 * @param [in] Configuration config
	 */
	virtual void setConfiguration(Configuration* configuration);

	/**
	 * get Configuration class
	 * @return Configuration class set by setConfig
	 */
	Configuration* getConfiguration();
};

} }

#endif /* EMWD_CORE_APPLICATION_H_ */
