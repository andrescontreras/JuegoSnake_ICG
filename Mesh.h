// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Mesh__h__
#define __Mesh__h__

#include <iostream>
#include <vector>
#include <GL/gl.h>

/**
 */
class Mesh
{
public:
  //! Streaming methods
  //@{
  friend std::istream& operator>>( std::istream& i, Mesh& s )
    {
      s._strIn( i );
      return( i );
    }

  friend std::istream& operator>>( std::istream& i, Mesh* s )
    {
      s->_strIn( i );
      return( i );
    }

  friend std::ostream& operator<<( std::ostream& o, const Mesh& s )
    {
      s._strOut( o );
      return( o );
    }

  friend std::ostream& operator<<( std::ostream& o, const Mesh* s )
    {
      s->_strOut( o );
      return( o );
    }
  //@}

public:
  //! Memory management
  //@{
  Mesh( );
  Mesh( const std::string& fname );
  virtual ~Mesh( );
  //@}

  //! Geometry-related methods
  //@{
  unsigned long getNumberOfPoints(int geo) const;
  float* getPoint(int geo, unsigned long i );
  const float* getPoint(int geo, unsigned long i ) const;
  void getPoint(int geo, unsigned long i, float* p ) const;
  void getPoint(int geo, unsigned long i, double* p ) const;

  unsigned long addPoint(int geo, float x, float y, float z );
  unsigned long addPoint(int geo, double x, double y, double z );
  unsigned long addPoint(int geo, float* p );
  unsigned long addPoint(int geo, double* p );

  void setPoint(int geo, unsigned long i, float x, float y, float z );
  void setPoint(int geo, unsigned long i, double x, double y, double z );
  void setPoint(int geo, unsigned long i, float* p );
  void setPoint(int geo, unsigned long i, double* p );
  //@}


  //! Topology-related methods
  //@{
  template< class _TContainer >
  void addFace(int tp, const _TContainer& f );

  template< class _TIterator >
  inline void addFace(int tp, _TIterator b, _TIterator e )
    {
      std::vector< unsigned long > f;
      for( _TIterator i = b; i != e; ++i )
        f.push_back( ( unsigned long )( *i ) );
      this->addFace(tp, f );
    }

  //! vector+natural+variadic arguments
  template< class _TNatural, class... _TArgs >
  inline void addFace(
    int tp,
    std::vector< unsigned long >& f,
    const _TNatural& x,
    _TArgs... args
    )
    {
      f.push_back( ( unsigned long )( x ) );
      this->addFace(tp, f, args... );
    }

  //! natural+variadic arguments
  template< class _TNatural, class... _TArgs >
  inline void addFace(int tp, const _TNatural& x, _TArgs... args )
    {
      std::vector< unsigned long > f;
      f.push_back( ( unsigned long )( x ) );
      this->addFace(tp, f, args... );
    }
  //@}

  //! Colors
  //@{
  float* getColor( );
  const float* getColor( ) const;
  void getColor( float* p ) const;

  template< class _TRed, class _TGreen, class _TBlue >
  inline void setColor( _TRed r, _TGreen g, _TBlue b )
    {
      this->m_Color[ 0 ] = float( r );
      this->m_Color[ 1 ] = float( g );
      this->m_Color[ 2 ] = float( b );
    }
  //@}

  //! All the magic happens here
  virtual void drawInOpenGLContext( GLenum mode );

protected:
  //! Here's where the real streaming is done
  //@{
  void _strIn( std::istream& in );
  void _strOut( std::ostream& out ) const;
  //@}

protected:
  std::vector<std::vector< float >>          m_Geometry;
  std::vector<std::vector< unsigned long >>  m_Topology;

  float                        m_Color[ 3 ];
};

#endif // __Mesh__h__

// eof - Mesh.h


