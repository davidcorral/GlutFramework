#include <Primitive.h>

Primitive::Primitive( const Type& type, float size )
: Renderable(), m_type(type), size(size){};

Primitive::~Primitive(){};

void
Primitive::draw() const
{
	glPopMatrix();
	
	glColor3f(red, green, blue);

	{
		// Sphere
		//if ( m_type == Primitive::kSphere && style == Renderable::kWireframe )
		//	glutWireSphere(size);
		//else if ( m_type == Primitive::kSphere && style == Renderable::kShaded )
		//	glutSolidSphere(size);
		// Cube
		if ( m_type == Primitive::kCube && style == Renderable::kWireframe )
			glutWireCube(size);
		else if ( m_type == Primitive::kCube && style == Renderable::kShaded )
			glutSolidCube(size);
		// Torus
		//else if ( m_type == Primitive::kTorus && style == Renderable::kWireframe )
		//	glutWireTorus(size);
		//else if ( m_type == Primitive::kTorus && style == Renderable::kShaded )
		//	glutSolidTorus(size);
		// Teapot
		else if ( m_type == Primitive::kTeapot && style == Renderable::kWireframe )
			glutWireTeapot(size);
		else if ( m_type == Primitive::kTeapot && style == Renderable::kShaded )
			glutSolidTeapot(size);
	}
	
	glPopMatrix();
};
