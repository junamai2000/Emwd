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
#include <web/ApacheRequest.h>
#include <web/ApacheResponse.h>
#include <web/WebApplication.h>

#include "config/JsonConfiguration.h"
#include "controllers/TwoChController.h"

using namespace Emwd::core;
using namespace Emwd::web;

extern "C" module AP_MODULE_DECLARE_DATA twoch_module;


static int twoch_handler(request_rec *r)
{
    if (strcmp(r->handler, "twoch")) {
        return DECLINED;
    }

    JsonConfiguration *json = new JsonConfiguration();
    json->open("/home/junya/Emwd/samples/mod_twoch/test.json");

    Configuration *conf = new Configuration();
    conf->setStorage(json);
    
    Request *request = new ApacheRequest(r);
    Response *response = new ApacheResponse(r);
    
    // Sample controller
    Controller* controller = new TwoChController();

    // Application
    WebApplication *app = new WebApplication();
    app->setRequest(request);
    app->setResponse(response);
    app->setConfiguration(conf);
    app->registerController("TwoChController", controller);
    app->registerRoute("/twoch", "TwoChController", "TopAction");
    app->registerRoute("/twoch/read", "TwoChController", "ReadAction");
    app->registerRoute("/twoch/post", "TwoChController", "PostAction");
    app->registerRoute("/twoch/list", "TwoChController", "ListAction");
    app->run();

    // ap_rputs(response->getBody(), r);
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
  ap_hook_handler(twoch_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

extern "C" {
    module AP_MODULE_DECLARE_DATA twoch_module = {
		STANDARD20_MODULE_STUFF,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		register_hooks
	};
};
