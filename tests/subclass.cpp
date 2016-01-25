// subclass.cpp
#include "../include/GlutFramework.h"
#include "../include/Primitive.h"

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

int main(int argc, char *argv[])
{		
	Subclass framework;
	framework.startFramework(argc, argv);
	return 0;
}