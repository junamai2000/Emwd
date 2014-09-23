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

namespace Emwd { namespace core {

class Request;
class Response;
class Configuration;
class Connection;

/**
 * Application class
 */
class Application : public Emwd::core::CoreComponent
{
private:

protected:
	/**
	 * Request class
	 */
	Emwd::core::Request* _request;

	/**
	 * Response class
	 */
	Emwd::core::Response* _response;

	/**
	 * Configuration class
	 */
	Emwd::core::Configuration* _configuration;

	/**
	 * Connection class
	 */
	Emwd::core::Connection* _connection;

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
	virtual void setRequest(Emwd::core::Request *request);

	/**
	 * set Response class.
	 * @param[in] request
	 */
	virtual void setResponse(Emwd::core::Response *response);

	/**
	 * Set Connection class
	 * @param connection
	 */
	virtual void setConnection(Emwd::core::Connection *connection);

	/**
	 * get Request class
	 * @return Request Request class set by setRequest()
	 */
	virtual Emwd::core::Request* getRequest();

	/**
	 * get Response class
	 * @return Request Request class set by setRequest()
	 */
	virtual Emwd::core::Response* getResponse();

	/**
	 * get Connection class
	 * @return
	 */
	virtual Emwd::core::Connection* getConnection();

	/**
	 * set Configuration class
	 * @param [in] Configuration config
	 */
	virtual void setConfiguration(Emwd::core::Configuration* configuration);

	/**
	 * get Configuration class
	 * @return Configuration class set by setConfig
	 */
	Emwd::core::Configuration* getConfiguration();
};

} }

#endif /* EMWD_CORE_APPLICATION_H_ */
