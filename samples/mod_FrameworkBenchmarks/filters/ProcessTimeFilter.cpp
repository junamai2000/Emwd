// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// C headers
#include <sys/time.h>

// C++ headers
#include <fstream>
#include <iostream>

// Emwd
#include <web/Filter.h>

#include "filters/ProcessTimeFilter.h"

using namespace Emwd::core;
using namespace Emwd::web;

const char* ProcessTimeFilter::getComponentName()
{
    return "ProcessTimeFilter";
}

bool ProcessTimeFilter::preFilter(Controller* controller, Action* action)
{
    this->_start = this->getTimeofDaySec();
    std::cerr << "Started at "<< std::fixed << this->_start << std::endl;
    return true;
}

bool ProcessTimeFilter::postFilter(Controller* controller, Action* action)
{
    this->_end = this->getTimeofDaySec();
    std::cerr << "Finished at "<< std::fixed << this->_end << std::endl;
    std::cerr << std::fixed << (double)(this->_end - this->_start) << std::endl;
    return true;
}

double ProcessTimeFilter::getTimeofDaySec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}
