// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * XmlSerializable.h
 *
 *  Created on: 2014/09/19
 *      Author: Junya Namai
 */

#ifndef EMWD_CORE_SERIALIZER_H_
#define EMWD_CORE_SERIALIZER_H_

#include <string>
#include <vector>
#include <sstream>

namespace Emwd { namespace core {

/**
 * XmlSerializable
 */
class XmlSerializable
{
protected:
	std::stringstream _serialized;
public:
	virtual std::string serialize() = 0;
	virtual ~XmlSerializable() {}
};

/**
 * SerializableObject
 */
template<class T>
class XmlSerializableObject : public XmlSerializable
{
private:
	const char *_name;
	T _object;

public:
	XmlSerializableObject(const char* name, T object)
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
 * 各型の部分特殊化
 * SerializableObject<const char*>
 */
template <> std::string XmlSerializableObject<const char*>::serialize()
{
	this->_serialized << "<" << this->_name << ">";
	this->_serialized << this->_object;
	this->_serialized << "</" << this->_name << ">";
	return this->_serialized.str();
};

template<> std::string XmlSerializableObject<int>::serialize()
{
	this->_serialized << "<" << this->_name << ">";
	this->_serialized << this->_object;
	this->_serialized << "</" << this->_name << ">";
	return this->_serialized.str();
};

template<> std::string XmlSerializableObject<float>::serialize()
{
	this->_serialized << "<" << this->_name << ">";
	this->_serialized << this->_object;
	this->_serialized << "</" << this->_name << ">";
	return this->_serialized.str();
};

template<> std::string XmlSerializableObject<double>::serialize()
{
	this->_serialized << "<" << this->_name << ">";
	this->_serialized << this->_object;
	this->_serialized << "</" << this->_name << ">";
	return this->_serialized.str();
};

/**
 * XmlSerializableComposite
 * ノードオブジェクト用
 */
class XmlSerializableComposite : public XmlSerializable
{
private:
	std::vector<XmlSerializable *> _children;
	const char* _name;

public:
	XmlSerializableComposite()
	{
		this->_name = NULL;
	}
	void setElementName(const char* name)
	{
		this->_name = name;
	}

	void add(XmlSerializable *element)
	{
		this->_children.push_back(element);
	}

	std::string serialize()
	{
		if (this->_name)
			this->_serialized << "<" << this->_name << ">";
		for (unsigned int i = 0; i < this->_children.size(); i++)
			this->_serialized << this->_children[i]->serialize();
		if (this->_name)
			this->_serialized << "</" << this->_name << ">";
		return this->_serialized.str();
	}

	~XmlSerializableComposite()
	{
		for (unsigned int i = 0; i < this->_children.size(); i++)
			delete this->_children[i];
	}
};

} }
#endif /* EMWD_CORE_SERIALIZER_H_ */
