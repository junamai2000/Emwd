// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <time.h>
#include <fstream>

#include <core/Configuration.h>
#include <picojson/picojson.h>

/**
 * JsonConfiguration
 */
class JsonConfiguration
{
private:
	/**
	 * parsed json
	 */
	picojson::value _json;

public:
	/**
	 * Open Json
	 * @param path
	 * @return
	 */
	bool open(const char* path);

	/**
	 * Get application name
	 * @return string from json
	 */
	const char* getApplicationName();
};
