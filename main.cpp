/*******************************************************************************
 * Tiny Fasta/Fastq Line Filter
 *   Filter seqs in fasta/fastq format by providing a list of wanted seq names
 * File: main.cpp
 *******************************************************************************
 * Author: Guangyu Li
 * Dep. of Civil and Environmental Engeering, Northeastern University
 * 360 Huntington Ave, Boston, MA, 02115, United States
 *******************************************************************************
 * This is a free software under GPL v3 lisence.
 * View LICENSE for more detailed information
 *******************************************************************************
 */

#include <iostream>
#include "argparse.h"
#include "extract.h"


typedef std::vector< ExtractorArgs::task >::iterator task_iter;

int main(const int argc, const char *argv[])
{
	// parse arguments
	ExtractorArgs args;
	try
	{
		args.parse_args(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl << std::endl;
		args.print_help();
		return 255;
	}

	Extractor ex;
	ex.load_ids_from_file(args.id_file);
	// extract based on the parsed src_file->dest_file settings iteratively
	for (std::vector< ExtractorArgs::task >::iterator it = args.task_queue.begin();
		it != args.task_queue.end(); it++)
		ex.extract(it->src_file, it->dest_file);
	return 0;
}
