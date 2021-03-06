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
#include "string_hash.h"
#include "kseq.h"


class Extractor
{
public:
	typedef StringHash hash;

public:
	/*==========================================================================
	 * these functions are used only for test purposes, and must use -D_TEST
	 * flag to actually compile them
	 * on other situations these functions are not recommended to be enabled
	 */
	#ifdef _TEST
	/*==========================================================================
	 * return the reference of loaded_ids member (hash)
	 */
	Extractor::hash& test_get_loaded_ids(void)
	{
		return loaded_ids;
	}
	#endif /* _TEST */

	/*==========================================================================
	 * load ids (def-line of fasta/fastq) from a file
	 *==========================================================================
	 * argument:
	 *   file: file name
	 * return:
	 *   no return values
	 */
	void load_ids_from_file(const char *file);

	/*==========================================================================
	 * extract seqs from src_file with loaded ids to dest_file
	 *==========================================================================
	 * argument:
	 *   src_file: source file name
	 *   dest_file: destination file name
	 * return:
	 *   no return values
	 */
	void extract(const char *src_file, const char *dest_file);

private:
	Extractor::hash loaded_ids;
};

#endif /* __EXTRACT_H__ */
