/* -------------------------------------------------------------------------
 * @brief Simulation of a simple solar system
 * @author Leonardo Flórez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "Camera.h"
#include "World.h"

#include <chrono>

// -------------------------------------------------------------------------
Camera myCamera;
World* myWorld = nullptr;
bool pause = false;
int dir = 1;
std::chrono::time_point< std::chrono::high_resolution_clock > m_StartAnimation;
double milisegundos = 0;
double frames = 0;

float angle = 0;
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_position1[] = {2.0f, 5.0f, 5.0f, 0.0f  };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

// -------------------------------------------------------------------------
World* initWorld( int argc, char* argv[] );
void destroyWorld( World* star);

// -------------------------------------------------------------------------
void DrawSquare(GLenum mode)
{
	glBegin(mode);
	{
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
	}
	glEnd();
}

// -------------------------------------------------------------------------
void displayCbk( );
void idleCbk( );
void resizeCbk( int w, int h );
void keyboardCbk( unsigned char key, int x, int y );
void specialKeyboardCbk( int key, int x, int y );
void mouseClickCbk( int button, int state, int x, int y );
void mouseMoveCbk( int x, int y );

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  // Init OpenGL context
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1024, 768 );
  glutCreateWindow( "CONGA" );

  // Init world
  try
  {
    myWorld = initWorld( argc, argv );
    glutDisplayFunc( displayCbk );
    glutIdleFunc( idleCbk );
    glutReshapeFunc( resizeCbk );
    glutKeyboardFunc( keyboardCbk );
    glutSpecialFunc( specialKeyboardCbk);
    glutMouseFunc( mouseClickCbk );
    glutMotionFunc( mouseMoveCbk );
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse1);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glutMainLoop( );

    destroyWorld( myWorld);
    return( 0 );
  }
  catch( std::exception& err )
  {
    std::cerr << err.what( ) << std::endl;
    return( 1 );
  } // end if
}

// -------------------------------------------------------------------------
World* initWorld( int argc, char* argv[] )
{
  // Initialize camera
  myCamera.setFOV( 45 );
  myCamera.setPlanes( 1e-2, 10000 );
  m_StartAnimation = std::chrono::high_resolution_clock::now( );
  // OpenGL initialization
  glClearColor( 0, 0, 0, 0 );
  // Read world
  return( new World() );
}

// -------------------------------------------------------------------------
void destroyWorld( World* star)
{
  if( star != nullptr )
    delete star;
}

// -------------------------------------------------------------------------
void displayCbk( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);

    glEnable(GL_LIGHT0);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  // Prepare model matrix
  myCamera.loadCameraMatrix();

  // Draw the scene
    myWorld->drawInOpenGLContext(GL_POLYGON);
    glPushMatrix();
    glTranslatef(0,-3,0);
    glColor3f(0.921568,0.921568,0.921568);
    glScalef(100,0.5,100);
    glutSolidCube(5);
    glPopMatrix();
  // Finish
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
void idleCbk( )
{
  if(!pause)
  {
    glutPostRedisplay( );
    myWorld->moveMonkeys(dir);
  }
  milisegundos =
                std::chrono::duration_cast< std::chrono::milliseconds >(
                    std::chrono::high_resolution_clock::now( ) - m_StartAnimation
                    ).count( );
  if(milisegundos/1000 >= 1.0)
  {
      m_StartAnimation = std::chrono::high_resolution_clock::now( );
      std::cout << frames << std::endl;
      frames = 0;
  }
  else
  {
      frames++;
  }
}


// -------------------------------------------------------------------------
void resizeCbk( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  myCamera.setWindow( w, h );
  myCamera.loadProjectionMatrix( );
}

// -------------------------------------------------------------------------
void keyboardCbk( unsigned char key, int x, int y )
{
  switch( key )
  {
  case 'w': case 'W':
  {
    myCamera.increaseAngleY() ;
    glutPostRedisplay( );
  }
    break;
  case 's': case 'S':
  {
    myCamera.decreaseAngleY() ;
    glutPostRedisplay( );
  }
    break;
  case 'a': case 'A':
  {
    myCamera.decreaseAngleX() ;
    glutPostRedisplay( );
  }
    break;
  case 'd': case 'D':
  {
    myCamera.increaseAngleX();
    glutPostRedisplay( );
  }
    break;
  case 'q': case 'Q':
  {
    myCamera.increaseZoom();
    glutPostRedisplay( );
  }
    break;
  case 'e': case 'E':
  {
    myCamera.decreaseZoom() ;
    glutPostRedisplay( );
  }
    break;
  case 'p': case 'P':
  {
    pause = !pause;
  }
    break;
  default:
    break;
  } // end switch

}

// -------------------------------------------------------------------------
void specialKeyboardCbk( int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        dir = 4;
        break;
    case GLUT_KEY_DOWN:
        dir = 3;
        break;
    case GLUT_KEY_RIGHT:
        dir = 1;
        break;
    case GLUT_KEY_LEFT:
        dir = 2;
        break;
    }
}

// -------------------------------------------------------------------------
void mouseClickCbk( int button, int state, int x, int y )
{
  if( state == GLUT_DOWN )
    myCamera.setReference( x, y );
  else
    myCamera.setReference( 0, 0 );
}

// -------------------------------------------------------------------------
void mouseMoveCbk( int x, int y )
{
  int dx, dy;
  myCamera.getReference( dx, dy, x, y );
  myCamera.setReference( x, y );

  // Apply rotations
  if( dx > 0 )      myCamera.rotY( -0.5 );
  else if( dx < 0 ) myCamera.rotY( 0.5 );
  if( dy > 0 )      myCamera.rotX( 0.5 );
  else if( dy < 0 ) myCamera.rotX( -0.5 );

  // Redraw
  glutPostRedisplay( );
}

// eof - RobotWorld.cxx

