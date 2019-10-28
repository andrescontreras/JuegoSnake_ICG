// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "Mesh.h"
#include <cstring>
#include <deque>
#include <fstream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
// -------------------------------------------------------------------------
Mesh::
Mesh( )
{
  std::vector<float> a;
  std::vector<float> b;
  std::vector< unsigned long > a1;
  std::vector< unsigned long > b1;
  m_Geometry.push_back(a);
  m_Geometry.push_back(b);
  m_Topology.push_back(a1);
  m_Topology.push_back(b1);
  this->m_Color[ 0 ] = this->m_Color[ 1 ] = this->m_Color[ 2 ] = 1;
}

// -------------------------------------------------------------------------
Mesh::
Mesh( const std::string& fname )
{
  std::vector<float> a;
  std::vector<float> b;
  std::vector< unsigned long > a1;
  std::vector< unsigned long > b1;
  m_Geometry.push_back(a);
  m_Geometry.push_back(b);
  m_Topology.push_back(a1);
  m_Topology.push_back(b1);
  this->m_Color[ 0 ] = this->m_Color[ 1 ] = this->m_Color[ 2 ] = 1;
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

  // Read file
  buffer >> this;
}

// -------------------------------------------------------------------------
Mesh::
~Mesh( )
{
}

// -------------------------------------------------------------------------
unsigned long Mesh::
getNumberOfPoints( int geo ) const
{
  return( this->m_Geometry[geo].size( ) / 3 );
}

// -------------------------------------------------------------------------
float* Mesh::
getPoint(int geo, unsigned long i )
{
  return( this->m_Geometry[geo].data( ) + ( i * 3 ) );
}

// -------------------------------------------------------------------------
const float* Mesh::
getPoint(int geo, unsigned long i ) const
{
  return( this->m_Geometry[geo].data( ) + ( i * 3 ) );
}

// -------------------------------------------------------------------------
void Mesh::
getPoint(int geo, unsigned long i, float* p ) const
{
  std::memcpy( p, this->getPoint(geo, i ), 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
void Mesh::
getPoint(int geo, unsigned long i, double* p ) const
{
  const float* fp = this->getPoint( geo, i );
  p[ 0 ] = double( fp[ 0 ] );
  p[ 1 ] = double( fp[ 1 ] );
  p[ 2 ] = double( fp[ 2 ] );
}

// -------------------------------------------------------------------------
unsigned long Mesh::
addPoint(int geo, float x, float y, float z )
{
  this->m_Geometry[geo].push_back( x );
  this->m_Geometry[geo].push_back( y );
  this->m_Geometry[geo].push_back( z );
  return( this->getNumberOfPoints( geo ) - 1 );

}

// -------------------------------------------------------------------------
unsigned long Mesh::
addPoint(int geo, double x, double y, double z )
{
  this->m_Geometry[geo].push_back( float( x ) );
  this->m_Geometry[geo].push_back( float( y ) );
  this->m_Geometry[geo].push_back( float( z ) );
  return( this->getNumberOfPoints(geo) - 1 );
}

// -------------------------------------------------------------------------
unsigned long Mesh::
addPoint(int geo, float* p )
{
  return( this->addPoint(geo, p[ 0 ], p[ 1 ], p[ 2 ] ) );
}

// -------------------------------------------------------------------------
unsigned long Mesh::
addPoint(int geo, double* p )
{
  return( this->addPoint(geo, p[ 0 ], p[ 1 ], p[ 2 ] ) );
}

// -------------------------------------------------------------------------
void Mesh::
setPoint(int geo, unsigned long i, float x, float y, float z )
{
  float* fp = this->getPoint(geo, i );
  fp[ 0 ] = x;
  fp[ 1 ] = y;
  fp[ 2 ] = z;
}

// -------------------------------------------------------------------------
void Mesh::
setPoint(int geo, unsigned long i, double x, double y, double z )
{
  float* fp = this->getPoint(geo, i );
  fp[ 0 ] = float( x );
  fp[ 1 ] = float( y );
  fp[ 2 ] = float( z );
}

// -------------------------------------------------------------------------
void Mesh::
setPoint(int geo, unsigned long i, float* p )
{
  std::memcpy( this->getPoint(geo, i ), p, 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
void Mesh::
setPoint(int geo, unsigned long i, double* p )
{
  float* fp = this->getPoint(geo, i );
  fp[ 0 ] = float( p[ 0 ] );
  fp[ 1 ] = float( p[ 1 ] );
  fp[ 2 ] = float( p[ 2 ] );
}

// -------------------------------------------------------------------------
#define Mesh_addFace_IMPL( _tp_, _c_, _t_ )                                   \
  template<>                                                            \
  void Mesh::                                                           \
  addFace< std::_c_< unsigned _t_ > >(                                  \
    int tp,                                                             \
    const std::_c_< unsigned _t_ >& f                                   \
    )                                                                   \
  {                                                                     \
    this->m_Topology[tp].push_back( f.size( ) );                            \
    for( const unsigned _t_& v: f )                                     \
      this->m_Topology[tp].push_back( ( unsigned long )( v ) );             \
  }
Mesh_addFace_IMPL(int tp, deque, char );
Mesh_addFace_IMPL(int tp, deque, short );
Mesh_addFace_IMPL(int tp, deque, int );
Mesh_addFace_IMPL(int tp, deque, long );
Mesh_addFace_IMPL(int tp, deque, long long );

Mesh_addFace_IMPL(int tp, list, char );
Mesh_addFace_IMPL(int tp, list, short );
Mesh_addFace_IMPL(int tp, list, int );
Mesh_addFace_IMPL(int tp, list, long );
Mesh_addFace_IMPL(int tp, list, long long );

Mesh_addFace_IMPL(int tp, vector, char );
Mesh_addFace_IMPL(int tp, vector, short );
Mesh_addFace_IMPL(int tp, vector, int );
Mesh_addFace_IMPL(int tp, vector, long );
Mesh_addFace_IMPL(int tp, vector, long long );

// -------------------------------------------------------------------------
float* Mesh::
getColor( )
{
  return( this->m_Color );
}

// -------------------------------------------------------------------------
const float* Mesh::
getColor( ) const
{
  return( this->m_Color );
}

// -------------------------------------------------------------------------
void Mesh::
getColor( float* p ) const
{
  std::memcpy( p, this->m_Color, 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
void Mesh::
drawInOpenGLContext( GLenum mode )
{
  if(mode == GL_POLYGON)
    glColor3fv( this->m_Color );
  else
  {
    glColor3f(0,0,0);
  }
  unsigned long i = 0;
  while( i < this->m_Topology[0].size( ) )
  {
    glBegin( mode );
    {
      for( unsigned long j = 0; j < this->m_Topology[0][ i ]; ++j )
      {
          if(m_Topology[1].size()>0)
          {
              glNormal3fv( this->getPoint(1, this->m_Topology[1][ i + j + 1 ] - 1 ) );
          }
          glVertex3fv( this->getPoint(0, this->m_Topology[0][ i + j + 1 ] - 1 ) );
      }
    }
    glEnd( );
    i += this->m_Topology[0][ i ] + 1;
  } // end while
}

// -------------------------------------------------------------------------
void Mesh::
_strIn( std::istream& in )
{
  for(unsigned int i = 0; i < m_Geometry.size(); i++)
    this->m_Geometry[i].clear( );
  for(unsigned int i = 0; i < m_Geometry.size(); i++)
    this->m_Topology[i].clear( );
  std::string line;
  std::getline( in, line );
  while( !in.eof( ) )
  {
    // Get command type
    std::istringstream str( line );
    std::string cmd;
    str >> cmd;

    // Process command
    if( cmd == "v" || cmd == "V" )
    {
      std::vector< float > p;
      while( !str.eof( ) )
      {
        float v;
        str >> v;
        p.push_back( v );
      } // end while
      this->addPoint(0, p.data( ) );
    }
    else if(cmd == "vn" || cmd == "VN" || cmd == "Vn" )
    {
       std::vector< float > p;
      while( !str.eof( ) )
      {
        float v;
        str >> v;
        p.push_back( v );
      } // end while
      this->addPoint(1, p.data( ) );
    }
    else if( cmd == "f" || cmd == "F" )
    {
      std::vector< unsigned long > f;
      std::vector< unsigned long > f2;
      std::size_t found = line.find("//");
      std::string s;
      bool h =true;
      s = str.str();
      std::replace(s.begin(), s.end(), '/', ' ');
      str.str(s);
      str >> cmd;
      int cont = 0;
      while( !str.eof( ) )
      {
        unsigned long v;
        if (found==std::string::npos)
        {
            str >> v;
            f.push_back(v);
        }
        else
        {
            if(h)
            {
                if( str>> v)
                {
                f.push_back(v);
                h = !h;
                }
            }
            else
            {
               if( str>> v)
                {
                f2.push_back(v);
                h = !h;
                }
            }
            cont++;
        }
      } // end while
      if(found == std::string::npos)
      {
        this->addFace(0, f );
      }
      else
      {
        this->addFace(0, f );
        this->addFace(1, f2 );
      }

    } // end if

    // Try next line
    std::getline( in, line );
  } // end while
}

// -------------------------------------------------------------------------
void Mesh::
_strOut( std::ostream& out ) const
{
  // Stream geometry
  unsigned long i = 0;
  for( i = 0; i < this->m_Geometry[0].size( ); ++i )
  {
      if( i % 3 == 0 )
        out << std::endl << "v ";
      out << this->m_Geometry[0][ i ];
  } // end for
  for( i = 0; i < this->m_Geometry[1].size( ); ++i )
  {
      if( i % 3 == 0 )
        out << std::endl << "vn ";
      out << this->m_Geometry[1][ i ];
  } // end for

  // Stream topology
  out << std::endl;
  i = 0;
  while( i < this->m_Topology.size( ) )
  {
    out << std::endl << "f ";
    for( unsigned long j = 0; j < this->m_Topology[0][i]; ++j )
      out << this->m_Topology[0][ i + j + 1 ] << "//" <<this->m_Topology[1][ i + j + 1 ] << " " ;
    i += this->m_Topology[0][ i ];
  } // end while
}

// eof - Mesh.cxx

