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
    // Request and Response for Apache
    Request *request = new ApacheRequest(r);
    Response *response = new ApacheResponse(r);
    // Application
    WebApplication *app = new WebApplication();
    app->setRequest(request);
    app->setResponse(response);
    app->setConnection(connection);
    app->setConfiguration(conf);
    app->registerController("FrameworkBenchmarksController", controller);
    // Test type 1: JSON serialization
    app->registerRoute("/FrameworkBenchmarks/json", "FrameworkBenchmarksController", "JsonAction");
    // Test type 2: Single database query
    app->registerRoute("/FrameworkBenchmarks/db", "FrameworkBenchmarksController", "DbAction");
    // Test type 3: Multiple database queries
    app->registerRoute("/FrameworkBenchmarks/queries", "FrameworkBenchmarksController", "QueriesAction");
    // Test type 4: Fortunes
    app->registerRoute("/FrameworkBenchmarks/fortunes", "FrameworkBenchmarksController", "FortunesAction");
    // Test type 5: Database updates
    app->registerRoute("/FrameworkBenchmarks/updates", "FrameworkBenchmarksController", "UpdatesAction");
    // Test type 6: Plaintext
    app->registerRoute("/FrameworkBenchmarks/plaintext", "FrameworkBenchmarksController", "PlainTextAction");
    // Run
    // Todo: Need to catch exception?
    // Todo: Check return value
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
    conf->readJson("/home/junya/Emwd/samples/mod_FrameworkBenchmarks/fwb-conf.json");
    controller = new FrameworkBenchmarksController();
    apr_pool_cleanup_register(p, s, post_config_destroy, apr_pool_cleanup_null);
    return OK;
}

static apr_status_t child_init_destroy(void *data)
{
    connection->disconnect();
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
    connection->setCharset(Connection::UTF_8);

    int numOfPreparedStaatement = conf->getPreparedStatementCount();
    for (int i=0; i<numOfPreparedStaatement; i++)
    {
        connection->prepare(
            conf->getPreparedStatementNameByIndex(i),
            conf->getPreparedStatementByIndex(i)
        );
    }
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
