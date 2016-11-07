#pragma once

#include <stdio.h>
#include <math.h>
#include <float.h>

//using namespace std;

#define inf 1e9
#define eps 1e-6

class Vector
{
public:
	// Vector Public Methods
	Vector() { x = y = z = 0.f; }
	Vector(double xx, double yy, double zz)
		: x(xx), y(yy), z(zz) 
	{		
	}
	void Print()
	{
		printf("\n x %f y %f z %f \n", x,y,z);
	}

	// The default versions of these are fine for release builds; for debug
	// we define them so that we can add the Assert checks.
	Vector(const Vector &v) {
		
		x = v.x; y = v.y; z = v.z;
	}

	Vector &operator=(const Vector &v) {
		
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	Vector operator+(const Vector &v) const {
		
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector& operator+=(const Vector &v) {
		
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	Vector operator-(const Vector &v) const {
		
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector& operator-=(const Vector &v) {
		
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	Vector operator*(double f) const { return Vector(f*x, f*y, f*z); }

	Vector &operator*=(double f) {
		
		x *= f; y *= f; z *= f;
		return *this;
	}
	Vector operator/(double f) const {
		if( f==0 )
		{
			return Vector(0,0,0);
		}

		double inv = 1.f / f;
		return Vector(x * inv, y * inv, z * inv);
	}
//	bool HasNaNs() const {
//		return isnan(x) || isnan(y) || isnan(z);
//	}
	Vector &operator/=(double f) {
		
		double inv = 1.f / f;
		x *= inv; y *= inv; z *= inv;
		return *this;
	}
	Vector operator-() const { return Vector(-x, -y, -z); }
	double operator[](int i) const {
		
		return (&x)[i];
	}

	double &operator[](int i) {
		
		return (&x)[i];
	}
	double LengthSquared() const { return x*x + y*y + z*z; }
	double Length() const { return sqrt(LengthSquared()); }
	

	bool operator==(const Vector &v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	bool operator!=(const Vector &v) const {
		return x != v.x || y != v.y || z != v.z;
	}
	bool isEmpty ()
	{
		return Length () == 0;
	}
	// Vector Public Data
	double x, y, z;
};



#define vec3        Vector
#define Pnt3D		Vector
#define RGBColors	Vector

// Geometry Inline Functions


inline Vector operator * (double f, const Vector &v)
{
	return v*f; 
}

inline double dot(const Vector &v1, const Vector &v2) {
	
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector VectorMulti(const Vector &v1, const Vector &v2) {

	return Vector (v1.x * v2.x , v1.y * v2.y , v1.z * v2.z);
}


inline Vector MovePoint(const Vector &originPoint, const Vector &direction, double t)
{
	return Vector(
		originPoint.x + t * direction.x,
		originPoint.y + t * direction.y,
		originPoint.z + t * direction.z
	);
}

inline double AbsDot(const Vector &v1, const Vector &v2) {
	
	return fabs(dot(v1, v2));
}


inline Vector Cross(const Vector &v1, const Vector &v2) {
	
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	double v2x = v2.x, v2y = v2.y, v2z = v2.z;
	return Vector((v1y * v2z) - (v1z * v2y),
		(v1z * v2x) - (v1x * v2z),
		(v1x * v2y) - (v1y * v2x));
}


inline Vector normalize(const Vector &v)
{ 
	return v / v.Length(); 
}



inline void CoordinateSystem(const Vector &v1, Vector *v2, Vector *v3) {
	if (fabsf(v1.x) > fabsf(v1.y)) {
		double invLen = 1.f / sqrt(v1.x*v1.x + v1.z*v1.z);
		*v2 = Vector(-v1.z * invLen, 0.f, v1.x * invLen);
	}
	else {
		double invLen = 1.0 / sqrt(v1.y*v1.y + v1.z*v1.z);
		*v2 = Vector(0.f, v1.z * invLen, -v1.y * invLen);
	}
	*v3 = Cross(v1, *v2);
}

inline Vector SphericalDirection(double sintheta,
	double costheta, double phi) {
		return Vector(sintheta * cosf(phi),
			sintheta * sinf(phi),
			costheta);
}


inline Vector SphericalDirection(double sintheta, double costheta,
	double phi, const Vector &x,
	const Vector &y, const Vector &z) {
		return sintheta * cos(phi) * x +
			sintheta * sin(phi) * y + costheta * z;
}

inline double SphericalTheta(const Vector &v) {
	Vector x=normalize(v);
	
	return acos(fabs(x.z));
}


inline double SphericalPhi(const Vector &v) {
	double p = atan2f(v.y, v.x);
	return (p < 0.f) ? p + 2.f*M_PI : p;
}

template <class T>
inline T Sqr(const T& x) {return x*x;}

inline double Clamp(double val, double low, double high) {
	if (val < low) 
		return low;
	else 
		if (val > high) return high;
		else return val;
}

inline double length(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline double CosBetweenVector(const Vector &v1, const Vector &v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)/(length(v1)*length(v2));
}

