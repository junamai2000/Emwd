// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#ifndef FB_MODELS_FORTUNE_H_
#define FB_MODELS_FORTUNE_H_ 
// C++ Header
#include <list>

#include <db/ar/ActiveRecord.h>

class Fortune : public Emwd::db::ActiveRecord
{
public:
    int id;
    const char* message;
    typedef std::list<Fortune*> Fortunes;

    virtual const char* getComponentName();
    virtual bool processSave() { return true; }
    virtual void registerValidators() { return; }
    Fortune(Emwd::core::Connection *connection);
    virtual void setTableSchema();

    static Fortune* findByPk(int id, Emwd::core::Connection *con);
    static Fortunes* findAll(Emwd::core::Connection *con);
};

#endif
