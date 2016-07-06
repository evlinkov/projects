#ifndef Data_D
#define Data_D

#include <iostream>
#include <vector>
#include "Geometry.h"
#include "TGA.hpp"

const int NUMBER = 3; /* number vertices in triangle */

class Data {
    
public :
    
    Data();
    TGAColor diffuse(Vector2D<int> uv);
    ~Data() {
        vertices.clear();
        textureVertices.clear();
        vertexNormals.clear();
        for (int i = 0; i < NUMBER; ++i) {
            faces[i].clear();
        }
    }
    
protected:
    
    std::vector <Vector3D<double> > vertices;
    std::vector <Vector3D<double> > textureVertices;
    std::vector <Vector3D<double> > vertexNormals;
    std::vector <Vector3D<int> > faces[NUMBER];
    TGAImage diffusemap;
};

#endif
