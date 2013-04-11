#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "types3d.h"

class ObjLoader
{
public:
    ObjLoader();
    Sector load(const char* filename);
};

#endif // OBJLOADER_H
