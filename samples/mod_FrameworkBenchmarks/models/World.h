// vim:set noexpandtab sts=0 ts=4 sw=4 ft=cpp fenc=utf-8 ff=unix:
#ifndef FB_MODELS_WORLD_H_
#define FB_MODELS_WORLD_H_

#include <db/ar/ActiveRecord.h>

class World : public Emwd::db::ActiveRecord
{
public:
    int id;
    int randomNumber;

    virtual const char* getComponentName();
    virtual bool processSave() { return true; }
    virtual void registerValidators() { return; }
    World(Emwd::core::Connection *connection);
    virtual void setTableSchema();
    static World* findByPk(int id, Emwd::core::Connection *con);
};

#endif
