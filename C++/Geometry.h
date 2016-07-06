#ifndef Geometry_h
#define Geometry_h

#include <cmath>

template <typename type>
class Vector2D {
    
public :

    Vector2D<type>() : x(0), y(0) {}
    Vector2D<type>(type _x, type _y) : x(_x), y(_y) {}
    type& operator[](const int number) {
        if (number == 0) return x;
        return y;
    }
    template <class t> Vector2D<type>(const Vector2D<t> &vec);
    Vector2D<type> & operator = (const Vector2D<type> &vec) {
        if (this != &vec) {
            x = vec.x;
            y = vec.y;
        }
        return *this;
    }
    Vector2D<type> operator +(const Vector2D<type> &vec) const {
        return Vector2D<type>(x + vec.x, y + vec.y);
    }
    Vector2D<type> operator -(const Vector2D<type> &vec) const {
        return Vector2D<type>(x - vec.x, y - vec.y);
    }
    Vector2D<type> operator * (type mult) {
        return Vector2D<type> (x * mult, y * mult);
    }
    type getElement(int i) const{
        if (i == 0) return x;
        return y;
    }
    
private:
    
    type x, y;
};

template <> template <> Vector2D<int>::Vector2D(const Vector2D<double> &vec);
template <> template <> Vector2D<double>::Vector2D(const Vector2D<int> &vec);

template <typename type>
class Vector3D {
    
public :
    
    Vector3D<type>() : x(0), y(0), z(0) {}
    Vector3D<type>(type _x, type _y, type _z) : x(_x), y(_y), z(_z) {}
    Vector3D<type> & operator = (const Vector3D<type> &vec) {
        if (this != &vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }
        return *this;
    }
    type& operator[](const int number) {
        if (number == 0) return x;
        if (number == 1) return y;
        return z;
    }
    template <class t> Vector3D<type>(const Vector3D<t> &vec);
    Vector3D<type> operator +(const Vector3D<type> &vec) const {
        return Vector3D<type>(x + vec.x, y + vec.y, z + vec.z);
    }
    Vector3D<type> operator -(const Vector3D<type> &vec) const {
        return Vector3D<type>(x - vec.x, y - vec.y, z - vec.z);
    }
    Vector3D<type> operator * (type mult) {
        return Vector3D<type> (x * mult, y * mult, z * mult);
    }
    type operator * (const Vector3D<type> &vec) const {
        return (x * vec.x + y * vec.y + z * vec.z);
    }
    Vector3D<type> operator ^(const Vector3D<type> &vec) const {
        return Vector3D<type>(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }
    Vector3D<type> & normalize() {
        *this = (*this) * (1. / sqrt(x * x + y * y + z * z));
        return *this;
    }
    type getElement(int i) const{
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

private :
    
    type x, y, z;

};

template <> template <> Vector3D<int>::Vector3D(const Vector3D<double> &vec);
template <> template <> Vector3D<double>::Vector3D(const Vector3D<int> &vec);

#endif