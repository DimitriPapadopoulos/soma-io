#ifndef _PhilipsNuclearModule_h_
#define _PhilipsNuclearModule_h_


#ifdef SOMA_IO_DICOM
#include <soma-io/config/soma_config.h>
#include <soma-io/Dicom/NuclearModule.h>
#else
#include <Dicom/NuclearModule.h>
#endif


namespace soma
{


class PhilipsNuclearModule : public NuclearModule
{

  public:

    PhilipsNuclearModule();

    bool parseDataset( DcmDataset* dataset );

};


}


#endif

