// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
/*
 * Kozaiku.h
 *
 *  Created on: 2014/09/08
 *      Author: junya
 */
#ifndef EMWD_KOZAIKU_H_
#define EMWD_KOZAIKU_H_

#include <dlfcn.h>

#include <string>

namespace Emwd { namespace kozaiku {

/**
 * Kozaiku class
 */
class Kozaiku
{
protected:

private:
	/**
	 * Shared Object Name to be opened
	 */
	const char* _soName;

	/**
	 * dl handle
	 */
	void* _handle;

	/**
	 * Need to construct with an argument
	 */
	Kozaiku();
public:
	/**
	 *
	 * @param soName
	 */
	Kozaiku(const char* soName)
	{
		this->_soName = soName;
		this->_handle = dlopen(this->_soName, RTLD_LAZY);
		/*
		if (this->_handle == 0)
		{
			fprintf(stderr, "%s\n", dlerror());
		}
		*/
	}

	/**
	 * closed so handle
	 */
	~Kozaiku()
	{
		dlclose(this->_handle);
		/*
		if (dlclose(this->_handle) != 0)
		{
			fprintf(stderr, "%s\n", dlerror());
			return 1;
		}
		*/
	}

	/**
	 * display function
	 * @param file
	 * @param stash
	 * @return
	 */
	bool display(const char* file, void* stash)
	{
		  std::string templateSymbol;
		  templateSymbol = "kozaiku_display_";
		  templateSymbol += file;
		  const char* (*displayFunction)(void*) ;
		  displayFunction = (const char* (*)(void*))dlsym(this->_handle, templateSymbol.c_str());
		  if (displayFunction == 0) {
		    //fprintf(stderr, "%s\n", dlerror());
		    return false;
		  }
		  return displayFunction(stash);
	}
};

} }

#endif /* EMWD_KOZAIKU_H_ */
