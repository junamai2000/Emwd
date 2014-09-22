// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include "models/Category.h"

using namespace Emwd::core;

std::string Category::serialize()
{
    XmlSerializableComposite data;
    data.add(new XmlSerializableObject<int>("Id", this->id));
    data.add(new XmlSerializableObject<const char*>("Name", this->name));
    data.add(new XmlSerializableObject<const char*>("Explanation", this->explanation));
    return data.serialize();
}
