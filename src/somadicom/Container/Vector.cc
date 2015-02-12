#ifdef SOMA_IO_DICOM
#include <soma-io/Container/Vector.h>
#else
#include <Container/Vector.h>
#endif

#include <cmath>
#include <cassert>


soma::Vector::Vector()
            : x( 0.0 ),
              y( 0.0 ),
              z( 0.0 )
{
}


soma::Vector::Vector( const soma::Vector& other )
            : x( other.x ), 
              y( other.y ), 
              z( other.z )  
{
}


soma::Vector::Vector( double theX, double theY, double theZ )
            : x( theX ),
              y( theY ),
              z( theZ )
{
}


soma::Vector& soma::Vector::operator += ( const soma::Vector& other )
{

  x += other.x;
  y += other.y;
  z += other.z;

  return *this;

}


soma::Vector& soma::Vector::operator -= ( const soma::Vector& other )
{

  x -= other.x;
  y -= other.y;
  z -= other.z;

  return *this;

}


soma::Vector& soma::Vector::operator *= ( double value )
{

  x *= value;
  y *= value;
  z *= value;

  return *this;

}


soma::Vector& soma::Vector::operator /= ( double value )
{

  assert( std::fabs( value ) > 1e-9 );
  x /= value;
  y /= value;
  z /= value;

  return *this;

}


soma::Vector soma::Vector::cross( const soma::Vector& other ) const
{

  return soma::Vector( y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x );

}


double soma::Vector::dot( const soma::Vector& other )
{

  return x * other.x + y * other.y + z * other.z;

}


double soma::Vector::getNorm()
{

  return std::sqrt( x * x + y * y + z * z );

}


void soma::Vector::normalize()
{


  operator /= ( getNorm() );

}


soma::Vector soma::Vector::mainDirection() const
{

  soma::Vector mainVector( 0.0, 0.0, 0.0 );
  double absX = std::fabs( x );
  double absY = std::fabs( y );
  double absZ = std::fabs( z );

  if ( absX > absY )
  {

    if ( absX > absZ )
    {
  
      mainVector.x = x / absX;
  
    }
    else
    {
  
      mainVector.z = z / absZ;
  
    }

  }
  else
  {

    if ( absY > absZ )
    {
  
      mainVector.y = y / absY;
  
    }
    else
    {
   
      mainVector.z = z / absZ;
  
    }

  }

  return mainVector;

}


soma::Vector soma::Vector::absoluteCoordinates() const
{

  return soma::Vector( std::fabs( x ), std::fabs( y ), std::fabs( z ) );

}


soma::Vector operator + ( const soma::Vector& vec )
{

  return vec;

}


soma::Vector operator - ( const soma::Vector& vec )
{

  return soma::Vector( -vec.x, -vec.y, -vec.z );

}


soma::Vector operator + ( const soma::Vector& vec1, const soma::Vector& vec2 )
{

  return soma::Vector( vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z );

}


soma::Vector operator - ( const soma::Vector& vec1, const soma::Vector& vec2 )
{

  return soma::Vector( vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z );

}


soma::Vector operator * ( const soma::Vector& vec, const double& val )
{

  return soma::Vector( val * vec.x, val * vec.y, val * vec.z );

}


soma::Vector operator / ( const soma::Vector& vec, const double& val )
{

  return soma::Vector( vec.x / val, vec.y / val, vec.z / val );

}


std::ostream& std::operator << ( std::ostream& os, const soma::Vector& vec )
{

  os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";

  return os;

}
