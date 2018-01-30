/*******************************************************************************
 * Tiny Fasta/Fastq Line Filter
 *   Filter seqs in fasta/fastq format by providing a list of wanted seq names
 * File: extract.cpp
 *******************************************************************************
 * Author: Guangyu Li
 * Dep. of Civil and Environmental Engeering, Northeastern University
 * 360 Huntington Ave, Boston, MA, 02115, United States
 *******************************************************************************
 * This is a free software under GPL v3 lisence.
 * View LICENSE for more detailed information
 *******************************************************************************
 */

#include "extract.h"


void extract::load_id_list(std::istream &ifs,
	boost::unordered_map<std::string, bool> &ids_hash)
{
	std::string line;
	while((!ifs.eof()) && std::getline(ifs, line))
	{
		if (line.length())
		{
			// trim eol
			if (line[line.length() - 1] == '\n')
				line.erase(line.length());
			ids_hash[line] = true;
		}
	}
}

void extract::extract_seqs(FILE *seqs_fp,
	const boost::unordered_map<std::string, bool> &ids_hash,
	std::ostream &output)
{
	kseq_t *kseq_worker;
	kseq_worker = kseq_init(seqs_fp);
	unsigned _tot = 0, _ex = 0;
	while (kseq_read(kseq_worker) >= 0)
	{
		_tot++;
		if (ids_hash.find(std::string(kseq_worker->name.s)) != ids_hash.end())
		{
			_ex++;
			if (kseq_worker->qual.l)
			{ // fastq format with quality data
				output << "@" << kseq_worker->name.s << std::endl;
				output << kseq_worker->seq.s << std::endl;
				output << "+" << std::endl;
				output << kseq_worker->qual.s << std::endl;
			}
			else
			{ // fasta format
				output << ">" << kseq_worker->name.s << std::endl;
				output << kseq_worker->seq.s << std::endl;
			}
		}
	}
	std::cerr << _ex << " reads extracted out of " << _tot << std::endl;
	kseq_destroy(kseq_worker);
}
