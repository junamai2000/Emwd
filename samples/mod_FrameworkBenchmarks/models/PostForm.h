// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#include <core/Model.h>

/**
 * PostForm class
 */
class PostForm : public Emwd::core::Model
{
private:
	const char *_name;
	const char *_email;
	const char *_text;

public:
	virtual const char* getComponentName();
	void registerValidators();
	// static int complicatedValidator(Model *model);
	bool processSave();
};
