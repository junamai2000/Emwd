// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/XmlSerializable.h>

/**
 * Serializable User Information
 */
class UserInfo : public Emwd::core::XmlSerializable
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
