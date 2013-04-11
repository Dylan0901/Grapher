#include "objloader.h"
//#include <GL/gl.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

ObjLoader::ObjLoader()
{
}

Sector ObjLoader::load(const char* filename)
{
    std::vector<std::string> coord;
    std::vector<Vertex> vertexes;
    std::vector<Face>* faces = new std::vector<Face>;
    std::vector<Vertex> normals;
    std::ifstream in(filename);
    if(!in.is_open())
    {
        throw "Can not open";
    }
    char buf[256];
    while(!in.eof())
    {
        in.getline(buf, 256);
        coord.push_back(std::string(buf));
    }
    std::vector<std::string>::iterator index;
    for (index = coord.begin(); index != coord.end(); ++index) {
        const std::string& line = *index;
        if(line[0]=='#')
            continue;
        else if(line[0]=='v' && line[1]==' ')
        {
            float tmpx, tmpy, tmpz;
            sscanf(line.c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
            vertexes.push_back(Vertex(tmpx, tmpy, tmpz));
        }else if(line[0]=='v' && line[1]=='t')
        {
            float tmpx, tmpy, tmpz;
            sscanf(line.c_str(), "vt %f %f %f",&tmpx,&tmpy,&tmpz);
            normals.push_back(Vertex(tmpx, tmpy, tmpz));
        }else if(line[0]=='f')
        {
            int a, b, c, d, e, f, g, h;
            if(std::count(line.begin(), line.end(), ' ')==4)
            {
                sscanf(line.c_str(),"f %d/%d %d/%d %d/%d",&a,&b,&c,&d,&e,&f);
                Face fa(vertexes[a-1], vertexes[c-1], vertexes[e-1], normals[b-1], normals[d-1], normals[f-1]);
                faces->push_back(fa);
            }else{
                sscanf(line.c_str(),"f %d/%d %d/%d %d/%d %d/%d",&a,&b,&c,&d,&e,&f,&g,&h);
                Face fa(vertexes[a-1], vertexes[c-1], vertexes[e-1], vertexes[g-1], normals[b-1], normals[d-1], normals[f-1], normals[h-1]);
                faces->push_back(fa);
            }
        }
    }
    /*int num;
    num=glGenLists(1);
    glNewList(num,GL_COMPILE);
    for(unsigned int i=0;i<faces.size();i++)
    {
        if(faces[i]->four)
        {
            glBegin(GL_QUADS);
                //basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
                //I subtract 1 because the index start from 0 in C++
                glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                //draw the faces
                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
                glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
            glEnd();
        }else{
            glBegin(GL_TRIANGLES);
                glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
            glEnd();
        }
    }
    glEndList();*/

    Sector sector;
    sector.faces = *faces;
    delete faces;
    return sector;
    //return num; //return with the id
}
