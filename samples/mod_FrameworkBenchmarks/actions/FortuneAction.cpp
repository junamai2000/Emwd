// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include "actions/FortuneAction.h"

const char* FortuneAction::getComponentName()
{
    return "FortuneAction";
}

bool FortuneAction::process()
{
    return true;
}
