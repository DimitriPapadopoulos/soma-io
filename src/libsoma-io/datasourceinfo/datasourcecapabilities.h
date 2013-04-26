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

#ifndef SOMAIO_DATASOURCEINFO_DATASOURCECAPABILITIES_H
#define SOMAIO_DATASOURCEINFO_DATASOURCECAPABILITIES_H

namespace soma
{
  /**
   * Reading/Writing Capabilities of a FormatReader
   * 
   * This object is constructed by the FormatChecker after reading the header.
   * It allows one to give informations about the possible ways to read a volume
   * ( partial reading ... ).
   *
   * \remarks Since capabilities may be file-dependant (and not just format-
   * dependant, think of compressed data), they need being stored in the
   * class. However, the current implementation uses \em hard booleans, which
   * make the object pretty heavy (7 bytes). Maybe is there a better way to do 
   * this ?
   */
  class DataSourceCapabilities
  {
    public:
      DataSourceCapabilities();
      DataSourceCapabilities( const DataSourceCapabilities & );
      virtual ~DataSourceCapabilities();
      
      bool  allowsMemoryMapping() const;
      bool  isThreadSafe()        const;
      bool  isOrdered()           const;
      bool  canSeekVoxel()  const;
      bool  canSeekLine()   const;
      bool  canSeekSlice()  const;
      bool  canSeekVolume() const;
      
      void  setMemoryMapping  ( const bool & );
      void  setThreadSafe     ( const bool & );
      void  setOrdered        ( const bool & );
      void  setSeekVoxel      ( const bool & );
      void  setSeekLine       ( const bool & );
      void  setSeekSlice      ( const bool & );
      void  setSeekVolume     ( const bool & );
      
    protected:
      /**
       * From LSB to MSB :
       *  - allows_memory_mapping
       *  - is_thread_safe
       *  - is_ordered
       *  - seek_voxel
       *  - seek_line
       *  - seek_slice
       *  - seek_volume
       *  - *unused*
       */
      unsigned char _capabilities;  // default: [00000000]
  };
  
}

#endif