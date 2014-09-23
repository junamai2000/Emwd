#include <string>
#include <map>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <core/Model.h>
#include <validator/NumberValidator.h>

using namespace Emwd::core;
using namespace Emwd::validator;

class TestForm : public Model
{
public:
    const char* getComponentName()
    {
        return "TestForm";
    }

    bool processSave()
    {
    }

    void registerValidators()
    {
        this->attachValidator("default", new NumberValidator(1, "number", 100, 10, "too small", "too big"));
    }
};

class NumberValidatorTestSuite : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(NumberValidatorTestSuite);
    CPPUNIT_TEST(validNumber);
    CPPUNIT_TEST(invalidNumber);
    CPPUNIT_TEST_SUITE_END();
public:
    virtual void setUp(){}
    virtual void tearDown(){}
    void validNumber(){
        TestForm form;
        std::map<std::string, const char*> params;
        params["number"] = "10";
        form.setParams(params);
        form.registerValidators();
        form.setScenario("default");
        form.validate();
        CPPUNIT_ASSERT(form.hasError() == false);    
    }
    
    void invalidNumber(){
        TestForm form;
        std::map<std::string, const char*> params;
        params["number"] = "9";
        form.setParams(params);
        form.registerValidators();
        form.setScenario("default");
        form.validate();
        CPPUNIT_ASSERT(form.hasError() == true);    
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(NumberValidatorTestSuite);

int main(){
    CPPUNIT_NS::TestResult controller;
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener( &result );       
    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener( &progress );     
    CPPUNIT_NS::TestRunner runner;
    runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
    runner.run( controller );

    return result.wasSuccessful() ? 0 : 1;
}
