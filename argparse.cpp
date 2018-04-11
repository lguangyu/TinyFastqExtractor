/*******************************************************************************
 * Tiny Fasta/Fastq Line Filter
 *   Filter seqs in fasta/fastq format by providing a list of wanted seq names
 * File: argparse.cpp
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
#include <cstring>
#include <string>
#include "argparse.h"

namespace argparse_util
{
	bool has_help_option(const int argc, const char *argv[])
	{
		for (int i = 1; i < argc; i++)
		{
			if ((strcmp(argv[i], "-h") == 0) ||
				(strcmp(argv[i], "--help") == 0))
				return true;
		}
		return false;
	}

	bool is_switch(const char *arg)
	{
		return (arg[0] == '-');
	}
};


void ExtractorArgs::print_help(void)
{
	std::cerr << "tiny_fastq_extractor [-h] -x file -i input1 -o output1 [-i input2 -o output2 ...]" << std::endl;
	std::cerr << std::endl;
	std::cerr << "synopsis:" << std::endl;
	std::cerr << "  extract fasta/fastq seqs from the input file according to a extract list" << std::endl;
	std::cerr << "  output file has ONLY unique seqs despite the redundancy in the extracting list" << std::endl;
	std::cerr << std::endl;
	std::cerr << "arguments:" << std::endl;
	std::cerr << "  -h, --help   show this help and exit" << std::endl;
	std::cerr << "  -x file      file contains ids to extract; each line is an id (required)" << std::endl;
	std::cerr << "  -i input     input fastq/fasta, must appear in pair with -o (required)" << std::endl;
	std::cerr << "  -o output    output fastq/fasta, must appear in pair with -i (required)" << std::endl;
}


void ExtractorArgs::parse_args(const int argc, const char *argv[])
{
	// the programs should always respond to -h or --help no matter what
	// weird input of arguments is
	// thus do it first
	if (argparse_util::has_help_option(argc, argv))
	{
		print_help();
		exit(0);
	}

	// parse other options
	// there should be no case of -h or --help at this point
	std::vector< const char* > opt_input;
	std::vector< const char* > opt_output;
	// parse arguments
	for (int i = 1; i < argc; i++)
	{
		if (argparse_util::is_switch(argv[i]))
		{
			switch (argv[i][1])
			{
				case 'x':
					if ((i == argc - 1) || argparse_util::is_switch(argv[i + 1]))
						throw std::invalid_argument("missing argument for '-x'");
					else if (id_file)
						throw std::invalid_argument("redundantly assign to '-x'");
					else
						id_file = argv[i + 1];
						i++;
					break;
				case 'i':
					if ((i == argc - 1) || argparse_util::is_switch(argv[i + 1]))
						throw std::invalid_argument("missing argument for '-i'");
					else
						opt_input.push_back(argv[i + 1]);
						i++;
					break;
				case 'o':
					if ((i == argc - 1) || argparse_util::is_switch(argv[i + 1]))
						throw std::invalid_argument("missing argument for '-o'");
					else
						opt_output.push_back(argv[i + 1]);
						i++;
					break;
				defaut:
					throw std::invalid_argument(std::string("unknown switch: ") + argv[i]);
					break;
			}
		}
		else
			throw std::invalid_argument(std::string("unknown argument: ") + argv[i]);
	}

	// check arguments
	// check if extract ids file is set
	if (!id_file)
		throw std::invalid_argument("'-x' is reuired");

	// check if input/output are equal in number (must be paired up)
	if (opt_input.size() != opt_output.size())
		throw std::invalid_argument("number of input files doesn't match output files");
	// check if input/output are not empty
	else if (!opt_input.size())
		throw std::invalid_argument("missing input files");
	else
		for (int i = 0; i < opt_input.size(); i++)
			task_queue.push_back({opt_input[i], opt_output[i]});
}
