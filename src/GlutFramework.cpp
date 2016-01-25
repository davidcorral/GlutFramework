/*
 * The MIT License
 *
 * Copyright (c) 2010 Paul Solt, PaulSolt@gmail.com 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <GlutFramework.h>

namespace glutFramework 
{

// Set constants
const double GlutFramework::FRAME_TIME = 1.0 / GlutFramework::FPS * 1000.0; // Milliseconds
GlutFramework* GlutFramework::instance = NULL;

GlutFramework::GlutFramework() 
{
	m_show_grid = true;
	m_frame_rate = 0;
	m_title = "GLUT Framework: Paul Solt 2010";
	
	m_modKey = false;
	l_mouse_down = false;
	m_mouse_down = false;
	r_mouse_down = false;
}

GlutFramework::~GlutFramework(){};

void GlutFramework::startFramework(int argc, char *argv[]) 
{
	instance = this; // Sets the instance to self, used in the callback wrapper functions
	
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow( m_title.c_str() ); 
	
	// Function callbacks with wrapper functions
	glutReshapeFunc(reshapeWrapper);
	glutMouseFunc(mouseButtonPressWrapper);
	glutMotionFunc(mouseMoveWrapper);
	glutDisplayFunc(displayWrapper);
	glutKeyboardFunc(keyboardDownWrapper);
	glutKeyboardUpFunc(keyboardUpWrapper);
	glutSpecialFunc(specialKeyboardDownWrapper);
	glutSpecialUpFunc(specialKeyboardUpWrapper);
	
	init();						// Initialize
	glutIdleFunc(runWrapper); 	// The program run loop
	glutMainLoop();				// Start the main GLUT thread
}

void GlutFramework::load() 
{
	// Subclass and override this method
}

void GlutFramework::display()
{
	// Subclass and override this method	
	Primitive primitive( Primitive::kTeapot, 2.5);
	primitive.draw();
}

void GlutFramework::reshape(int width, int height) 
{
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
}

// ----------------------------------------------------------------------------
// MOUSE LOGIC
//
void GlutFramework::mouseButtonPressLogic(int button, int state, int x, int y) 
{
	// Get current position
	if ( m_modKey )
	{
		m_posPrevX = x;
		m_posPrevY = y;
	}

	if(button==GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			l_mouse_down = true;
		else
			l_mouse_down = false;
	}
	else if (button==GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
			m_mouse_down = true;
		else
			m_mouse_down = false;
	}
	else if (button==GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			r_mouse_down = true;
		else
			r_mouse_down = false;
	};
};

//virtual 
void GlutFramework::mouseMoveLogic(int x, int y)
{	
	if ( m_modKey && 
	   ( l_mouse_down || m_mouse_down || r_mouse_down ) )
	{
		float deltaX = x - m_posPrevX;
		float deltaY = y - m_posPrevY;

		m_posPrevX = x;
		m_posPrevY = y;

		if ( l_mouse_down )
		{
			camera.rotate( deltaX, deltaY );
		}
		else if ( m_mouse_down )
		{
			camera.pan( deltaX, deltaY );
		}
		else if ( r_mouse_down )
		{
			float distance = camera.distance();

			distance += deltaX * -0.05f;
            distance += deltaY *  0.05f;
            distance  = std::max( 0.01f, distance );
			camera.zoom( distance );
		};
		
	};
};

// ----------------------------------------------------------------------------
// KEYBOARD LOGIC
//
void GlutFramework::keyboardDownLogic( unsigned char key, int x, int y ) 
{
	keyboard.keyDown( (int)key );

	// Key Actions
	switch (key)
	{
		case 27: // ESC key
			exit (0);
			break;
		case ' ':
			m_modKey = true;
			break;
		default:
			break;
	};
};

void GlutFramework::keyboardUpLogic( unsigned char key, int x, int y ) 
{
	keyboard.keyUp( (int)key );

	if ( key == ' ' )
		m_modKey = false;
}

void GlutFramework::specialKeyboardDownLogic( int key, int x, int y ) 
{
	printf( "SpecialKeyboardDown: %d\n", key );
}

void GlutFramework::specialKeyboardUpLogic( int key, int x, int y ) 
{
	printf( "SpecialKeyboardUp: %d \n", key );
}

// ----------------------------------------------------------------------------

void GlutFramework::mouseButtonPress(int button, int state, int x, int y) 
{
	// Subclass and override this method	
	//printf("MouseButtonPress: x: %d y: %d\n", x, y);
	mouseButtonPressLogic(button,state,x,y);
};

void GlutFramework::mouseMove(int x, int y)
{
	// Subclass and override this method	
	//printf("MouseMove: x: %d y: %d\n", x, y);
	mouseMoveLogic(x,y);
};

void GlutFramework::keyboardDown( unsigned char key, int x, int y ) 
{
	// Subclass and override this method	
	//printf( "KeyboardDown: %c = %d\n", key, (int)key );
	keyboardDownLogic(key,x,y);
};

void GlutFramework::keyboardUp( unsigned char key, int x, int y ) 
{
	// Subclass and override this method	
	//printf( "KeyboardUp: %c \n", key );
	keyboardUpLogic(key,x,y);
};

void GlutFramework::specialKeyboardDown( int key, int x, int y ) 
{
	// Subclass and override this method	
	//printf( "SpecialKeyboardDown: %d\n", key );
	specialKeyboardDownLogic(key,x,y);
};

void GlutFramework::specialKeyboardUp( int key, int x, int y ) 
{
	// Subclass and override this method	
	//printf( "SpecialKeyboardUp: %d \n", key );
	specialKeyboardUpLogic(key,x,y);
};

// ----------------------------------------------------------------------------

// ******************************
// ** Graphics helper routines **
// ******************************

// Initialize the projection/view matricies.
void GlutFramework::setDisplayMatricies() 
{
	/* Setup the projection and model view matricies */
	int width  = glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	float aspectRatio = width/height;
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, aspectRatio, 1, 500.0 );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void GlutFramework::setupLights() 
{
	GLfloat light1_position[] = { 0.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat ambient_light[] = { 0.8, 0.8, 0.8, 1.0 };
	
	glLightfv( GL_LIGHT0, GL_POSITION, light1_position );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, white_light );
	glLightfv( GL_LIGHT0, GL_SPECULAR, white_light );
	
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );
}

void GlutFramework::setTitle( const std::string& title ) 
{
	m_title = title;
};

void GlutFramework::showGrid( bool status )
{
	m_show_grid = status;
};

// **************************
// ** GLUT Setup functions **
// **************************
void GlutFramework::init() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	load();
};

void GlutFramework::run() 
{
	glutPostRedisplay();
};

void GlutFramework::displayFramework() 
{
	// Start the timer on the initial frame
	m_timer.start();
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear once
	
	setupLights();
	setDisplayMatricies();
	
	// Set Camera
	camera.draw();

	// Show Grid
	if ( m_show_grid )
		grid.draw();

	// Run Display Function.	
	display();

	// Clear Buffers
	glutSwapBuffers();

	// Stores Runtime FPS
	m_frame_rate = m_timer.end() * GlutFramework::FRAME_TIME;
}

// ******************************************************************
// ** Static functions which are passed to Glut function callbacks **
// ******************************************************************

void GlutFramework::displayWrapper() {
	instance->displayFramework(); 
}

void GlutFramework::reshapeWrapper(int width, int height) {
	instance->reshape(width, height);
}

void GlutFramework::runWrapper() {
	instance->run();
}

void GlutFramework::mouseButtonPressWrapper(int button, int state, int x, int y) {
	instance->mouseButtonPress(button, state, x, y);
}

void GlutFramework::mouseMoveWrapper(int x, int y) {
	instance->mouseMove(x, y);
}
									 
void GlutFramework::keyboardDownWrapper(unsigned char key, int x, int y) {
	instance->keyboardDown(key,x,y);
}

void GlutFramework::keyboardUpWrapper(unsigned char key, int x, int y) {
	instance->keyboardUp(key,x,y);
}

void GlutFramework::specialKeyboardDownWrapper(int key, int x, int y) {
	instance->specialKeyboardDown(key,x,y);
}

void GlutFramework::specialKeyboardUpWrapper(int key, int x, int y) {
	instance->specialKeyboardUp(key,x,y);
}
	
} // end namespace glutFramework
