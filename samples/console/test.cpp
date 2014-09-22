// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include <fstream>

#include <core/Configuration.h>
#include <core/Model.h>
#include <core/XmlSerializable.h>
#include <web/WebApplication.h>
#include <web/DummyRequest.h>
#include <web/DummyResponse.h>
#include <web/Filter.h>
#include <web/Action.h>
#include <web/Controller.h>
#include <db/Connection.h>
#include <db/ar/ActiveRecord.h>
#include <db/SqlBuilder.h>
#include <validator/NumberValidator.h>
#include <validator/LengthValidator.h>
#include <validator/RequiredValidator.h>
#include <validator/FunctionPointerValidator.h>
// #include <kozaiku/Kozaiku.h>

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::validator;
using namespace Emwd::db;
// using namespace Emwd::kozaiku;

/**
 * Serializable User Information
 */
class UserInfo : public XmlSerializable
{
public:
	const char *name;
	int age;
	const char *prefecture;

	virtual std::string serialize()
	{
		XmlSerializableComposite data;
		data.add(new XmlSerializableObject<const char*>("Name",this->name));
		data.add(new XmlSerializableObject<int>("Age",this->age));
		data.add(new XmlSerializableObject<const char*>("Prefecture",this->prefecture));
		return data.serialize();
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
		this->_price = atoi(this->getParam("price").c_str());
		this->_user = this->getParam("user").c_str();
		this->_age = 30;

		// save this somewhere
		// Archive ar;
		// ar << this;

		XmlSerializableComposite data;
		data.setElementName("ResultSet");
		data.add(new XmlSerializableObject<int>("Year", 2014));
		data.add(new XmlSerializableObject<const char*>("Month", "Sep"));
		data.add(new XmlSerializableObject<int>("Date", 19));

		UserInfo *info = new UserInfo();
		info->name = "Junya";
		info->age = 30;
		info->prefecture = "Tokyo";
		data.add(new XmlSerializableObject<UserInfo*>("User", info));

		std::cout << data.serialize() << std::endl;
		delete info;
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
		//Configuration *conf = this->getController()->getConfiguration();
		//Response *response = this->getController()->getApplication()->getRequest()->getResponse();
		//(*response) << "Start Application : " << conf->getApplicationName(); // << std::endl;
		// this->getController()->getApplication()->getRequest()->getResponse()->setBody("SampleAction run success!");

		SampleForm form;
		// form.setParams(this->getController()->getApplication()->getRequest()->getGets());
		form.registerValidators();
		form.setScenario("default");
		if (form.save())
		{
			this->getController()->getApplication()->getResponse()->setBody("SampleAction run success!");
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
		// Kozaiku *kozaiku = new Kozaiku("/Users/junya/Documents/project/emwd/include/kozaiku/Kozaiku_Template_Autogen.so");
		// std::string output;
		// kozaiku->display("sample", &output);
		// std::cout << output << std::endl;
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

	/**
	 * Init and register action and filters
	 */
	virtual void init()
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
	~SampleController()
	{
		delete this->filter;
		delete this->filter2;
		delete this->timer;
		delete this->action;
		delete this->email;
	}
};

class Category : public ActiveRecord
{
public:
    int categoryId;
    const char* categoryName;
    int parentCategoryId;
    bool isValid;
    long flags;

    typedef std::list<Category*> Categories;

    virtual const char* getComponentName()
    {
        return "Category";
    }

    virtual bool processSave() {return true;}
    virtual void registerValidators() {return;}

    Category(Connection *connection) : ActiveRecord(connection)
    {
    	this->setTableSchema();
    }

    #define EMWD_ACTIVE_RECORD_MAKE_COLUMN(col, type) this->makeColumn(#col, type, (void*)&this->col)
    virtual void setTableSchema()
    {
    	EMWD_ACTIVE_RECORD_MAKE_COLUMN(categoryId, COL_INT);
    	EMWD_ACTIVE_RECORD_MAKE_COLUMN(categoryName, COL_CHAR);
    	EMWD_ACTIVE_RECORD_MAKE_COLUMN(parentCategoryId, COL_INT);
    	EMWD_ACTIVE_RECORD_MAKE_COLUMN(isValid, COL_BOOL);
    	EMWD_ACTIVE_RECORD_MAKE_COLUMN(flags, COL_LONG);
        this->makePrimaryKey("categoryId", COL_INT);
    }

    static Category* findByPk(int id, Connection *con)
    {
    	PRIMARY_KEY pk;
    	pk.ival = id;
    	pk.type = COL_INT;
    	pk.col = "categoryId";
    	std::list<PRIMARY_KEY> pks;
    	pks.push_back(pk);
    	Category *category = new Category(con);
    	category->findByPrimaryKey(pks);
    	return category;
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

	Configuration *conf = new Configuration();
	conf->readJson("./test.json");

    Connection *con = ConnectionManager::loadDriver(conf->getDatabaseDriverPath(), conf->getDatabaseDriver());
    if (!con)
    {
    	std::cerr << "can not open driver" << std::endl;
    	return 1;
    }
    con->connect(
    		conf->getDatabaseHost(),
    		conf->getDatabasePort(),
    		conf->getDatabaseUser(),
    		conf->getDatabasePassword(),
    		conf->getDatabaseName());

    Category *category = Category::findByPk(1, con);
    std::cout << "CategoryId: " << category->categoryId << std::endl;
    std::cout << "CategoryName: " << category->categoryName << std::endl;
    std::cout << "parentCategoryId: " << category->parentCategoryId << std::endl;
    delete category;
    return 1;

	// create dummy request to emulate http get request
	Request *request = new DummyRequest();
	request->setGet("user", "123456");
	request->setGet("price", "100");
	request->setGet("age", "100");
	request->setGet("x", "100");
	request->setGet("y", "101");
	request->setRequestUrl(argv[1]);

	DummyResponse *response = new DummyResponse();

	// Sample controller
	Controller* controller = new SampleController();

	// Application
	WebApplication *app = new WebApplication();
	app->setRequest(request);
	app->setResponse(response);
	app->setConfiguration(conf);
	app->registerController("sampleController", controller);
	app->registerRoute("/sample/do", "sampleController", "sampleAction");
	app->registerRoute("/sample/do2", "sampleController", "sample2Action");
	app->registerRoute("/sample/do3", "sampleController", "sample3Action");
	app->run();

	std::cout << response->getStatus() << std::endl;
	std::cout << response->getBody() << std::endl;

	con->disconnect();
	delete con;
	delete conf;
	delete request;
	delete response;
	delete controller;
	delete app;

	return 0;
}
