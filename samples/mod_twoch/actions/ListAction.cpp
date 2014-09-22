// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include "actions/ListAction.h"

const char* ListAction::getComponentName()
{
    return "ListAction";
}

bool ListAction::process()
{
    return true;
}
