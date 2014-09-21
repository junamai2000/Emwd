// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <web/Filter.h>

#include "controllers/TwoChController.h"
#include "actions/ReadAction.h"
#include "filters/ProcessTimeFilter.h"

using namespace Emwd::core;
using namespace Emwd::web;

void TwoChController::init()
{
    // Read action
    this->action = new ReadAction();
    // Process Time Filter chain
    this->timer = new ProcessTimeFilter();

    this->registerAction("ReadAction", action);
    this->registerFilter("ReadAction", timer);
}

const char* TwoChController::getComponentName()
{
    return "TwoChController";
}

TwoChController::~TwoChController()
{
    delete this->timer;
    delete this->action;
}
