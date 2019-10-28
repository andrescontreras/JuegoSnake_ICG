
// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "Vector.h"
#include <cmath>
#include <cstring>
#include <iostream>

// -------------------------------------------------------------------------
Vector::
Vector( const float& x, const float& y, const float& z )
{
  this->m_V[ 0 ] = x;
  this->m_V[ 1 ] = y;
  this->m_V[ 2 ] = z;
}

// -------------------------------------------------------------------------
Vector::
Vector( float* p )
{
  std::memcpy( this->m_V, p, 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
Vector::
Vector( double* p )
{
  this->m_V[ 0 ] = float( p[ 0 ] );
  this->m_V[ 1 ] = float( p[ 1 ] );
  this->m_V[ 2 ] = float( p[ 2 ] );
}

// -------------------------------------------------------------------------
Vector::
Vector( const Vector& r )
{
  std::memcpy( this->m_V, r.m_V, 3 * sizeof( float ) );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator=( const Vector& r )
{
  std::memcpy( this->m_V, r.m_V, 3 * sizeof( float ) );
  return( *this );
}

// -------------------------------------------------------------------------
Vector::
~Vector( )
{
}

// -------------------------------------------------------------------------
float& Vector::
operator[]( const unsigned int& i )
{
  return( this->m_V[ i ] );
}

// -------------------------------------------------------------------------
const float& Vector::
operator[]( const unsigned int& i ) const
{
  return( this->m_V[ i ] );
}

// -------------------------------------------------------------------------
Vector Vector::
operator+( const Vector& r ) const
{
  return(
    Vector(
      this->m_V[ 0 ] + r.m_V[ 0 ],
      this->m_V[ 1 ] + r.m_V[ 1 ],
      this->m_V[ 2 ] + r.m_V[ 2 ]
      )
    );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator+=( const Vector& r )
{
  this->m_V[ 0 ] += r.m_V[ 0 ];
  this->m_V[ 1 ] += r.m_V[ 1 ];
  this->m_V[ 2 ] += r.m_V[ 2 ];
  return( *this );
}

// -------------------------------------------------------------------------
Vector Vector::
operator-( const Vector& r ) const
{
  return(
    Vector(
      this->m_V[ 0 ] - r.m_V[ 0 ],
      this->m_V[ 1 ] - r.m_V[ 1 ],
      this->m_V[ 2 ] - r.m_V[ 2 ]
      )
    );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator-=( const Vector& r )
{
  this->m_V[ 0 ] -= r.m_V[ 0 ];
  this->m_V[ 1 ] -= r.m_V[ 1 ];
  this->m_V[ 2 ] -= r.m_V[ 2 ];
  return( *this );
}

// -------------------------------------------------------------------------
float Vector::
operator/( const Vector& r ) const
{
  float c = this->m_V[ 0 ] * r.m_V[ 0 ];
  c      += this->m_V[ 1 ] * r.m_V[ 1 ];
  c      += this->m_V[ 2 ] * r.m_V[ 2 ];
  return( c );
}

// -------------------------------------------------------------------------
Vector Vector::
operator*( const Vector& r ) const
{
  return(
    Vector(
      ( this->m_V[ 1 ] * r.m_V[ 2 ] ) - ( this->m_V[ 2 ] * r.m_V[ 1 ] ),
      ( this->m_V[ 2 ] * r.m_V[ 0 ] ) - ( this->m_V[ 0 ] * r.m_V[ 2 ] ),
      ( this->m_V[ 0 ] * r.m_V[ 1 ] ) - ( this->m_V[ 1 ] * r.m_V[ 0 ] )
      )
    );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator*=( const Vector& r )
{
  *this = *this * r;
  return( *this );
}

// -------------------------------------------------------------------------
Vector Vector::
operator*( const float& r ) const
{
  return(
    Vector(
      this->m_V[ 0 ] * r, this->m_V[ 1 ] * r,this->m_V[ 2 ] * r
      )
    );
}

// -------------------------------------------------------------------------
Vector Vector::
operator*( const double& r ) const
{
  return( this->operator*( float( r ) ) );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator*=( const float& r )
{
  this->m_V[ 0 ] *= r;
  this->m_V[ 1 ] *= r;
  this->m_V[ 2 ] *= r;
  return( *this );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator*=( const double& r )
{
  this->m_V[ 0 ] *= float( r );
  this->m_V[ 1 ] *= float( r );
  this->m_V[ 2 ] *= float( r );
  return( *this );
}

// -------------------------------------------------------------------------
Vector Vector::
operator/( const float& r ) const
{
  return(
    Vector(
      this->m_V[ 0 ] / r, this->m_V[ 1 ] / r,this->m_V[ 2 ] / r
      )
    );
}

// -------------------------------------------------------------------------
Vector Vector::
operator/( const double& r ) const
{
  return( this->operator/( float( r ) ) );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator/=( const float& r )
{
  this->m_V[ 0 ] /= r;
  this->m_V[ 1 ] /= r;
  this->m_V[ 2 ] /= r;
  return( *this );
}

// -------------------------------------------------------------------------
Vector& Vector::
operator/=( const double& r )
{
  this->m_V[ 0 ] /= float( r );
  this->m_V[ 1 ] /= float( r );
  this->m_V[ 2 ] /= float( r );
  return( *this );
}
// -------------------------------------------------------------------------
float Vector::
getXAngle( ) const
{
  float norm = this->getNorm();
  return (std::acos(this->m_V[ 0 ]/norm)*_180_PI);
}
// -------------------------------------------------------------------------
float Vector::
getYAngle( ) const
{
  float norm = this->getNorm();
  return (std::acos(this->m_V[ 1 ]/norm)*_180_PI);
}
// -------------------------------------------------------------------------
float Vector::
getZAngle( ) const
{
  float norm = this->getNorm();
  return (std::acos(this->m_V[ 2 ]/norm)*_180_PI);
}

// -------------------------------------------------------------------------
float Vector::
getPhiAngle( ) const
{
  return (std::acos(this->m_V[ 2 ]/std::sqrt(this->m_V[ 2 ]*this->m_V[ 2 ] +this->m_V[ 0 ]*this->m_V[ 0 ]))*_180_PI);
}
// -------------------------------------------------------------------------
float Vector::
getThetaAngle( ) const
{
  return getYAngle();
}
// -------------------------------------------------------------------------
void Vector::
updateVector(float aX, float aY, float aZ, float n)
{
    float norma = n;
    float px,py,pz;
    px = std::sin(aZ*_PI_180)*cos(aY*_PI_180) * norma;
    py = std::sin(aZ*_PI_180)*sin(aY*_PI_180)* norma;
    pz = std::cos(aZ*_PI_180) * norma;
    this->m_V[0] = px;
    this->m_V[1] = py;
    this->m_V[2] = pz;
}
// -------------------------------------------------------------------------
float Vector::
getNorm( ) const
{
  return( std::sqrt( *this / *this ) );
}

// -------------------------------------------------------------------------
void Vector::
normalize( )
{
  float n = this->getNorm( );
  *this /= ( ( 1e-5 < n )? n: 1.0 );
}

// eof - Vector.cxx

