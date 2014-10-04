#ifndef FB_VIEWS_H_
#define FB_VIEWS_H_

typedef struct _FortuneTmplArgs
{
    std::string output;
    Fortune::Fortunes *fortunes;
} FortuneTmplArgs;

#endif
