/*
 * ApacheRequest.h
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */

#ifndef EMWD_WEB_APACHE_REQUEST_H_
#define EMWD_WEB_APACHE_REQUEST_H_

#include <core/Request.h>

namespace Emwd { namespace web {

using namespace Emwd::core;

/**
 * ApacheRequest class
 * create Request class from request_rec
 */
class ApacheRequest : public Request
{
private:

public:
	virtual const char* getGet(const char* key)
	{
		return "empty";
	}

	virtual void setGet(const char* key, const char* value)
	{

	}

	virtual void setGets(std::map <const char*, const char*> gets)
	{

	}

	virtual const char* getPost(const char* key)
	{
		return "empty";
	}

	virtual void setPost(const char* key, const char *value)
	{

	}

	virtual void setContentType(const char* type)
	{

	}

	virtual const char* getContentType()
	{
		return "text/plain";
	}
};

} }

#endif /* APACHEREQUEST_H_ */
