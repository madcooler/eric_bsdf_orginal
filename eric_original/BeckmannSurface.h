#pragma once

#include "Vector.h"
#include "vec2.hpp"


class BeckmannSurface
{
public:
	BeckmannSurface ( const float alpha_x , const float alpha_y ,
		const int N = 1000 ); // use at least 1000 otherwise correlation patterns appear
	~BeckmannSurface ();
	float h ( const vec2& pos ) const;
	vec2 slope ( const vec2& pos ) const;
	vec3 normal ( const vec2& pos ) const;
private:
	const int N; // number of cosine waves
	const float scale; // sqrt(2/N)
	float* phi; // phases
	float* fx; // frequencies in the x direction
	float* fy; // frequencies in the y direction
};
BeckmannSurface::BeckmannSurface ( const float alpha_x , const float alpha_y , const int N )
	: N ( N ) , scale ( sqrtf ( 2.0f / N ) )
{
	// allocate
	phi = new float[ N ];
	fx = new float[ N ];
	fy = new float[ N ];
	// initialize parameters
	for (int i = 0; i<N; ++i)
	{
		const float U1 = ( rand () ) / ( float ) RAND_MAX;
		const float U2 = ( rand () ) / ( float ) RAND_MAX;
		const float U3 = ( rand () ) / ( float ) RAND_MAX;
		phi[ i ] = 2.0f * M_PI * U1;
		const float theta = 2.0f * M_PI * U2;
		const float r = sqrtf ( -logf ( 1.0f - U3 ) );
		fx[ i ] = r*cosf ( theta ) * alpha_x;
		fy[ i ] = r*sinf ( theta ) * alpha_y;
	}
}
BeckmannSurface::~BeckmannSurface ()
{
	delete [] phi;
	delete [] fx;
	delete [] fy;
}
float BeckmannSurface::h ( const vec2& pos ) const
{
	float res = 0;
	for (int i = 0; i<N; ++i)
		res += cosf ( phi[ i ] + pos.x*fx[ i ] + pos.y*fy[ i ] );
	return scale*res;
}
vec2 BeckmannSurface::slope ( const vec2& pos ) const
{
	vec2 res ( 0 , 0 );
	for (int i = 0; i<N; ++i)
	{
		const float tmp = sinf ( phi[ i ] + pos.x*fx[ i ] + pos.y*fy[ i ] );
		res.x += -fx[ i ] * tmp;
		res.y += -fy[ i ] * tmp;
	}
	return  res * scale ;
}
vec3 BeckmannSurface::normal ( const vec2& pos ) const
{
	const vec2 s = slope ( pos );
	return normalize ( vec3 ( -s.x , -s.y , 1.0f ) );
}

void mean()
{
	
}