// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include "actions/PostAction.h"

const char* PostAction::getComponentName()
{
    return "PostAction";
}

bool PostAction::process()
{
    return true;
}
