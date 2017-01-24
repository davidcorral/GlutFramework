/*
 * Camera.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: Jim Stanev
 */

#include <glutframework/Camera.h>

namespace glutframework
{

Camera::Camera()
{
    m_camPos[0] = 0.0f;
    m_camPos[1] = 0.0f;
    m_camPos[2] = 5.0f;
    m_camAim[0] = 0.0f;
    m_camAim[1] = 0.0f;
    m_camAim[2] = 0.0f;

    m_camRotX = PI/2.0f;
    m_camRotY = PI/2.0f;
};

Camera::~Camera() 
{
	//
}

// ---------------------------------------------------------------------------

void 
Camera::direction( float vect[3], bool normalized ) const
{
    vect[0] = m_camPos[0] - m_camAim[0];
    vect[1] = m_camPos[1] - m_camAim[1];
    vect[2] = m_camPos[2] - m_camAim[2];

    if ( normalized )
    {
        float d = sqrt( vect[0]*vect[0] + vect[1]*vect[1] + vect[2]*vect[2] );

        vect[0] /= d;
        vect[1] /= d;
        vect[2] /= d;
    };
};

float 
Camera::distance() const
{
    float vect[3];
    direction( vect, false );

    return sqrt( vect[0]*vect[0] + vect[1]*vect[1] + vect[2]*vect[2] );
};

// -----------------------------------------------------------------------

void 
Camera::rotate( float deltaX, float deltaY )
{
    m_camRotX += deltaY * -0.01f; // rotation in ZY plane // X
    m_camRotY += deltaX *  0.01f; // rotation in XZ plane // Y

    float d = distance();

    m_camPos[0] = d * sin( m_camRotX ) * cos( m_camRotY ) + m_camAim[0];
    m_camPos[1] = d * cos( m_camRotX ) + m_camAim[1];
    m_camPos[2] = d * sin( m_camRotX ) * sin( m_camRotY ) + m_camAim[2];	
};

void
Camera::pan( float deltaX, float deltaY )
{
    float angleX = m_camRotX-PI/2.0; // remove initial rotation
    float angleY = m_camRotY-PI/2.0; // remove initial rotation.
    float angleZ = 0.0f;

    float x, y, z, xx, yy, zz;

        float d = distance();

    // Position in plane
    x = deltaX * -0.0015f * d;
    y = deltaY *  0.0015f * d;
    z = 0.0f;

    // Rotate in YZ Plane // X
    xx =  x;
    yy = (y*cos( angleX )) - (z*sin( angleX ));
    zz = (y*sin( angleX )) + (z*cos( angleX ));
    x = xx;
    y = yy;
    z = zz;

    // Rotate in XZ Plane // Y
    xx = (x*cos( angleY )) - (z*sin( angleY ));
    yy = y;
    zz = (x*sin( angleY )) + (z*cos( angleY ));
    x = xx;
    y = yy;
    z = zz;

    m_camAim[0] += x;
    m_camAim[1] += y;
    m_camAim[2] += z;

    m_camPos[0] += x ;
    m_camPos[1] += y ;
    m_camPos[2] += z ;
};

void 
Camera::zoom( float new_distance )
{
    float vect[3];
    direction( vect, true );

    vect[0] *= new_distance;
    vect[1] *= new_distance;
    vect[2] *= new_distance;

    vect[0] += m_camAim[0];
    vect[1] += m_camAim[1];
    vect[2] += m_camAim[2];
    
    m_camPos[0] = vect[0];
    m_camPos[1] = vect[1];
    m_camPos[2] = vect[2];
};

// ---------------------------------------------------------------------------

void 
Camera::draw() const
{
    gluLookAt( m_camPos[0], m_camPos[1], m_camPos[2], // camera position
                   m_camAim[0], m_camAim[1], m_camAim[2], // camera aim
                   0.0f, 1.0f, 0.0f);                     // camera up vector
};

};