// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include "config/JsonConfiguration.h"

bool JsonConfiguration::open(const char* path)
{
    std::ifstream file(path);
    if (file.fail())
    {
        std::cerr << "Failed to open file : " << path << std::endl;
        return false;
    }

    std::istreambuf_iterator<char> first(file);
    std::istreambuf_iterator<char> last;
    std::string json_in(first, last);

    std::string error;
    picojson::parse(this->_json, json_in.begin(), json_in.end(), &error);
    if (!error.empty())
    {
        std::cerr << "Json parse error" << std::endl;
        return false;
    }
    return true;
}

const char* JsonConfiguration::getApplicationName()
{
    return this->_json.get<picojson::object>()["web"].get<picojson::object>()["name"].get<std::string>().c_str();
}
