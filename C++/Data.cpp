#include "Data.hpp"
#include <fstream>

Data :: Data() {
    std::ifstream in("head.txt");
    std::string line;
    char symbol;
    while (in >> line) {
        
        if (line == "v") {
            double a, b, c;
            in >> a >> b >> c;
            vertices.push_back(Vector3D<double> (a, b, c));
        }
        if (line == "vt") {
            double a, b, c;
            in >> a >> b >> c;
            textureVertices.push_back(Vector3D<double> (a, b, c));
        }
        if (line == "vn") {
            double a, b, c;
            in >> a >> b >> c;
            vertexNormals.push_back(Vector3D<double>(a, b, c));
        }
        if (line == "f") {
            for (int i = 0; i < NUMBER; ++i) {
                int a, b, c;
                in >> a >> symbol >> b >> symbol >> c;
                --a;
                faces[i].push_back(Vector3D<int> (a, b, c));
            }
        }
    }
    /*std::string texfile("head.txt");
    size_t dot = texfile.find_last_of(".");
    if (dot!=std::string::npos) {
        texfile = texfile.substr(0,dot) + std::string("head.tga");
        diffusemap.flip_vertically();
    }*/
}

TGAColor Data::diffuse(Vector2D<int> uv) {
    return diffusemap.get(uv[0], uv[1]);
}