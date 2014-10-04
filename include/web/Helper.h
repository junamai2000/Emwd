// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Helper.h
 *
 *  Created on: 2014/10/3
 *      Author: Junya Namai
 */
#ifndef EMWD_WEB_HELPER_H_
#define EMWD_WEB_HELPER_H_

// C++ headers
#include <string>
#include <iterator>

namespace Emwd { namespace web {

class Helper {
public:
	static std::string encode(std::string& data)
    {
        std::string buffer;
        buffer.reserve(data.size());
        for(size_t pos = 0; pos != data.size(); ++pos)
        {
            switch(data[pos])
            {
                case '&':  buffer.append("&amp;");       break;
                case '\"': buffer.append("&quot;");      break;
                case '\'': buffer.append("&apos;");      break;
                case '<':  buffer.append("&lt;");        break;
                case '>':  buffer.append("&gt;");        break;
                default:   buffer.append(&data[pos], 1); break;
            }
        }
        data.swap(buffer);
        return data;
    }
};

} }

#endif /* EMWD_WEB_HELPER_H_ */
