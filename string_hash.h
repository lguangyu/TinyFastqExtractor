/*******************************************************************************
 * Tiny Fasta/Fastq Line Filter
 *   Filter seqs in fasta/fastq format by providing a list of wanted seq names
 * File: string_hash.h
 *******************************************************************************
 * Author: Guangyu Li
 * Dep. of Civil and Environmental Engeering, Northeastern University
 * 360 Huntington Ave, Boston, MA, 02115, United States
 *******************************************************************************
 * This is a free software under GPL v3 lisence.
 * View LICENSE for more detailed information
 *******************************************************************************
 */

#ifndef __STRING_HASH_H__
#define __STRING_HASH_H__

#include <unordered_map>
#include <string>


/*
// BKRD hash algorithm
struct bkrd_hasher
{
	// overload () for interface
	std::size_t operator() (const char *str) const
	{
		std::size_t seed = 131;
		std::size_t hash = 0;
		while (*str)
			hash = hash * seed + (*str++);
		return hash;
	};

	// overload () for std::string input
	std::size_t operator() (const std::string &str) const
	{
		return (*this)(str.c_str());
	}
};
*/

//typedef std::unordered_map< std::string, bool, bkrd_hasher > StringHash;

// use standard template library implementation
typedef std::unordered_map< std::string, bool > StringHash;

#endif /* __STRING_HASH_H__ */
