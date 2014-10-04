// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <web/Filter.h>

#include "controllers/FrameworkBenchmarksController.h"
#include "actions/JsonAction.h"
#include "actions/DbAction.h"
#include "actions/QueriesAction.h"
#include "actions/FortunesAction.h"
#include "actions/UpdatesAction.h"
#include "actions/PlainTextAction.h"
#include "filters/ProcessTimeFilter.h"

using namespace Emwd::core;
using namespace Emwd::web;

void FrameworkBenchmarksController::init()
{
    // actions
    this->_jsonAction = new JsonAction();
    this->_dbAction = new DbAction();
    this->_queriesAction = new QueriesAction();
    this->_fortunesAction = new FortunesAction();
    this->_updatesAction = new UpdatesAction();
    this->_plaintextAction = new PlainTextAction();
    // Process Time Filter chain
    // this->_timer = new ProcessTimeFilter();

    this->registerAction("JsonAction", this->_jsonAction);
    this->registerAction("DbAction", this->_dbAction);
    this->registerAction("QueriesAction", this->_queriesAction);
    this->registerAction("FortunesAction", this->_fortunesAction);
    this->registerAction("UpdatesAction", this->_updatesAction);
    this->registerAction("PlainTextAction", this->_plaintextAction);

    // this->registerFilter("JsonAction", this->_timer);
}

const char* FrameworkBenchmarksController::getComponentName()
{
    return "FrameworkBenchmarksController";
}

FrameworkBenchmarksController::~FrameworkBenchmarksController()
{
    // delete this->_timer;
    delete this->_jsonAction;
    delete this->_dbAction;
    delete this->_fortunesAction;
    delete this->_plaintextAction;
    delete this->_updatesAction;
    delete this->_queriesAction;
}
