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

//--- soma io ------------------------------------------------------------------
#include <soma-io/datasourceinfo/datasourcecapabilities.h>  // class declaration
//------------------------------------------------------------------------------

using namespace soma;
using namespace std;

//==============================================================================
//   C O N S T R U C T O R S
//==============================================================================

DataSourceCapabilities::DataSourceCapabilities() : _capabilities( 0 )
{
}

DataSourceCapabilities::DataSourceCapabilities( const DataSourceCapabilities 
                                                & other ) :
  _capabilities( other._capabilities )
{
}

DataSourceCapabilities::~DataSourceCapabilities()
{
}

//==============================================================================
//   A C C E S S O R S
//==============================================================================

bool DataSourceCapabilities::allowsMemoryMapping() const
{
  return _capabilities & 1;
}

bool DataSourceCapabilities::isThreadSafe() const
{
  return _capabilities & 2;
}

bool DataSourceCapabilities::isOrdered() const
{
  return _capabilities & 4;
}

bool DataSourceCapabilities::canSeekVoxel() const
{
  return _capabilities & 8;
}

bool DataSourceCapabilities::canSeekLine() const
{
  return _capabilities & 16;
}

bool DataSourceCapabilities::canSeekSlice() const
{
  return _capabilities & 32;
}

bool DataSourceCapabilities::canSeekVolume() const
{
  return _capabilities & 64;
}

//==============================================================================
//   M U T A T O R S
//==============================================================================

void DataSourceCapabilities::setMemoryMapping( const bool & val )
{
  _capabilities = _capabilities | 1;
}

void DataSourceCapabilities::setThreadSafe( const bool & val )
{
  _capabilities = _capabilities | 2;
}

void DataSourceCapabilities::setOrdered( const bool & val )
{
  _capabilities = _capabilities | 4;
}

void DataSourceCapabilities::setSeekVoxel( const bool & val )
{
  _capabilities = _capabilities | 8;
}

void DataSourceCapabilities::setSeekLine( const bool & val )
{
  _capabilities = _capabilities | 16;
}

void DataSourceCapabilities::setSeekSlice( const bool & val )
{
  _capabilities = _capabilities | 32;
}

void DataSourceCapabilities::setSeekVolume( const bool & val )
{
  _capabilities = _capabilities | 64;
}