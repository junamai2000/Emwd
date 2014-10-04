// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * ActiveRecord.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_DB_ACTIVERECORD_H_
#define EMWD_DB_ACTIVERECORD_H_
// C header
#include <stdlib.h>

// C++ header
#include <string>
#include <map>
#include <list>
#include <sstream>

// Emwd
#include <core/Model.h>
#include <core/Connection.h>

#include <db/Criteria.h>
#include <db/SqlBuilder.h>

#define EMWD_ACTIVE_RECORD_MAKE_COLUMN(col, type) this->makeColumn(#col, type, (void*)&this->col)
#define EMWD_ACTIVE_RECORD_MAKE_PK(col, type) this->makePrimaryKey(#col, type, (void*)&this->col)

namespace Emwd { namespace db {

/**
 * ActiveRecord
 */
class ActiveRecord : public Emwd::core::Model
{
private:
	ActiveRecord() {};

protected:
	enum COLUMN_TYPE {COL_BOOL=1, COL_INT, COL_LONG, COL_FLOAT, COL_DOUBLE, COL_DATE, COL_BIN, COL_CHAR, COL_STRING};
	struct FIELD_META {
		COLUMN_TYPE type;
		void* member;
	};
	std::map<std::string, FIELD_META> _meta;

	struct PRIMARY_KEY {
		const char* col;
		COLUMN_TYPE type;
		union
		{
			int ival;
			bool bval;
			long lval;
			float fval;
			double dval;
			const char* cval;
		};
		void* member;
	};
	std::list<PRIMARY_KEY> _pks;
	Emwd::core::Connection* _connection;

	std::map<std::string, FIELD_META>& getMeta()
	{
		return this->_meta;
	}

public:
	explicit ActiveRecord(Emwd::core::Connection *connection) {
		this->_connection = connection;
		//this->setTableSchema();
	};

	virtual void makeColumn(const char* col, COLUMN_TYPE type, void* member)
	{
		FIELD_META meta;
		meta.type = type;
		meta.member = member;
		this->_meta[col] = meta;
	}

	virtual void makePrimaryKey(const char* col, COLUMN_TYPE type, void* member)
	{
		PRIMARY_KEY pk;
		pk.col = col;
		pk.type = type;
		pk.member = member;
		this->_pks.push_back(pk);
	}

	virtual void restoreRecord(const char* col, const char* value, std::map<std::string, FIELD_META> &meta)
	{
		FIELD_META field = meta[col];
		if(field.type == COL_INT)
		{
			int *tmpInt = (int*)field.member;
			*tmpInt = atoi(value);
		}
		else if (field.type == COL_CHAR)
		{
			const char **tmpChar = (const char**)field.member;
			*tmpChar = value;
		}
		else if (field.type == COL_STRING)
		{
			std::string *tmpChar = (std::string *)field.member;
			*tmpChar = value;
		}
		else if (field.type == COL_LONG)
		{
			long *tmpLong = (long*)field.member;
			*tmpLong = atol(value);
		}
		else if (field.type == COL_BOOL)
		{
			std::string tmp = value;
			bool *tmpBool = (bool*) field.member;
			if (tmp == "1" or tmp == "true")
			{
				*tmpBool = true;
			}
			else
			{
				*tmpBool = false;
			}
		}
		else if (field.type == COL_FLOAT)
		{
			float *tmpFloat = (float*)field.member;
			*tmpFloat = (float)atof(value);
		}
		else if (field.type == COL_DOUBLE)
		{
			double *tmpDouble = (double*) field.member;
			*tmpDouble = atof(value);
		}
		else if (field.type == COL_DATE)
		{
			// not implemented yet
		}
		else if (field.type == COL_BIN)
		{
			// not implemented yet
		}
	}

	virtual void setTableSchema() = 0;

	Emwd::core::Connection *getConnection()
	{
		return this->_connection;
	}

	std::string makePkCondition(std::list<PRIMARY_KEY> &pk)
	{
		std::string sql;
		std::list<PRIMARY_KEY>::iterator it = pk.begin();
		for(;it != pk.end(); ++it)
		{
			PRIMARY_KEY pk = *it;
			sql = pk.col;
			sql += "=";
			if (pk.type==COL_INT)
			{
				std::stringstream ss;
				ss << pk.ival;
				sql += ss.str();
			}
			else if (pk.type==COL_CHAR)
			{
				sql += pk.cval;
			}
		}
		return sql;
	}

	bool findByPrimaryKey(std::list<PRIMARY_KEY> &pk)
	{
		Emwd::db::Criteria *criteria = new Emwd::db::Criteria();
		criteria->select = "*";
		criteria->condition = this->makePkCondition(pk);
		criteria->limit = 1;

		Emwd::core::Connection::Results results;
		Emwd::db::SqlBuilder *builder = SqlBuilderManager::createSqlBuilder(this->_connection);
		std::string sql = builder->buildFindCommand(this, criteria);
		if (!this->_connection->execute(sql.c_str(), results))
		{
			std::cerr << "query error: " << sql << std::endl;
			return false;
		}

		Emwd::core::Connection::Records::iterator rIt;
		int index = 0;
		for (rIt = results.records.begin(); rIt != results.records.end(); ++rIt)
		{
			Emwd::core::Connection::Record::iterator rIt2;
			int index2 = 0;
			for (rIt2 = (*rIt).begin(); rIt2 != (*rIt).end(); ++rIt2)
			{
				this->restoreRecord(results.fields[index2].c_str(), (*rIt2).c_str(), this->getMeta());
				index2++;
			}
			index++;
		}
		delete criteria;
		return true;
	}

	// T find(int id);
	// bool findAll(Emwd::db:schema::Criteria criteria);
};

} }

#endif /* EMWD_DB_ACTIVERECORD_H_ */
