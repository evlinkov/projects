#include "TGA.hpp"
#include "Data.hpp"
#include "Geometry.h"

class Solution : public Data {
    
public:
    
    Solution(int _width, int _height, int _depth) : width(_width), height(_height), depth(_depth), Data() {
        buffer = new int [width * height];
        for (int i=0; i<width*height; i++) {
            buffer[i] = std::numeric_limits<int>::min();
        }
        light = Vector3D<double>(0, 0, -1);
        rendering();
    }
    
    void triangle(Vector3D<int> A, Vector3D<int> B, Vector3D<int> C,
                  TGAImage &image, TGAColor colour, int *buffer) {
        if (A[1] == B[1] && A[1] == C[1]) return;
        if (A[1]>B[1]) {
            std::swap(A, B);
        }
        if (A[1]>C[1]) {
            std::swap(A, C);
        }
        if (B[1]>C[1]) {
            std::swap(B, C);
        }
        int level = C[1] - A[1];
        for (int i = 0; i < level; ++i) {
            bool half = i > B[1] - A[1] || B[1] == A[1]; // part of triangle
            int segment = half ? C[1] - B[1] : B[1] - A[1];
            double alpha = (double)i/level;
            double beta  = (double)(i-(half ? B[1]-A[1] : 0))/segment;
            Vector3D<int> a = A + (Vector3D<double>(C - A) * alpha);
            Vector3D<int> b = half ? B  + Vector3D<double>(C - B) * beta : A  + Vector3D<double>(B - A)*beta;
            if (a[0] > b[0]) {
                std::swap(a, b);
            }
            for (int j=a[0]; j <= b[0]; j++) {
                double phi = (b[0] == a[0]) ? 1. : (double)(j - a[0])/(double)(b[0] - a[0]);
                Vector3D<int> p = Vector3D<double>(a) + Vector3D<double>(b - a) * phi;
                int id = p[0] + p[1] * width;
                if (buffer[id] < p[2]) {
                    buffer[id] = p[2];
                    image.set(p[0], p[1], colour);
                }
            }
        }
    }

    
    void rendering() {
        TGAImage image(width, height, TGAImage::RGB);
        for (int i = 0; i < faces[0].size(); ++i) {
            Vector3D <int> gridCoordinates[NUMBER];
            for (int j = 0; j < 3; ++j) {
                Vector3D<double> point = vertices[faces[j][i][0]];
                gridCoordinates[j] = Vector3D<int> (int((point[0] + 1.) * width * 0.5 + 0.5),int((point[1] + 1.) * height * 0.5 + 0.5),
                                                        int((point[2] + 1.) * depth * 0.5) + 0.5);
                
            }
            Vector3D<double> normal = (vertices[faces[2][i][0]] - vertices[faces[0][i][0]]) ^
                                        (vertices[faces[1][i][0]] - vertices[faces[0][i][0]]);
            normal.normalize();
            double intensity = normal * light;
            if (intensity > 0) { /* we can see it */
                /*Vector2D<int> uv[NUMBER];
                for (int j = 0; j < NUMBER; ++j) {
                    int id = faces[j][i][1];
                    uv[j] = Vector2D<int> (textureVertices[id][0] * diffusemap.get_width(),
                                           textureVertices[id][1] * diffusemap.get_height());
                }*/
                triangle(gridCoordinates[0], gridCoordinates[1], gridCoordinates[2], image, TGAColor(intensity*255,
                                                            intensity*255, intensity*255, 255), buffer);

            }
        }
        image.flip_vertically();
        image.write_tga_file("picture.tga");
    }
    ~Solution () {
        delete buffer;
    }
    
private:
    
    int width, height, depth;
    int * buffer = nullptr;
    Vector3D<double> light;
};

int main() {
    Solution solution(800, 800, 255);
    return 0;
}