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

using namespace Emwd::core;
using namespace Emwd::web;
using namespace Emwd::validator;
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
