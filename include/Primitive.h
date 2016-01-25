#pragma once
#include "Renderable.h"


class Primitive : public Renderable
{

public:
	enum Type{ /*kSphere,*/ 
		       kCube, 
		       /*kTorus,*/
		       kTeapot };

	Primitive( const Type& type, float size );
	virtual ~Primitive();

	virtual void draw() const;
	
private:
	Type m_type;
	float size;
};

