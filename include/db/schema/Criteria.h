// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Criteria.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_DB_CRITERIA_H_
#define EMWD_DB_CRITERIA_H_
// C++ header
#include <string>
#include <map>
#include <list>

// Emwd
#include <core/CoreComponent.h>

namespace Emwd { namespace db { namespace schema

/**
 * Criteria
 */
class Criteria : public Emwd::core::CoreComponent
{
public:
	std::string select;
	bool distinct;
	std::string condition;
	std::map<std::string, std::string> params;
	int limit;
	int offset;
	std::string order;
	std::string group;
	std::string join;
	std::string having;
};

} } }

#endif /* EMWD_DB_CRITERIA_H_ */
