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
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "omp_adapter.h"

typedef uint64_t hash_t;

#include "dbs.h"
#include "hash.h"
#include "config_sam_filter.h"
#include "seq_transform.h"
#include "p_string.h"

using namespace std;

struct SamReader
{
    std::istream *f = nullptr;
    SamReader()
    {
        f = &std::cin;
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    bool readline(string &line)
    {
        std::getline(*f, line);
        // handling windows line endings
        if (!line.empty() && *line.rbegin() == '\r')
            line.erase(line.size() - 1);

        return (!f->eof());
    }
};

struct Filter
{
    typedef std::vector<hash_t> HashSortedArray;

	HashSortedArray hash_array;
    int kmer_len = 0;

    Filter(const string &db)
    {
	    kmer_len = DBSIO::load_dbs(db, hash_array);
    }

    bool in_db(hash_t hash)
    {
        hash = seq_transform<hash_t>::min_hash_variant(hash, kmer_len);
    	return std::binary_search(hash_array.begin(), hash_array.end(), hash);
    }

    bool fine_seq(const p_string seq)
    {
        bool found = false;
    	Hash<hash_t>::for_all_hashes_do(seq, kmer_len, [&](hash_t hash)
    	{
	        if (in_db(hash) > 0)
    		    found = true;
                return !found;
    	});

        return !found;
    }
};

// from 1th. returns line.length() if not found
int find_nth(const string &line, int from, int n, char ch)
{
    if (n <= 0)
        return int(line.length());

    for (int i = from; i < int(line.length()); i++)
        if (line[i] == ch)
        {
            n--;
            if (n == 0)
                return i;
        }
     
    return int(line.length());
}

p_string find_sam_nucleotide_seq(const std::string &sam_line)
{
    const int SAM_SEQ_COLUMN = 9;

    auto begin_pos = 1 + find_nth(sam_line, 0, SAM_SEQ_COLUMN, '\t'); // starts from 1th
    if (begin_pos >= sam_line.length())
        return p_string();

    auto end_pos = find_nth(sam_line, begin_pos, 1, '\t'); // returns sam_line.length() if not found

    return p_string(&sam_line[begin_pos], end_pos - begin_pos);
}

// limitations: accepts ACTG only, upper case, no N or other charachters
int main(int argc, char const *argv[])
{
	Config config(argc, argv);

    Filter filter(config.db);

    SamReader reader;

    std::ofstream filtered_file;
    if (!config.filtered_file.empty())
        filtered_file.open(config.filtered_file);

    string sam_line, local_copy_sam_line;
    while (reader.readline(sam_line))
    {
        local_copy_sam_line = sam_line; // overall can be optimized and removed
        if (filter.fine_seq(seq_transform_actg::to_upper_inplace(find_sam_nucleotide_seq(local_copy_sam_line))))
            cout << sam_line << endl;
        else
            if (filtered_file.good())
                filtered_file << sam_line << endl;
    }
}