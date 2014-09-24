// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ActiveRecord.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_DB_ACTIVERECORD_H_
#define EMWD_DB_ACTIVERECORD_H_
// C++ header
#include <string>
#include <map>
#include <list>

// Emwd
#include <core/Model.h>

namespace Emwd { namespace db { namespace ar

class Connection;

/**
 * ActiveRecord
 */
class ActiveRecord : public Emwd::core::Model
{
private:
	ActiveRecord() {};

protected:
	enum COLUMN_TYPE {COL_INT, COL_LONG, COL_FLOAT, COL_DOUBLE, COL_DATE, COL_BIN, COL_CHAR};
	struct FILE_PAIR {
		const char* col;
		void* member;
	};
	std::map<std::string, COLUMN_TYPE> _meta;

	struct PRIMARY_KEY {
		const char* col;
		COLUMN_TYPE type;
	};
	std::list<PRIMARY_KEY> _pks;

	Emwd::db::Connection* _connection;

public:
	ActiveRecord(Emwd::db::Connection *);
	virtual void setup() = 0;


	// template <typename T> bool findByPk(T id);


};

} } }

#endif /* EMWD_DB_ACTIVERECORD_H_ */
