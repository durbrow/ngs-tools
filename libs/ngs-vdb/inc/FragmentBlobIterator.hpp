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

#ifndef _hpp_FragmentBlobIterator_hpp_
#define _hpp_FragmentBlobIterator_hpp_

#include <ngs-vdb/inc/FragmentBlob.hpp>

typedef struct NGS_FragmentBlobIterator* FragmentBlobIteratorRef;

namespace ncbi
{
    namespace ngs
    {
        namespace vdb
        {

            class FragmentBlobIterator
            {
            public:

                bool hasMore() const;

                FragmentBlob nextBlob();

            public:

                // C++ support

                FragmentBlobIterator ( FragmentBlobIteratorRef ref )
                    NGS_NOTHROW();

                FragmentBlobIterator & operator = ( const FragmentBlobIterator & obj );
                FragmentBlobIterator ( const FragmentBlobIterator & obj );

                ~ FragmentBlobIterator ()
                    NGS_NOTHROW();

            private:
                FragmentBlobIterator () throw ();

                FragmentBlobIteratorRef self;
            };
        }
    }
} // ncbi

#endif
