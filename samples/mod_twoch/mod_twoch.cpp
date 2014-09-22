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

#include "controllers/TwoChController.h"

using namespace Emwd::core;
using namespace Emwd::web;

extern "C" module AP_MODULE_DECLARE_DATA twoch_module;

static Configuration *conf;
static Controller* controller;

static int twoch_handler(request_rec *r)
{
    if (strcmp(r->handler, "twoch")) {
        return DECLINED;
    }

    Request *request = new ApacheRequest(r);
    Response *response = new ApacheResponse(r);
    
    // Application
    WebApplication *app = new WebApplication();
    app->setRequest(request);
    app->setResponse(response);
    app->setConfiguration(conf);
    app->registerController("TwoChController", controller);
    app->registerRoute("/twoch/read", "TwoChController", "ReadAction");
    app->registerRoute("/twoch/post", "TwoChController", "PostAction");
    app->registerRoute("/twoch/list", "TwoChController", "ListAction");
    app->registerRoute("/twoch", "TwoChController", "TopAction");
    app->run();

    delete request;
    delete response;
    delete app;

    return OK;
}

static apr_status_t pool_destroy(void *data)
{
	delete conf;
	delete controller;
	return APR_SUCCESS;
}

static int pool_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
	conf = new Configuration();
    conf->readJson("/home/junya/Emwd/samples/mod_twoch/test.json");
    controller = new TwoChController();
	apr_pool_cleanup_register(pconf, s, pool_destroy, apr_pool_cleanup_null);
	return OK;
}

static void child_init(apr_pool_t *p, server_rec *s)
{
	;
}

static void register_hooks(apr_pool_t *p)
{
  ap_hook_handler(twoch_handler, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_post_config(pool_post_config, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_child_init(child_init, NULL, NULL, APR_HOOK_MIDDLE);
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
