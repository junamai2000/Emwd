// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * mod_FrameworkBenchmarks.cpp
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
#include <core/Connection.h>
#include <web/ApacheRequest.h>
#include <web/ApacheResponse.h>
#include <web/WebApplication.h>

#include "controllers/FrameworkBenchmarksController.h"

using namespace Emwd::core;
using namespace Emwd::web;

extern "C" module AP_MODULE_DECLARE_DATA FrameworkBenchmarks_module;

static Configuration *conf;
static Controller* controller;
static Connection* connection;

static int FrameworkBenchmarks_handler(request_rec *r)
{
    if (strcmp(r->handler, "frameworkbenchmarks")) {
        return DECLINED;
    }

    Request *request = new ApacheRequest(r);
    Response *response = new ApacheResponse(r);
    
    // Application
    WebApplication *app = new WebApplication();
    app->setRequest(request);
    app->setResponse(response);
    app->setConnection(connection);
    app->setConfiguration(conf);
    app->registerController("FrameworkBenchmarksController", controller);
    app->registerRoute("/FrameworkBenchmarks/json", "FrameworkBenchmarksController", "JsonAction");
    app->registerRoute("/FrameworkBenchmarks/db", "FrameworkBenchmarksController", "DbAction");
    app->registerRoute("/FrameworkBenchmarks/fortune", "FrameworkBenchmarksController", "FortuneAction");
    app->registerRoute("/FrameworkBenchmarks/plaintext", "FrameworkBenchmarksController", "PlainTextAction");
    app->run();

    delete request;
    delete response;
    delete app;
    return OK;
}

static apr_status_t post_config_destroy(void *data)
{
	delete conf;
	delete controller;
	return APR_SUCCESS;
}

static int post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
	conf = new Configuration();
    conf->readJson("/home/junya/Emwd/samples/mod_FrameworkBenchmarks/test.json");
    controller = new FrameworkBenchmarksController();
	apr_pool_cleanup_register(p, s, post_config_destroy, apr_pool_cleanup_null);
	return OK;
}

static apr_status_t child_init_destroy(void *data)
{
	delete connection;
	return APR_SUCCESS;
}

static void child_init(apr_pool_t *p, server_rec *s)
{
    connection = ConnectionManager::loadDriver(conf->getDatabaseDriverPath(), conf->getDatabaseDriver());
    connection->connect(
            conf->getDatabaseHost(),
            conf->getDatabasePort(),
            conf->getDatabaseUser(),
            conf->getDatabasePassword(),
            conf->getDatabaseName());
	apr_pool_cleanup_register(p, s, child_init_destroy, apr_pool_cleanup_null);
}

static void register_hooks(apr_pool_t *p)
{
  ap_hook_handler(FrameworkBenchmarks_handler, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_child_init(child_init, NULL, NULL, APR_HOOK_MIDDLE);
}

extern "C" {
    module AP_MODULE_DECLARE_DATA FrameworkBenchmarks_module = {
		STANDARD20_MODULE_STUFF,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		register_hooks
	};
};
