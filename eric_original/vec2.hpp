//
//  vec2.hpp
//  eric_original
//
//  Created by Administrator on 07/11/2016.
//  Copyright © 2016 Chi Wang. All rights reserved.
//

#ifndef vec2_hpp
#define vec2_hpp

#include <stdio.h>
#include "Vector.h"

class vec2 {
public:
	// vec2 Public Methods
	vec2() { x = y = 0.f; }
	vec2(double xx, double yy)
		: x(xx), y(yy)
	{		
	}
	void Print()
	{
		printf("\n x %f y %f \n", x,y);
	}

	// The default versions of these are fine for release builds; for debug
	// we define them so that we can add the Assert checks.
	vec2(const vec2 &v) {
		
		x = v.x; y = v.y;
	}

	vec2 &operator=(const vec2 &v) {
		
		x = v.x; y = v.y;
		return *this;
	}

	vec2 operator+(const vec2 &v) const {
		
		return vec2(x + v.x, y + v.y);
	}

	vec2& operator+=(const vec2 &v) {
		
		x += v.x; y += v.y;
		return *this;
	}
	vec2 operator-(const vec2 &v) const {
		
		return vec2(x - v.x, y - v.y);
	}

	vec2& operator-=(const vec2 &v) {
		
		x -= v.x; y -= v.y;
		return *this;
	}
	vec2 operator*(double f) const { return vec2(f*x, f*y); }

	vec2 &operator*=(double f) {
		
		x *= f; y *= f;
		return *this;
	}
	vec2 operator/(double f) const {
		if( f==0 )
		{
			return vec2(0,0);
		}

		double inv = 1.f / f;
		return vec2(x * inv, y * inv);
	}
//	bool HasNaNs() const {
//		return isnan(x) || isnan(y) || isnan(z);
//	}
	vec2 &operator/=(double f) {
		
		double inv = 1.f / f;
		x *= inv; y *= inv;
		return *this;
	}
	vec2 operator-() const { return vec2(-x, -y); }
	double operator[](int i) const {
		
		return (&x)[i];
	}

	double &operator[](int i) {
		
		return (&x)[i];
	}
	double LengthSquared() const { return x*x + y*y ; }
	double Length() const { return sqrt(LengthSquared()); }
	

	bool operator==(const vec2 &v) const {
		return x == v.x && y == v.y ;
	}
	bool operator!=(const vec2 &v) const {
		return x != v.x || y != v.y ;
	}
	bool isEmpty ()
	{
		return Length () == 0;
	}
	// vec2 Public Data
	double x, y;
};


#endif /* vec2_hpp */
