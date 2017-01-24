# GLUT Object Oriented Framework #

## Overview: ##

The original authors of this project are Paul Soft and Dimitar Stanev.
I basically merged both projects and improved some areas like the camera, primitives, grid etc. 
I removed Paul's `PerformanceTimer` from the project, I might get it back.

Paul Solt:
https://github.com/PaulSolt/GLUT-Object-Oriented-Framework.git

Dimitar Stanev:
https://github.com/mitkof6/GlutFramework.git

The GLUT Object Oriented Framework is a set of classes that wrap around the GLUT C-style function calls to create an animation framework. It provides a simple object oriented wrapper that has virtual methods to override default behavior. Four lines of code within a main function can be used to get a graphics window that draws an animated teapot. 

### Hotkeys: ###

	Espace: Tumble, track, dolly, roll, or zoom the camera
	1: Draw points
	2: Draw wireframe
	3: Draw shaded
	4: Draw wireframe and shaded
	g: Show/Hide grid
	Esc: Exit

## Examples: ##

### teapot.cpp ###
~~~{.cpp}
#include "GlutFramework.h"

using namespace glutframework;

int main(int argc, char *argv[]) 
{
	GlutFramework framework;
	framework.startFramework(argc, argv);
	return 0;
};
~~~

### subclass.cpp ###
~~~{.cpp}
#include "GlutFramework.h"
#include "Primitive.h"

using namespace glutframework;

class Subclass: public GlutFramework
{
public:
	Subclass(): m_prim(NULL){};
	~Subclass()
	{
		if (m_prim) 
			delete m_prim; 
	};
	
	virtual void load()
	{
		if (m_prim)
			delete m_prim;
		m_prim = new Primitive( Primitive::kCube, 1 );
	};
	virtual void display()
	{
		if (m_prim)	
			m_prim->draw();
	};
private:
	Primitive* m_prim;
};
~~~