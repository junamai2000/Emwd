// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <web/Filter.h>

#include "controllers/FrameworkBenchmarksController.h"
#include "actions/JsonAction.h"
#include "actions/DbAction.h"
#include "actions/FortuneAction.h"
#include "actions/PlainTextAction.h"
#include "filters/ProcessTimeFilter.h"

using namespace Emwd::core;
using namespace Emwd::web;

void FrameworkBenchmarksController::init()
{
    // actions
    this->_jsonAction = new JsonAction();
    this->_dbAction = new DbAction();
    this->_fortuneAction = new FortuneAction();
    this->_plaintextAction = new PlainTextAction();
    // Process Time Filter chain
    // this->_timer = new ProcessTimeFilter();

    this->registerAction("JsonAction", this->_jsonAction);
    this->registerAction("DbAction", this->_dbAction);
    this->registerAction("FortuneAction", this->_fortuneAction);
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
    delete this->_fortuneAction;
    delete this->_plaintextAction;
}
