/*******************************************************************************
 * Tiny Fasta/Fastq Line Filter
 *   Filter seqs in fasta/fastq format by providing a list of wanted seq names
 * File: extract.h
 *******************************************************************************
 * Author: Guangyu Li
 * Dep. of Civil and Environmental Engeering, Northeastern University
 * 360 Huntington Ave, Boston, MA, 02115, United States
 *******************************************************************************
 * This is a free software under GPL v3 lisence.
 * View LICENSE for more detailed information
 *******************************************************************************
 */

#ifndef __EXTRACT_H__
#define __EXTRACT_H__

#include <string>
#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include "kseq.h"


#define READ_FUNC(fh, buffer_ptr, buffer_size) (fread(buffer_ptr, sizeof(char), buffer_size, fh))
KSEQ_INIT(FILE*, READ_FUNC);

namespace extract
{
	// load wanted ids from istream (a list file)
	void load_id_list(std::istream&, boost::unordered_map<std::string, bool>&);
	// extract seq given a wanted list of ids from a fasta/fastq file, and print
	// extracted seqs to specified ostream
	void extract_seqs(FILE*, const boost::unordered_map<std::string, bool>&, std::ostream&);
};

#endif /* __EXTRACT_H__ */
