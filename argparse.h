/*******************************************************************************
 * Tiny Fasta/Fastq Line Filter
 *   Filter seqs in fasta/fastq format by providing a list of wanted seq names
 * File: argparse.h
 *******************************************************************************
 * Author: Guangyu Li
 * Dep. of Civil and Environmental Engeering, Northeastern University
 * 360 Huntington Ave, Boston, MA, 02115, United States
 *******************************************************************************
 * This is a free software under GPL v3 lisence.
 * View LICENSE for more detailed information
 *******************************************************************************
 */

#ifndef __ARGPARSE_H__
#define __ARGPARSE_H__

#include <cstdlib>
#include <vector>
#include <stdexcept>


class ExtractorArgs
{
public:
	struct task
	{
		const char *src_file;
		const char *dest_file;
	};

public:
	ExtractorArgs(void)
	:	id_file(NULL)
	{}

	const char *id_file;
	std::vector < ExtractorArgs::task > task_queue;

	/*==========================================================================
	 * parse args and store into local member variables
	 *==========================================================================
	 * argument:
	 *   argc: same as argc
	 *   argv: same as argv
	 * return:
	 *   no return values
	 * exception:
	 *   throw std::invalid_argument if parse failed
	 */
	void parse_args(const int argc, const char *argv[]);

	/*==========================================================================
	 * print help
	 *==========================================================================
	 * argument:
	 *   no args
	 * return:
	 *   no return values
	 */
	void print_help(void);
};

#endif /* __ARGPARSE_H__ */
