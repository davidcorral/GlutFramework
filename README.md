GLUT Object Oriented Framework
-------------------------------

Overview:
---------

The original authors of this project are Paul Soft and Dimitar Stanev.
I basically merged both projects and improved some areas like the camera, primitives, grid etc. 
I removed Paul's `PerformanceTimer` from the project, I might get it back.

Paul Solt:
	https://github.com/PaulSolt/GLUT-Object-Oriented-Framework.git
Dimitar Stanev:
	https://github.com/mitkof6/GlutFramework.git

The GLUT Object Oriented Framework is a set of classes that wrap around the GLUT C-style function calls to create an animation framework. It provides a simple object oriented wrapper that has virtual methods to override default behavior. Four lines of code within a main function can be used to get a graphics window that draws an animated teapot. 

	Teapot Demo:
	------------
	// main.cpp
	#include "GlutFramework.h"
	using namespace glutFramework;
	int main(int argc, char *argv[]) {
		GlutFramework framework;
		framework.startFramework(argc, argv);
	    return 0;
	}
	
	Subclass Example:
   	-----------------
	// subclass.cpp
	#include "GlutFramework.h"
	#include "Primitive.h"
	using namespace glutFramework;
	class Subclass: public GlutFramework
	{
	public:
		Subclass(): m_prim(0){};
		~Subclass(){ delete m_prim; };
		
		virtual void load()
		{
			m_prim = new Primitive( Primitive::kCube, 1 );
		};
		virtual void display()
		{	
			m_prim->draw();
		};
	private:
		Primitive* m_prim;
	};
