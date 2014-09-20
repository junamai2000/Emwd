// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * hello_world.cpp
 *
 *  Created on: 2014/09/07
 *      Author: Junya Namai
 */
#include "ap_config.h"
#include "apr.h"
#include "apr_lib.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_want.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_request.h"
#include "http_protocol.h"

#include <string>

#include <core/Configuration.h>
#include <core/Model.h>
#include <core/XmlSerializable.h>
#include <web/WebApplication.h>
#include <web/ApacheRequest.h>
#include <web/DummyResponse.h>
#include <web/Filter.h>
#include <validator/NumberValidator.h>
#include <validator/LengthValidator.h>
#include <validator/RequiredValidator.h>
#include <validator/FunctionPointerValidator.h>

#include "test.h"

extern "C" module AP_MODULE_DECLARE_DATA cpphello_module;

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::validator;

static int cpphello_handler(request_rec *r)
{
    if (strcmp(r->handler, "cpphello")) {
        return DECLINED;
    }

    r->content_type = "text/html"; 

    JsonConfiguration *json = new JsonConfiguration();
    json->open("/home/junya/Emwd/src/test.json");

    Configuration *conf = new Configuration();
    conf->setStorage(json);

    Request *request = new ApacheRequest(r);

    DummyResponse *response = new DummyResponse();
    request->setResponse(response);

    // Sample controller
    Controller* controller = new SampleController();

    // Application
    WebApplication *app = new WebApplication();
    app->setRequest(request);
    app->setConfiguration(conf);
    app->registerController("sampleController", controller);
    app->registerRoute("/sample/do", "sampleController", "sampleAction");
    app->registerRoute("/sample/do2", "sampleController", "sample2Action");
    app->registerRoute("/sample/do3", "sampleController", "sample3Action");
    app->run();

    ap_rputs(response->getBody(), r);

    // clean up, sould I use auto_ptr or somethig?
    delete json;
    delete conf;
    delete request;
    delete response;
    delete controller;
    delete app;

    return OK;
}

static void register_hooks(apr_pool_t *p)
{
  // ap_hook_fixups(cpphello_handler,NULL,NULL,APR_HOOK_MIDDLE);
  ap_hook_handler(cpphello_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

extern "C" {
    module AP_MODULE_DECLARE_DATA cpphello_module = {
		STANDARD20_MODULE_STUFF,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		register_hooks
	};
};
