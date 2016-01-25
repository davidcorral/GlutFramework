#pragma once

// **Note:** Include GLUT after the standard c++ libraries to prevent linker errors
#ifdef WIN32
	#include <windows.h> 
	#include <GL/glut.h> 
#else
	#include <GLUT/glut.h>
#endif
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glext.h>
#endif

class Renderable
{
public:
	enum DrawStyle
	{
		kWireframe,
		kShaded
	};

	Renderable(): red(1.0f), green(1.0f), blue(1.0f), style( kShaded ){};
	virtual ~Renderable(){};
	
	virtual void draw() const = 0;

protected:
	float red;
	float green;
	float blue;
	DrawStyle style;
};

