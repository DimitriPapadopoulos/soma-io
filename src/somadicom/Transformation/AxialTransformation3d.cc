#ifdef SOMA_IO_DICOM
#include <soma-io/Transformation/AxialTransformation3d.h>
#else
#include <Transformation/AxialTransformation3d.h>
#endif

#include <cmath>


soma::AxialTransformation3d::AxialTransformation3d()
                           : soma::Transformation3d()
{
}


soma::AxialTransformation3d::AxialTransformation3d( 
                                               const soma::Vector& rowCosine,
                                               const soma::Vector& columnCosine,
                                               const soma::Vector& normal,
                                               const soma::Vector& origin )
                           : soma::Transformation3d()
{

  soma::Vector rowVec = rowCosine.mainDirection();
  soma::Vector columnVec = columnCosine.mainDirection();
  soma::Vector normalVec = normal.mainDirection();

  setItems(  rowVec.x,  columnVec.x,  normalVec.x, origin.x,
             rowVec.y,  columnVec.y,  normalVec.y, origin.y,
            -rowVec.z, -columnVec.z, -normalVec.z, origin.z,
             0.0,       0.0,          0.0,         1.0 );

}


soma::AxialTransformation3d::AxialTransformation3d( 
                                      const soma::AxialTransformation3d& other )
                           : soma::Transformation3d( other )
{
}


void soma::AxialTransformation3d::setTranslation( 
                                               const soma::Vector& translation )
{

  _direct[ 0 ][ 3 ] = std::fabs( _direct[ 0 ][ 2 ] * translation.x );
  _direct[ 1 ][ 3 ] = std::fabs( _direct[ 1 ][ 2 ] * translation.y );
  _direct[ 2 ][ 3 ] = std::fabs( _direct[ 2 ][ 2 ] * translation.z );

  invert( _direct, _inverse );

}


void soma::AxialTransformation3d::getDirect( 
                     const double fromX, const double fromY, const double fromZ,
                     double& toX, double& toY, double& toZ ) const
{

  if ( std::fabs( _direct[ 0 ][ 2 ] ) > 0.0 ) // sagittal
  {

    toX = _direct[ 0 ][ 2 ] * fromZ + _direct[ 0 ][ 3 ];
    toY = _direct[ 1 ][ 0 ] * fromX;
    toZ = _direct[ 2 ][ 1 ] * fromY;

  }
  else if ( std::fabs( _direct[ 1 ][ 2 ] ) > 0.0 ) // coronal
  {

    toX = _direct[ 0 ][ 0 ] * fromX;
    toY = _direct[ 1 ][ 2 ] * fromZ + _direct[ 1 ][ 3 ];
    toZ = _direct[ 2 ][ 1 ] * fromY;

  }
  else // axial
  {

    toX = _direct[ 0 ][ 0 ] * fromX;
    toY = _direct[ 1 ][ 1 ] * fromY;
    toZ = _direct[ 2 ][ 2 ] * fromZ + _direct[ 2 ][ 3 ];

  }

}


void soma::AxialTransformation3d::getInverse( 
                           const double toX, const double toY, const double toZ,
                           double& fromX, double& fromY, double& fromZ ) const
{

  if ( std::fabs( _direct[ 0 ][ 2 ] ) > 0.0 ) // sagittal
  {

    fromX = _direct[ 1 ][ 0 ] * toY;
    fromY = _direct[ 2 ][ 1 ] * toZ;
    fromZ = _direct[ 0 ][ 2 ] * ( toX - _direct[ 0 ][ 3 ] );

  }
  else if ( std::fabs( _direct[ 1 ][ 2 ] ) > 0.0 ) // coronal
  {

    fromX = _direct[ 0 ][ 0 ] * toX;
    fromY = _direct[ 2 ][ 1 ] * toZ;
    fromZ = _direct[ 1 ][ 2 ] * ( toY - _direct[ 1 ][ 3 ] );

  }
  else // axial
  {

    fromX = _direct[ 0 ][ 0 ] * toX;
    fromY = _direct[ 1 ][ 1 ] * toY;
    fromZ = _direct[ 2 ][ 2 ] * ( toZ - _direct[ 2 ][ 3 ] );

  }

}

