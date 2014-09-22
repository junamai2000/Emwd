// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <web/Filter.h>

#include "controllers/TwoChController.h"
#include "actions/ReadAction.h"
#include "actions/ListAction.h"
#include "actions/TopAction.h"
#include "actions/PostAction.h"
#include "filters/ProcessTimeFilter.h"

using namespace Emwd::core;
using namespace Emwd::web;

void TwoChController::init()
{
    // actions
    this->_readAction = new ReadAction();
    this->_listAction = new ListAction();
    this->_topAction = new TopAction();
    this->_postAction = new PostAction();
    // Process Time Filter chain
    this->_timer = new ProcessTimeFilter();

    this->registerAction("ReadAction", this->_readAction);
    this->registerAction("TopAction", this->_topAction);
    this->registerAction("ListAction", this->_listAction);
    this->registerAction("PostAction", this->_postAction);

    this->registerFilter("ReadAction", this->_timer);
}

const char* TwoChController::getComponentName()
{
    return "TwoChController";
}

TwoChController::~TwoChController()
{
    delete this->_timer;
    delete this->_readAction;
    delete this->_topAction;
    delete this->_listAction;
    delete this->_postAction;
}
