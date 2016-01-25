#include "Grid.h"

Grid::Grid( float size ) 
: Renderable(), size(size){};

Grid::~Grid(){};

void
Grid::draw() const
{
	glPushMatrix();

	glColor3f(red, green, blue);

    int rows = 10;
    
    glBegin( GL_LINES );
    glColor3f( 0.5f, 0.5f, 0.5f); 
    
    // Draw z
    float x, z;
    float step = rows*2.0f/rows;
    for ( unsigned int i=0; i<rows+1; i++ )
    {
        z = -rows + (step*i);

        glVertex3f( -rows, 0, z );
        glVertex3f(  rows, 0, z );
    };
    
    // Draw x
    step = rows*2.0f/rows;
    for ( unsigned int i=0; i<rows+1; i++ )
    {
        x = -rows + (step*i);

        glVertex3f( x, 0, -rows );
        glVertex3f( x, 0,  rows );
    };

    glEnd();

	glPopMatrix();
};
