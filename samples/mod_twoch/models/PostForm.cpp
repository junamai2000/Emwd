// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <core/Configuration.h>
#include <core/Model.h>
#include <core/XmlSerializable.h>
#include <web/WebApplication.h>
#include <web/DummyRequest.h>
#include <web/DummyResponse.h>
#include <web/Filter.h>
#include <validator/NumberValidator.h>
#include <validator/LengthValidator.h>
#include <validator/RequiredValidator.h>
#include <validator/FunctionPointerValidator.h>

#include <picojson/picojson.h>
// #include <kozaiku/Kozaiku.h>

#include "PostForm.h"

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::validator;
// using namespace Emwd::kozaiku;

/**
 * PostForm class
 */
const char* PostForm::getComponentName()
{
    return "PostForm";
}

void PostForm::registerValidators()
{
    this->attachValidator("name", new LengthValidator(1, "name", 10, 5, "名前が短すぎ", "名前が長過ぎ"));
    this->attachValidator("email", new LengthValidator(2, "email", 10, 5,"年齢は必須項目です"));
    this->attachValidator("text", new LengthValidator(3, "age", 10, 5, "年齢は必須項目です"));
}

/*
int PostForm::complicatedValidator(Model* model)
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
*/

bool PostForm::processSave()
{
    this->_name = this->getParam("name").c_str();
    this->_email = this->getParam("email").c_str();
    this->_text = this->getParam("text").c_str();

    // save this somewhere
    // Archive ar;
    // ar << this;

    /*
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
    */
    return true;
}
