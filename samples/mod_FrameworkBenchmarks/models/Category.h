// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/XmlSerializable.h>

/**
 * Serializable User Information
 */
class Category : public Emwd::core::XmlSerializable
{
public:
    int id;
	const char *name;
    const char *explanation;

	virtual std::string serialize();
	~Category() {}
};
