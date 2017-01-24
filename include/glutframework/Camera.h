#pragma once

#include <math.h> // std::sqrt
#include "Renderable.h"

#define PI 3.14159265359

namespace glutframework
{

class Camera: public Renderable
{
public:
	Camera();
	virtual ~Camera();
	
	virtual void draw() const;

	// -----------------------------------------------------------------------

	void  direction( float vect[3], bool normalized=false ) const;
	float distance() const;
	
	// -----------------------------------------------------------------------

	void rotate( float deltaX, float deltaY );
	void pan( float deltaX, float deltaY );
	void zoom( float new_distance );

private:
	float m_camRotX; // rotation on screen
    float m_camRotY; // rotation on screen

    float m_camPos[3];
    float m_camAim[3];

}; // end class Camera

}; // end namespace