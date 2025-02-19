/*===========================================================================
*
*                            PUBLIC DOMAIN NOTICE
*               National Center for Biotechnology Information
*
*  This software/database is a "United States Government Work" under the
*  terms of the United States Copyright Act.  It was written as part of
*  the author's official duties as a United States Government employee and
*  thus cannot be copyrighted.  This software/database is freely available
*  to the public for use. The National Library of Medicine and the U.S.
*  Government have not placed any restriction on its use or reproduction.
*
*  Although all reasonable efforts have been taken to ensure the accuracy
*  and reliability of the software and data, the NLM and the U.S.
*  Government do not and cannot warrant the performance or results that
*  may be obtained by using this software or data. The NLM and the U.S.
*  Government disclaim all warranties, express or implied, including
*  warranties of performance, merchantability or fitness for any particular
*  purpose.
*
*  Please cite the author in any work or product based on this material.
*
* ===========================================================================
*
*/

#ifndef _hpp_ngs_tools_NGS_VDB_
#define _hpp_ngs_tools_NGS_VDB_

#ifndef _hpp_ngs_ncbi_NGS_
#include <ngs/ncbi/NGS.hpp>
#endif

#include <ngs-vdb/inc/VdbReadCollection.hpp>

/*==========================================================================
 * NCBI-specific interface to NGS Engine
 *  this class adds NCBI-specific functionality to the NCBI's implementation of the NGS interface
 *  all of the code operates natively on SRA files
 */
namespace ncbi
{
    namespace ngs
    {
        namespace vdb
        {
            class NGS_VDB
            {
            public:
                /* openVdbReadCollection
                *  create an object representing a named collection of reads
                *  with NCBI-specific functionality added
                *  "spec" may be a path to an object
                *  or may be an id, accession, or URL
                */
                static
                VdbReadCollection openVdbReadCollection ( const ncbi :: String & spec );
            };
        };
    }

} // ncbi

#endif
