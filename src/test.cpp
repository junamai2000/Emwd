#include <core/Configuration.h>
#include <core/Model.h>
#include <web/WebApplication.h>
#include <web/DummyRequest.h>
#include <web/Filter.h>
#include <validator/NumberValidator.h>
#include <validator/LengthValidator.h>
#include <validator/RequiredValidator.h>

using namespace Emwd::web;
using namespace Emwd::validator;

/**
 * SampleController class
 */
class SampleController : public Controller
{

};

/**
 * SampleEmail class
 */
class SampleEmail : public CoreComponent
{
public:

	/**
	 * Get component name
	 * @return component name
	 */
	virtual const char* getComponentName()
	{
		return "SampleEmail";
	}

	/**
	 * On Event
	 * @param conponentName
	 * @param eventName
	 * @param obj
	 * @return
	 */
	virtual bool onEvent(const char *conponentName, const char* eventName, CoreComponent *obj)
	{
		// implement email program here
		// you can isolate email program from core logic with event handler
		std::cout << conponentName << ":" << eventName << " => Send Email" << std::endl;
		return 0;
	}
};

/**
 * SampleForm class
 */
class SampleForm : public Model
{
private:
	int _price;
	int _age;
	const char* _user;
public:
	virtual const char* getComponentName()
	{
		return "SampleForm";
	}

	void registerValidators()
	{
		this->attachValidator("default", new NumberValidator(1, "price", 100, 10, "価格が小さすぎ", "価格が大きすぎ"));
		this->attachValidator("default", new LengthValidator(2, "user", 10, 5, "名前が短すぎ", "名前が長過ぎ"));
		this->attachValidator("default", new RequiredValidator(3, "age", "年齢は必須項目です"));
	}

	bool processSave()
	{
		this->_price = std::stoi(this->getParam("price"));
		this->_user = this->getParam("user").c_str();
		this->_age = 30;

		// save this somewhere
		// Archive ar;
		// ar << this;

		return true;
	}
};

/**
 * SampleAction class
 */
class SampleAction : public Action
{
public:
	virtual const char* getComponentName()
	{
		return "SampleAction";
	}

	bool process()
	{
		SampleForm form;
		form.setParams(this->getController()->getApplication()->getRequest()->getGets());
		form.registerValidators();
		form.setScenario("default");
		if (form.save())
		{
			std::cout << "SampleAction run success!" << std::endl;
		}
		else
		{
			std::vector<Error *> errors = form.getErrors();
			int numOfItems = errors.size();
			for (int i=0; i<numOfItems; i++)
			{
				std::cout << errors[i]->getErrorCode() << " : "<< errors[i]->getMessage() << std::endl;
			}
		}
		return true;
	}
};

/**
 * SampleFilter class
 */
class SampleFilter : public Filter
{
public:
	virtual const char* getComponentName()
	{
		return "SampleFilter";
	}

	virtual bool preFilter(Controller* controller, Action* action)
	{
		for (int i=0; i<=this->_filterDepth; i++)
			std::cout << "=";
		std::cout << "> preFilter in SampleFilter" << std::endl;
		return true;
	}

	virtual bool postFilter(Controller* controller, Action* action)
	{
		for (int i=0; i<=this->_filterDepth; i++)
			std::cout << "=";
		std::cout << "> postFilter in SampleFilter" << std::endl;
		return true;
	}
};

/**
 * Sample2Filter class
 */
class Sample2Filter : public Filter
{
public:
	virtual const char* getComponentName()
	{
		return "Sample2Filter";
	}

	virtual bool preFilter(Controller* controller, Action* action)
	{
		for (int i=0; i<=this->_filterDepth; i++)
			std::cout << "=";
		std::cout << "> preFilter in SampleFilter2" << std::endl;
		return true;
	}

	virtual bool postFilter(Controller* controller, Action* action)
	{
		for (int i=0; i<=this->_filterDepth; i++)
					std::cout << "=";
		std::cout << "> postFilter in SampleFilter2" << std::endl;
		return true;
	}

};

/**
 * Main
 * @param argc
 * @param argv
 * @return 0 if finishes successfully
 */
int main (int argc,char **argv)
{
	Configuration *conf = new Configuration();

	if (argv[1] == NULL)
	{
		std::cerr << "need request path" << std::endl;
		return 1;
	}

	// create dummy request to emulate http get request
	Request *request = new DummyRequest();
	request->setGet("user", "aa");
	request->setGet("price", "1000");
	request->setRequestUrl(argv[1]);

	// Email logic, which is a sample
	// by using this, users can isolate email logic from a core logig
	SampleEmail *email = new SampleEmail;

	// sample action
	Action* action = new SampleAction;
	action->attachEvent("beforeRun", email);

	// filter chain
	// you may use this to authorize users (but not implmented yet)
	Filter* filter = new SampleFilter();
	Filter* filter2 = new Sample2Filter();
	filter->setNextFilter(filter2);

	// Sample controller
	Controller* controller = new SampleController;
	controller->registerAction("sampleAction", action);
	controller->registerAction("sample2Action", action);
	controller->registerFilter("sampleAction", filter);

	// Application
	WebApplication *app = new WebApplication();
	app->setRequest(request);
	app->setConfig(conf);
	app->registerController("sampleController", controller);
	app->registerRoute("/sample/do", "sampleController", "sampleAction");
	app->registerRoute("/sample/do2", "sampleController", "sample2Action");
	app->run();

	// std::cout << request->getResponse() << std::endl;

	// clean up, sould I use auto_ptr or somethig?
	delete conf;
	delete request;
	delete action;
	delete email;
	delete controller;
	delete app;

	return 0;
}
