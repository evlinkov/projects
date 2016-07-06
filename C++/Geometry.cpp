#include "Geometry.h"

template <> template <> Vector2D<int>::Vector2D(const Vector2D<double> &vec) :
    x(int(vec.getElement(0)+.5)), y(int(vec.getElement(1)+.5)) {}

template <> template <> Vector2D<double>::Vector2D(const Vector2D<int> &vec) :
    x(vec.getElement(0)), y(vec.getElement(1)){}



template <> template <> Vector3D<int>::Vector3D(const Vector3D<double> &vec) :
    x(int(vec.getElement(0)+.5)), y(int(vec.getElement(1)+.5)), z(int(vec.getElement(2)+.5)) {}

template <> template <> Vector3D<double>::Vector3D(const Vector3D<int> &vec) :
    x(vec.getElement(0)), y(vec.getElement(1)), z(vec.getElement(2)) {}

