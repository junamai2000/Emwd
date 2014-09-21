// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Controller.cpp
 *
 *  Created on: 2014/09/06
 *      Author: Junya Namai
 */
#include <web/Controller.h>
#include <web/Action.h>
#include <web/Filter.h>
#include <web/HttpException.h>

namespace Emwd { namespace web {

/**
 * Get Application class
 * @return a pointer to Application class
 */
 Emwd::core::Application* Controller::getApplication()
 {
     return this->_app;
 }

 /**
  * Get Application class
  * @return a pointer to Application class
  */
 Emwd::core::Configuration* Controller::getConfiguration()
 {
     return this->_app->getConfiguration();
 }

 /**
  * Register Action with a name
  * @param name
  * @param action
  */
 void Controller::registerAction(const char* actionName, Action* action)
 {
     action->setController(this);
     this->_actions[actionName] = action;
 }

 /**
  * Check action class is registered or not
  * @param name
  * @return true if registered
  */
 bool Controller::hasAction(const char* actionName)
 {
     return this->_actions[actionName]==NULL? false:true;
 }

 /**
  * Register Filters
  * all filters will be executed before and after action class
  * @param actionName
  * @param filters
  */
 void Controller::registerFilter(const char* actionName, Filter* filters)
 {
     this->_filters[actionName] = filters;
 }

 /**
  * RUn Action with filters
  * @param app
  * @param action
  * @return true if action finishes successfully
  */
 bool Controller::run(Emwd::core::Application* app, const char* actionName)
 {
     this->init();
     if (!this->hasAction(actionName))
     {
         std::string message = "Requested Action Is Not Found";
         message += "(";
         message += actionName;
         message += ")";
         throw Emwd::web::HttpException(404, message.c_str());
     }

     this->_app = app;
     if (this->_filters.size() > 0)
     {
         Filter* filters = this->_filters[actionName];
         if (filters)
         {
             return filters->run(this, this->_actions[actionName]);
         }
     }
     return this->_actions[actionName]->run(this);
 }

 /**
  *
  */
 Controller::~Controller()
 {
     ;
 }

} }
