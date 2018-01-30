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

#include <boost/program_options.hpp>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include "extract.h"


namespace popt = boost::program_options;
namespace config
{
	static const char *synopsis = "Synopsis\n\
  Extract seqs in Fasta/Fastq by a given list of interested definition lines.\n\n\
Usage:\n  ";
	static const char *options = " [-h][-v][-o <FILE>] -x <FILE> input\n\nOptions";
	static const char *opt_help = "show this message and exit";
	static const char *opt_input = "fasta/fastq input FILE";
	static const char *opt_extract = "definition lines to extract; each line is an interested seq";
	static const char *opt_output = "FILE to write the output (default stdout)";
	static const char *err_arg_missing = "required argument missing: ";
	static const char *err_cant_open_file = "cannot open file: ";
};


// parse options
popt::variables_map parse_potions(int, char **);
// check the required argument is passed or throw an exception
void _check_required_arg(const popt::variables_map&, const std::string&,
						const popt::options_description&);

#define _OPEN_FILE_FAIL_EXIT(path) \
{ \
	std::cerr << config::err_cant_open_file << path << std::endl; \
	exit(1); \
}


void _check_required_arg(const popt::variables_map &vmap, const char *opt,
						const popt::options_description &op_desc)
{
	if (vmap.count(opt))
		return;
	std::cerr << config::err_arg_missing << opt << std::endl;
	std::cerr << op_desc << std::endl;
	exit(1);
}


int main(int argc, char *argv[])
{
	popt::variables_map vmap = parse_potions(argc, argv);
	const std::string &_extract  = vmap["extract"].as< std::string >();
	const std::string &_input    = vmap["input"  ].as< std::string >();

	// load ids from list file
	boost::unordered_map< std::string, bool > ids_hash;
	std::ifstream ids_ifs(_extract.c_str());
	if (!ids_ifs.is_open())
		_OPEN_FILE_FAIL_EXIT(_extract);
	extract::load_id_list(ids_ifs, ids_hash);
	ids_ifs.close();

	// extract seqs
	FILE *seqs_fp = fopen(_input.c_str(), "r");
	if (!seqs_fp)
		_OPEN_FILE_FAIL_EXIT(_input);
	if (vmap.count("output"))
	{ // if output is defined using output, otherwise cout
		const std::string &_output = vmap["output"].as< std::string >();
		std::ofstream ex_ofs(_output.c_str());
		if (!ex_ofs.is_open())
			_OPEN_FILE_FAIL_EXIT(_output);
		extract::extract_seqs(seqs_fp, ids_hash, ex_ofs);
		ex_ofs.close();
	}
	else
		extract::extract_seqs(seqs_fp, ids_hash, std::cout);
	fclose(seqs_fp); seqs_fp = NULL;
	return 0;
}

popt::variables_map parse_potions(int argc, char *argv[])
{
	popt::options_description op_desc(std::string(config::synopsis) + *argv + config::options);
	// add options
	op_desc.add_options()
		("help,h",    config::opt_help)
		("input,i",   popt::value< std::string >(), config::opt_input)
		("extract,x", popt::value< std::string >(), config::opt_extract)
		("output,o",  popt::value< std::string >(), config::opt_output);
	// positional argument 'input'
	popt::positional_options_description op_pos_desc;
	op_pos_desc.add("input", -1);
	// parse options
	popt::variables_map vmap;
	popt::store(popt::command_line_parser(argc, argv).\
				options(op_desc).positional(op_pos_desc).run(), vmap);
	popt::notify(vmap);
	// check arguments
	if (vmap.count("help"))
	{
		std::cerr << op_desc << std::endl;
		exit(0);
	}
	_check_required_arg(vmap, "input", op_desc);
	_check_required_arg(vmap, "extract", op_desc);
	return vmap;
}
