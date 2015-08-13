#ifndef VEC3_H
#define VEC3_H

template<typename T>
class Vec3
{
public:
    // Constructors
    Vec3();
    Vec3(const T& x, const T& y, const T& z);
    Vec3(const T& xyz);	// x = y = z = xyz
    Vec3(const T xyz[]);
    Vec3(const Vec3<T>& o);

    // Math operators (=, +, -, *, /, etc...) with self assignment
    Vec3<T>& operator=(const Vec3<T>& o);
    Vec3<T>& operator+=(const Vec3<T> &o);
    Vec3<T>& operator-=(const Vec3<T> &o);
    Vec3<T>& operator*=(const T& scalar);
    Vec3<T>& operator/=(const T& scalar);

    // Math operators without self-assignment (Create a temporary variable)
    Vec3<T> operator+(const Vec3<T>& o) const;
    Vec3<T> operator-(const Vec3<T>& o) const;

    Vec3<T> operator*(const T& scalar) const;
    Vec3<T> operator/(const T& scalar) const;

    // Boolean operators
    bool operator==(const Vec3<T>& o) const;

    // Vector operations
    T length2() const;
    T length() const;

    Vec3<T>& Normalize();	// Returns a reference to "this"
    Vec3<T> getNormalizedVec() const;

    T dot(const Vec3<T>& o) const;
    Vec3<T> cross(const T& o) const;
    Vec3<T>& applyCross(const T& o);	// a = cross(a,b). Returns a reference to "this"

    // Member variables
    T	x;
    T	y;
    T	z;
};

// Non-member operators
template<typename T> Vec3<T> operator*(const T& scalar, const Vec3<T>& v);
template<typename T> Vec3<T> operator/(const T& scalar, const Vec3<T>& v);

typedef Vec3<double>			Vec3d;
typedef Vec3<float>				Vec3f;
typedef Vec3<int>				Vec3i;
typedef Vec3<unsigned int>		Vec3ui;
typedef Vec3<long>				Vec3l;
typedef Vec3<unsigned long>		Vec3ul;
typedef Vec3<short>				Vec3s;
typedef Vec3<unsigned short>	Vec3us;

// Implementation details are in Vec3.hpp
#include "Vec3.hpp"

#endif // VEC3_Hs
