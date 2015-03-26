#ifdef SOMA_IO_DICOM
#include <soma-io/config/somadicom.h>
#include <soma-io/Dicom/DicomIO.h>
#include <soma-io/Dicom/DicomReaderFactory.h>
#include <soma-io/Dicom/DicomDatasetHeader.h>
#include <soma-io/System/DirectoryParser.h>
#include <soma-io/Container/DicomProxy.h>
#include <soma-io/Object/HeaderProxy.h>
#ifdef SOMA_DICOM_JPEG2000_SUPPORT
#include <soma-io/Dicom/DcmtkJpeg2000/djdecode.h>
#endif
#else
#include <Dicom/DicomIO.h>
#include <Dicom/DicomReaderFactory.h>
#include <Dicom/DicomDatasetHeader.h>
#include <System/DirectoryParser.h>
#include <Container/DicomProxy.h>
#include <Object/HeaderProxy.h>
#include <Dicom/DcmtkJpeg2000/djdecode.h>
#endif

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcrledrg.h>
#include <dcmtk/dcmjpeg/djdecode.h>
#ifndef SOMA_IO_DICOM
#include <dcmtk/dcmjpls/djdecode.h>
#endif

#include <fstream>


soma::DicomIO::DicomIO()
             : soma::Singleton< soma::DicomIO >()
{

  DcmRLEDecoderRegistration::registerCodecs();
  DJDecoderRegistration::registerCodecs();

#ifdef SOMA_IO_DICOM
#ifdef SOMA_DICOM_JPEG2000_SUPPORT
  DJ2KDecoderRegistration::registerCodecs();
#endif
#else
  DJ2KDecoderRegistration::registerCodecs();
  DJLSDecoderRegistration::registerCodecs();
#endif

}


soma::DicomIO::~DicomIO()
{

#ifdef SOMA_IO_DICOM
#ifdef SOMA_DICOM_JPEG2000_SUPPORT
  DJ2KDecoderRegistration::cleanup();
#endif
#else
  DJLSDecoderRegistration::cleanup();
  DJ2KDecoderRegistration::cleanup();
#endif
  DJDecoderRegistration::cleanup();
  DcmRLEDecoderRegistration::cleanup();

}


bool soma::DicomIO::analyze( const std::string& fileName,
                             soma::DataInfo& dataInfo )
{

  soma::DirectoryParser directory( fileName );
  std::string selectedFile = directory.getSelectedFile();

  if ( checkDicom( selectedFile ) )
  {

    DcmFileFormat header;

    if ( header.loadFile( selectedFile.c_str() ).good() )
    {

      if ( _datasetModule.parseItem( header.getDataset() ) )
      {

        int32_t bits = _datasetModule.getBitsAllocated();

        dataInfo._depth = bits < 8 ? 8 : bits;
        dataInfo._spp = _datasetModule.getSamplesPerPixel();
        dataInfo._bpp = ( dataInfo._depth >> 3 ) * dataInfo._spp;

        return true;

      }

    }

  }

  return false;

}


bool soma::DicomIO::check( const std::string& fileName,
                           soma::DataInfo& dataInfo,
                           soma::DicomDatasetHeader& datasetHeader )

{

  soma::DirectoryParser directory( fileName );
  std::string selectedFile = directory.getSelectedFile();

  if ( !selectedFile.empty() )
  {

    return soma::DicomReaderFactory::getInstance().check( _datasetModule,
                                                          directory, 
                                                          dataInfo,
                                                          datasetHeader );

  }

  return false;

}


bool soma::DicomIO::getHeader( soma::HeaderProxy& header, 
                               soma::DataInfo& dataInfo,
                               soma::DicomDatasetHeader& datasetHeader )
{

  return soma::DicomReaderFactory::getInstance().getHeader( _datasetModule, 
                                                            header,
                                                            dataInfo,
                                                            datasetHeader );

}


bool soma::DicomIO::read( soma::DicomDatasetHeader& datasetHeader, 
                          soma::DicomProxy& proxy )
{

  return soma::DicomReaderFactory::getInstance().read( _datasetModule,
                                                       datasetHeader, 
                                                       proxy );

}


bool soma::DicomIO::checkDicom( const std::string& fileName )
{

  if ( !fileName.empty() )
  {

    std::ifstream ifs( fileName.c_str(), std::ifstream::binary );

    if ( ifs.good() )
    {

      int32_t length = 0;
      uint8_t dcmTest[] = { 0x44, 0x49, 0x43, 0x4D };
      uint8_t value[] = { 0, 0, 0, 0 };
      int32_t* dcmTestInt = (int32_t*)dcmTest;
      int32_t* valueInt = (int32_t*)value;

      ifs.seekg( 0, ifs.end );

      length = ifs.tellg();

      if ( length > 132 )
      {

        ifs.seekg( 128, ifs.beg );
        ifs.read( (char*)value, 4 );

      }

      ifs.close();

      if ( *dcmTestInt == *valueInt )
      {

        return true;

      }

    }

  }

  return false;

}
