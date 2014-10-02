// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
// C++ header
#include <string>
#include <core/Response.h>
#include <core/Connection.h>
#include <web/Controller.h>
#include <kozaiku/Kozaiku.h>

#include "actions/FortunesAction.h"
#include "models/Fortune.h"

using namespace Emwd::core;
using namespace Emwd::kozaiku;

const char* FortunesAction::getComponentName()
{
    return "FortuneAction";
}

bool FortunesAction::process()
{
	Response *response = this->getController()->getApplication()->getResponse();
	Connection *connection= this->getController()->getApplication()->getConnection();
	//i Kozaiku *kozaiku = new Kozaiku("/Users/junya/Documents/project/emwd/include/kozaiku/Kozaiku_Template_Autogen.so");

	typedef struct _FortuneTmplArgs
	{
		std::string output;
		Fortune::Fortunes fortunes;
	} FortuneTmplArgs;

	FortuneTmplArgs args;
	Fortune::Fortunes *fortunes = Fortune::findAll(connection);
	Fortune::Fortunes::iterator it;
	for (it = fortunes->begin(); it != fortunes->end(); ++it)
	{
		response->setBody((*it)->message);
	}
	// kozaiku->display("fortunes", &args);
	response->setContentType("text/html");
	// response->setBody(args.output.c_str());
    return true;
}
