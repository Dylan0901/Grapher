#ifndef TYPES3D_H
#define TYPES3D_H
#include <vector>

typedef struct vertex {
    float x, y, z;
    //float u, v;
    vertex(){}
    vertex(const vertex& ver){
        x = ver.x;
        y = ver.y;
        z = ver.z;
    }
    vertex(float nx, float ny, float nz){
        x = nx;
        y = ny;
        z = nz;
    }
} Vertex;

/*
class Type3d {
protected:
    const char* type;
    virtual void addVertex(float x, float y, float z, float u, float v) = 0;
    //virtual void pointCount() = 0;
    virtual void setType(const char*) = 0;
};

class Triangle: public Type3d {
public:
    Triangle() {
        index = 0;
    }
    virtual void setType(const char* type) {
        this->type = type;
    }
    virtual void addVertex(float x, float y, float z, float u, float v){
        vertexes[index] = Vertex(x, y, z, u, v);
        ++ index;
    }
    //virtual void pointCount() {
    //}
    Vertex vertexes[3];
private:
    short index;
};
*/

typedef struct face {
    bool quad;
    Vertex txt[4];
    Vertex vertex[4];
    face(){}
    face(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& t1, Vertex& t2, Vertex& t3) {
        quad = false;
        vertex[0] = v1;
        vertex[1] = v2;
        vertex[2] = v3;
        txt[0] = t1;
        txt[1] = t2;
        txt[2] = t3;
    }
    face(Vertex& v1, Vertex& v2, Vertex& v3, Vertex& v4, Vertex& t1, Vertex& t2, Vertex& t3, Vertex& t4) {
        quad = true;
        vertex[0] = v1;
        vertex[1] = v2;
        vertex[2] = v3;
        vertex[3] = v4;
        txt[0] = t1;
        txt[1] = t2;
        txt[2] = t3;
        txt[3] = t4;
    }
} Face;

typedef struct sector {
    std::vector<Face> faces;
} Sector;

typedef struct bundle {
    Vertex position;
    Vertex angle;
    Sector sector;
    bundle(){}
    bundle(const bundle& bun) {
        position = bun.position;
        angle = bun.angle;
        sector = bun.sector;
    }
} Bundle;

#endif // TYPES3D_H
