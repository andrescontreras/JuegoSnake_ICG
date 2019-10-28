
// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Object__h__
#define __Object__h__

#include "Vector.h"
#include "Mesh.h"
#include <chrono>

/**
 */
class Object
{
public:
  //! Streaming methods
  //@{
  friend std::istream& operator>>( std::istream& i, Object& s )
    {
      s._strIn( i );
      return( i );
    }

  friend std::istream& operator>>( std::istream& i, Object* s )
    {
      s->_strIn( i );
      return( i );
    }

  friend std::ostream& operator<<( std::ostream& o, const Object& s )
    {
      s._strOut( o );
      return( o );
    }

  friend std::ostream& operator<<( std::ostream& o, const Object* s )
    {
      s->_strOut( o );
      return( o );
    }
  //@}

public:


  //! Memory management
  //@{
  Object( );
  Object( const std::string& fname, Mesh** omesh );
  Object( const std::string& name,const std::string fname , float r, float g, float b, float scalex,float scaley,float scalez);
  virtual ~Object( );
  //@}

  //! Mesh-related methods
  //@{
  Mesh* getMesh( );
  const Mesh* getMesh( ) const;
  //@}

  //! All the magic of babies happens here
  //@{
  void addChild( Object* o );
  unsigned long getNumberOfChildren( ) const;
  Object* getChild( unsigned long i );
  const Object* getChild( unsigned long i ) const;
  //@}

  //! Other methods
  //@{
  const std::string& getName( ) const;
  const float& getScaleX( ) const;
  const float& getScaleY( ) const;
  const float& getScaleZ( ) const;
  void         rotateX(const float& angle);
  void         rotateY(const float& angle);
  void         rotateZ(const float& angle);
  void         setQuaternionAxis(Vector n_QuaternionAxis);
  void         setQuaternionReal(float  n_QuaternionReal);
  Vector       getQuaternionAxis();
  float        getQuaternionReal();
  void         restoreColor();

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

  std::string m_Name;
  float       m_ScaleX;
  float       m_ScaleY;
  float       m_ScaleZ;
  Mesh*       m_Mesh;
  Vector      m_QuaternionAxis;
  float       m_QuaternionReal;
  float       m_OriginalColor[ 3 ];


  float m_Frequency;
  bool m_Animating;
  std::chrono::time_point< std::chrono::high_resolution_clock > m_StartAnimation;

  std::vector< Object* > m_Children;

};

#endif // __Object__h__

// eof - Object.h

