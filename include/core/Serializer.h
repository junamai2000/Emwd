// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Response.h
 *
 *  Created on: 2014/09/19
 *      Author: Junya Namai
 *      テンプレートの特殊化とかSFINAEとか、メタプログラムをすればもっと実装が簡単になるはず
 */

#ifndef EMWD_CORE_SERIALIZER_H_
#define EMWD_CORE_SERIALIZER_H_

#include <string>
#include <vector>
#include <sstream>

namespace Emwd { namespace core {

/**
 * SerializableComponent
 */
class SerializableComponent
{
protected:
	std::stringstream _serialized;
public:
	virtual std::string serialize() = 0;
	virtual ~SerializableComponent() {}
};

/**
 * SerializableObject
 */
template<class T>
class SerializableObject : public SerializableComponent
{
private:
	const char *_name;
	T *_object;

public:
	SerializableObject(const char* name, T *object)
	{
		this->_name = name;
		this->_object = object;
	}

	virtual std::string serialize()
	{
		this->_serialized << "<" << this->_name << ">";
		this->_serialized << this->_object->serialize();
		this->_serialized << "</" << this->_name << ">";
		return this->_serialized.str();
	}
};

/**
 * 特殊化
 * SerializableObject<const char*>
 */
template<>
class SerializableObject<const char*> : public SerializableComponent
{
private:
	const char *_name;
	const char *_object;

public:
	SerializableObject(const char* name, const char* object)
	{
		this->_name = name;
		this->_object = object;
	}
	virtual std::string serialize()
	{
		this->_serialized << "<" << this->_name << ">";
		this->_serialized << this->_object;
		this->_serialized << "</" << this->_name << ">";
		return this->_serialized.str();
	}
};

/**
 * 特殊化
 * SerializableObject<int>
 */
template<>
class SerializableObject<int> : public SerializableComponent
{
private:
	const char *_name;
	int _object;

public:
	SerializableObject(const char* name, int object)
	{
		this->_name = name;
		this->_object = object;
	}
	virtual std::string serialize()
	{
		this->_serialized << "<" << this->_name << ">";
		this->_serialized << this->_object;
		this->_serialized << "</" << this->_name << ">";
		return this->_serialized.str();
	}
};

/**
 * 特殊化
 * SerializableObject<double>
 */
template<>
class SerializableObject<double> : public SerializableComponent
{
private:
	const char *_name;
	double _object;

public:
	SerializableObject(const char* name, double object)
	{
		this->_name = name;
		this->_object = object;
	}
	virtual std::string serialize()
	{
		this->_serialized << "<" << this->_name << ">";
		this->_serialized << this->_object;
		this->_serialized << "</" << this->_name << ">";
		return this->_serialized.str();
	}
};

/**
 * SerializableComposite
 * ノードオブジェクト用
 */
class SerializableComposite : public SerializableComponent
{
private:
	std::vector<SerializableComponent *> _children;
	const char* _name;

public:
	SerializableComposite()
	{
		this->_name = NULL;
	}
	void setElementName(const char* name)
	{
		this->_name = name;
	}

	void add(SerializableComponent *element)
	{
		this->_children.push_back(element);
	}

	std::string serialize()
	{
		if (this->_name)
			this->_serialized << "<" << this->_name << ">";
		for (int i = 0; i < this->_children.size(); i++)
			this->_serialized << this->_children[i]->serialize();
		if (this->_name)
			this->_serialized << "</" << this->_name << ">";
		return this->_serialized.str();
	}

	~SerializableComposite()
	{
		for (int i = 0; i < this->_children.size(); i++)
			delete this->_children[i];
	}
};

} }
#endif /* EMWD_CORE_SERIALIZER_H_ */
