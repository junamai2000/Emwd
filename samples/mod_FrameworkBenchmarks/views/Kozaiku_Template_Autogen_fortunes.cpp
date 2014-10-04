// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
//==========================================================
// DO NOT EDIT. THIS FILE IS GENERATED BY Kozaiku.pl
//==========================================================
#include "Kozaiku_Template_Autogen.h"
using namespace Emwd::kozaiku;
// Header => start
#include <string>
#include <boost/lexical_cast.hpp>
#include <web/Helper.h>
#include "models/Fortune.h"
#include "views/View.h"

// Header => end
bool Kozaiku_Template_Autogen::display_fortunes(void* stash)
{
// Init => strt
	FortuneTmplArgs *args = (FortuneTmplArgs*)stash;

// Init => end
// Source => start
	args->output.append("<!DOCTYPE html>");
args->output.append("<html>");
args->output.append("<head>");
args->output.append("<title>Fortunes</title>");
args->output.append("</head>");
args->output.append("<body>");
args->output.append("<table>");
args->output.append("<tr><th>id</th><th>message</th></tr>");
Fortune::Fortunes::iterator it;
for (it = args->fortunes->begin(); it != args->fortunes->end(); ++it) {
args->output.append("<tr>");
args->output.append("<td>");
args->output.append(boost::lexical_cast<std::string>((*it)->id));
args->output.append("</td>");
args->output.append("<td>");
args->output.append(Emwd::web::Helper::encode((*it)->message));
args->output.append("</td>");
args->output.append("</tr>");
}
args->output.append("</table>");
args->output.append("</body>");
args->output.append("</html>");

// Source => end
	return true;
}

extern "C" int kozaiku_display_fortunes(void* stash)
{
	Emwd::kozaiku::Kozaiku_Template_Autogen tpl;
	tpl.display_fortunes(stash);
	return 1;
}
