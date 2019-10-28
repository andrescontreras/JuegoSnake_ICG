// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "Object.h"
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>

// -------------------------------------------------------------------------
Object::
Object( )
  : m_Mesh( nullptr ),
    m_Animating( false )
{
}

// -------------------------------------------------------------------------
Object::
Object( const std::string& fname,Mesh** omesh )
  : m_Mesh( nullptr ),
    m_QuaternionAxis( 0, 0, 0 ),
    m_QuaternionReal( 1 ),
    m_Animating( false )
{
  // Open file and put its contents into a string buffer
  std::ifstream in( fname.c_str( ) );
  if( !in )
  {
    in.close( );
    throw std::runtime_error(
      std::string( "Error: Could not open \"" ) + fname + "\""
      );
  } // end if
  std::istringstream buffer(
    std::string(
      ( std::istreambuf_iterator< char >( in ) ),
      std::istreambuf_iterator< char >( )
      )
    );
  in.close( );
  std::string line;
  this->m_Mesh = *omesh;
  std::getline( buffer, line );
  // Read file
  buffer >> this;
}


// -------------------------------------------------------------------------
Object::
Object( const std::string& name,const std::string fname , float r, float g, float b, float scalex,float scaley,float scalez)
    : m_Mesh( nullptr ),
      m_Animating( false )
{

}
// -------------------------------------------------------------------------
Object::
~Object( )
{
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  for( Object* c: this->m_Children )
    delete c;
  this->m_Children.clear( );
}

// -------------------------------------------------------------------------
Mesh* Object::
getMesh( )
{
  return( this->m_Mesh );
}

// -------------------------------------------------------------------------
const Mesh* Object::
getMesh( ) const
{
  return( this->m_Mesh );
}

// -------------------------------------------------------------------------
void Object::
addChild( Object* o )
{
  this->m_Children.push_back( o );
}

// -------------------------------------------------------------------------
unsigned long Object::
getNumberOfChildren( ) const
{
  return( this->m_Children.size( ) );
}

// -------------------------------------------------------------------------
void Object::
restoreColor()
{

}

// -------------------------------------------------------------------------
Object* Object::
getChild( unsigned long i )
{
  return( this->m_Children[ i ] );
}

// -------------------------------------------------------------------------
const Object* Object::
getChild( unsigned long i ) const
{
  return( this->m_Children[ i ] );
}

// -------------------------------------------------------------------------
const std::string& Object::
getName( ) const
{
  return( this->m_Name );
}

// -------------------------------------------------------------------------
const float& Object::
getScaleX( ) const
{
  return( this->m_ScaleX );
}
// -------------------------------------------------------------------------
const float& Object::
getScaleY( ) const
{
  return( this->m_ScaleY );
}
// -------------------------------------------------------------------------
const float& Object::
getScaleZ( ) const
{
  return( this->m_ScaleZ );
}

// -------------------------------------------------------------------------
void Object::
rotateX(const float& angle)
{
  float s1 = std::cos( angle / 2.0 );
  float s2 = this->m_QuaternionReal;
  Vector a1( std::sin( angle / 2.0 ), 0, 0 );
  Vector a2 = this->m_QuaternionAxis;

  this->m_QuaternionReal = ( s1 * s2 ) - ( a1 / a2 );
  this->m_QuaternionAxis = ( a2 * s1 ) + ( a1 * s2 ) + ( a1 * a2 );
}

// -------------------------------------------------------------------------
void Object::
rotateY(const float& angle)
{
   float s1 = std::cos( angle / 2.0 );
  float s2 = this->m_QuaternionReal;
  Vector a1( 0,std::sin( angle / 2.0 ), 0 );
  Vector a2 = this->m_QuaternionAxis;

  this->m_QuaternionReal = ( s1 * s2 ) - ( a1 / a2 );
  this->m_QuaternionAxis = ( a2 * s1 ) + ( a1 * s2 ) + ( a1 * a2 );
}
// -------------------------------------------------------------------------
void Object::
setQuaternionAxis(Vector n_QuaternionAxis)
{
  this->m_QuaternionAxis = n_QuaternionAxis;
}

// -------------------------------------------------------------------------
void Object::
setQuaternionReal(float n_QuaternionReal)
{
  this->m_QuaternionReal = n_QuaternionReal;
}

// -------------------------------------------------------------------------
Vector Object::
getQuaternionAxis()
{
  return this->m_QuaternionAxis;
}

// -------------------------------------------------------------------------
float Object::
getQuaternionReal()
{
  return this->m_QuaternionReal;
}

// -------------------------------------------------------------------------
void Object::
rotateZ(const float& angle)
{
  float s1 = std::cos( angle / 2.0 );
  float s2 = this->m_QuaternionReal;
  Vector a1( 0, 0, std::sin( angle / 2.0 ));
  Vector a2 = this->m_QuaternionAxis;

  this->m_QuaternionReal = ( s1 * s2 ) - ( a1 / a2 );
  this->m_QuaternionAxis = ( a2 * s1 ) + ( a1 * s2 ) + ( a1 * a2 );
}


// -------------------------------------------------------------------------
void Object::
drawInOpenGLContext( GLenum mode )
{

  if( this->m_Mesh == nullptr )
    return;
  // Save call matrix
  glPushMatrix( );
  glScalef(this->m_ScaleX,this->m_ScaleY,this->m_ScaleZ);
  Vector axis = this->m_QuaternionAxis;
  float norm = axis.getNorm( );
  if( norm > 1e-5 )
  {
    float angle = std::acos( this->m_QuaternionReal ) * ( 2.0 / _PI_180 );
    glRotatef( angle, axis[ 0 ] / norm, axis[ 1 ] / norm, axis[ 2 ] / norm );
  } // end if
  this->m_Mesh->drawInOpenGLContext(mode);
  glPopMatrix( );

  // Show children
  for( Object* child: this->m_Children )
    child->drawInOpenGLContext( mode );
}


// -------------------------------------------------------------------------

void Object::
_strIn( std::istream& in )
{

  // Read data for this spatial object
  std::string line;
  std::getline( in, line );
  std::istringstream str2( line );
  str2 >> this->m_ScaleX;
  str2 >> this->m_ScaleY;
  str2 >> this->m_ScaleZ;
  str2 >> this->m_OriginalColor[0];
  str2 >> this->m_OriginalColor[1];
  str2 >> this->m_OriginalColor[2];
  this->m_Frequency = 60;
  std::getline( in, line );



}

// -------------------------------------------------------------------------
void Object::
_strOut( std::ostream& out ) const
{
}

// eof - Object.cxx

