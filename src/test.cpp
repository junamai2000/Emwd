// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <core/Configuration.h>
#include <core/Model.h>
#include <web/WebApplication.h>
#include <web/DummyRequest.h>
#include <web/Filter.h>
#include <validator/NumberValidator.h>
#include <validator/LengthValidator.h>
#include <validator/RequiredValidator.h>
#include <validator/FunctionPointerValidator.h>

#include <picojson/picojson.h>

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::validator;

/**
 * JsonConfiguration
 */
class JsonConfiguration
{
private:
	/**
	 * parsed json
	 */
	picojson::value _json;

public:
	/**
	 * Open Json
	 * @param path
	 * @return
	 */
	bool open(const char* path)
	{
		std::ifstream file(path);
		if (file.fail())
		{
			std::cout << "Failed to open file : " << path << std::endl;
			return false;
		}

		std::istreambuf_iterator<char> first(file);
		std::istreambuf_iterator<char> last;
		std::string json_in(first, last);

		std::string error;
		picojson::parse(this->_json, json_in.begin(), json_in.end(), &error);
		if (!error.empty())
		{
			std::cout << "Json parse error" << std::endl;
			return false;
		}
		return true;
	}

	/**
	 * Get application name
	 * @return string from json
	 */
	const char* getApplicationName()
	{
		return this->_json.get<picojson::object>()["web"].get<picojson::object>()["name"].get<std::string>().c_str();
	}
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
		this->attachValidator("default", new FunctionPointerValidator(SampleForm::complicatedValidator));
	}

	static int complicatedValidator(Model* model)
	{
		// 複数の要素の依存をチェックするようなチェックが実装できるはず
		int x = atoi(model->getParam("x").c_str());
		int y = atoi(model->getParam("y").c_str());
		if (x == y)
		{
			model->addError(4, "x and y can not be the same.");
			return false;
		}
		std::cout << atoi(model->getParam("x").c_str()) << std::endl;
		std::cout << atoi(model->getParam("y").c_str()) << std::endl;
		std::cout << "custom validator against: x="<< model->getParam("x") << " and y=" << model->getParam("y") << std::endl;
		return true;
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
		// test for config
		JsonConfiguration *conf = (JsonConfiguration*)this->getController()->getConfiguration()->getStorage();
		std::cout << "Start Application : " << conf->getApplicationName() << std::endl;

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
				std::cout << "Error Code=" << errors[i]->getErrorCode() << " : "<< errors[i]->getMessage() << std::endl;
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
 * ProcessTimeFilter class
 */
class ProcessTimeFilter : public Filter
{
private:
	clock_t _start;
	clock_t _end;
public:
	virtual const char* getComponentName()
	{
		return "ProcessTimeFilter";
	}

	virtual bool preFilter(Controller* controller, Action* action)
	{
		this->_start = clock();
		std::cout << "Started at "<< std::fixed << this->_start << std::endl;
		return true;
	}

	virtual bool postFilter(Controller* controller, Action* action)
	{
		this->_end = clock();
		std::cout << "Finished at "<< std::fixed << this->_end << std::endl;
		std::cout << std::fixed << (double)(this->_end - this->_start)/CLOCKS_PER_SEC << "秒かかりました" << std::endl;
		return true;
	}
};

/**
 * SampleController class
 */
class SampleController : public Controller
{
private:
	Filter* filter;
	Filter* filter2;
	Filter* timer;
	Action* action;
	SampleEmail* email;

public:
	/**
	 *
	 * @return
	 */
	virtual const char* getComponentName()
	{
		return "SampleController";
	}

	/**
	 *
	 */
	void init()
	{
		// Email logic, which is a sample
		// by using this, users can isolate email logic from a core logig
		this->email = new SampleEmail;

		// sample action
		this->action = new SampleAction;
		this->action->attachEvent("beforeRun", email);

		// filter chain
		// you may use this to authorize users (but not implmented yet)
		this->filter = new SampleFilter();
		this->filter2 = new Sample2Filter();
		this->filter->setNextFilter(filter2);

		// sample to check process time in action class
		this->timer = new ProcessTimeFilter();

		this->registerAction("sampleAction", action);
		this->registerAction("sample2Action", action);
		this->registerFilter("sampleAction", filter);
		this->registerFilter("sample2Action", timer);
	}

	~SampleController()
	{
		delete this->filter;
		delete this->filter2;
		delete this->timer;
		delete this->action;
		delete this->email;
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
	if (argv[1] == NULL)
	{
		std::cerr << "need request path" << std::endl;
		return 1;
	}

	JsonConfiguration *json = new JsonConfiguration();
	json->open("./test.json");

	Configuration *conf = new Configuration();
	conf->setStorage(json);

	// create dummy request to emulate http get request
	Request *request = new DummyRequest();
	request->setGet("user", "123456");
	request->setGet("price", "100");
	request->setGet("x", "100");
	request->setGet("y", "100");
	request->setRequestUrl(argv[1]);

	// Sample controller
	Controller* controller = new SampleController();
	controller->init();

	// Application
	WebApplication *app = new WebApplication();
	app->setRequest(request);
	app->setConfiguration(conf);
	app->registerController("sampleController", controller);
	app->registerRoute("/sample/do", "sampleController", "sampleAction");
	app->registerRoute("/sample/do2", "sampleController", "sample2Action");
	app->run();

	// std::cout << request->getResponse() << std::endl;

	// clean up, sould I use auto_ptr or somethig?
	delete json;
	delete conf;
	delete request;
	delete controller;
	delete app;

	return 0;
}
