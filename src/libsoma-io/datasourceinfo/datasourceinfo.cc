/* This software and supporting documentation are distributed by
 *     Institut Federatif de Recherche 49
 *     CEA/NeuroSpin, Batiment 145,
 *     91191 Gif-sur-Yvette cedex
 *     France
 *
 * This software is governed by the CeCILL-B license under
 * French law and abiding by the rules of distribution of free software.
 * You can  use, modify and/or redistribute the software under the
 * terms of the CeCILL-B license as circulated by CEA, CNRS
 * and INRIA at the following URL "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

//--- soma io ----------------------------------------------------------------
#include <soma-io/config/soma_config.h>
#include <soma-io/datasourceinfo/datasourceinfo.h>        // class declaration
#include <soma-io/datasourceinfo/datasourcecapabilities.h>           // member
#include <soma-io/datasource/datasourcelist.h>                       // member
#include <soma-io/datasource/datasource.h>           // constructor's argument
#include <soma-io/datasource/filedatasource.h> // used with string constructor
//--- cartobase --------------------------------------------------------------
#include <cartobase/object/object.h>                                 // member
#include <cartobase/object/property.h>          // to manage header properties
#include <cartobase/smart/rcptr.h>                      // used by constructor
//--- system -----------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------

using namespace soma;
using namespace carto;
using namespace std;

//============================================================================
//   C O N S T R U C T O R S
//============================================================================
DataSourceInfo::DataSourceInfo( const Object & header, 
                                const DataSourceCapabilities & cap,
                                const DataSourceList & dsl )
: _header( header ), _capabilities( cap ), _datasourcelist( dsl ),
  _privateiodata( Object::value( PropertySet() ) )
{
}

DataSourceInfo::DataSourceInfo( const rc_ptr<DataSource> & ds,
                                const std::vector<int> & dim )
: _header( none() ), _capabilities(), _datasourcelist( ds ),
  _privateiodata( Object::value( PropertySet() ) )
{
  if( !dim.empty() ) {
    _header = Object::value( PropertySet() );
    _header->setProperty( "sizeX", dim[ 0 ] );
    _header->setProperty( "sizeY", dim[ 1 ] );
    _header->setProperty( "sizeZ", dim[ 2 ] );
    _header->setProperty( "sizeT", dim[ 3 ] );
  }
}

DataSourceInfo::DataSourceInfo( const rc_ptr<DataSource> & ds, 
                                Object header )
: _header( header ), _capabilities(), _datasourcelist( ds ),
  _privateiodata( Object::value( PropertySet() ) )
{
}

DataSourceInfo::DataSourceInfo( const DataSourceInfo & other )
: _header( other._header ), 
  _capabilities( other._capabilities ), 
  _datasourcelist( other._datasourcelist ),
  _privateiodata( other._privateiodata ),
  _identifiedFormat( other._identifiedFormat )
{
}

DataSourceInfo::DataSourceInfo( const string & fname )
: _header( none() ), _capabilities(),
  _datasourcelist( carto::rc_ptr<DataSource>( new FileDataSource( fname ) ) ),
  _privateiodata( Object::value( PropertySet() ) )
{
}

DataSourceInfo::~DataSourceInfo()
{
}

//============================================================================
//   A C C E S S   T O   M E M B E R S
//============================================================================

// already defined in header
