// subclass.cpp
#include <glutframework/GlutFramework.h>
#include <glutframework/Primitive.h>

using namespace glutframework;

class Subclass: public GlutFramework
{
public:
	Subclass(): m_prim(NULL){};
	~Subclass(){ delete m_prim; };
	
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

int main(int argc, char *argv[])
{		
	Subclass framework;
	framework.startFramework(argc, argv);
	return 0;
};
