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
#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdexcept>


#define READ_FUNC(fh, buffer_ptr, buffer_size) (fread(buffer_ptr, sizeof(char), buffer_size, fh))
KSEQ_INIT(FILE*, READ_FUNC);


void Extractor::load_ids_from_file(const char *file)
{
	// initialize, erase former results
	unsigned num_ids = 0;
	loaded_ids.empty();
	// load new ids
	std::ifstream id_ifs(file);
	std::string line;
	while (std::getline(id_ifs, line))
		if (line.size())
		{
			loaded_ids.emplace(line, true);
			num_ids++;
		}
	std::cerr << loaded_ids.size() << " unique ids loaded from '" << file << "'" << std::endl;
	std::cerr << "(total  " << num_ids << " including redundants)" << std::endl;
}

/*==============================================================================
 * write kseq object to an file stream (FILE from standard c lib)
 * locally defined function
 *==============================================================================
 */
void write_kseq(FILE *file, kseq_t *kseq)
{
	if (kseq->qual.l)
	{
		// write as fastq
		if (kseq->comment.l)
			fprintf(file, "@%s %s\n", kseq->name.s, kseq->comment.s);
		else
			fprintf(file, "@%s\n", kseq->name.s);
		fprintf(file, "%s\n", kseq->seq.s);
		fprintf(file, "+\n%s\n", kseq->qual.s);
	}
	else
	{
		// write as fasta
		if (kseq->comment.l)
			fprintf(file, ">%s %s\n", kseq->name.s, kseq->comment.s);
		else
			fprintf(file, ">%s\n", kseq->name.s);
		fprintf(file, "%s\n", kseq->seq.s);
	}
}

void Extractor::extract(const char *src_file, const char *dest_file)
{
	// initialize, erase former results
	unsigned num_extracted = 0;
	unsigned num_total_seqs = 0;
	// open file handler
	FILE *ifp = NULL, *ofp = NULL;
	if (!(ifp = fopen(src_file, "r")))
		throw std::runtime_error(std::string(src_file) + "does not exist");
	if (!(ofp = fopen(dest_file, "w")))
		throw std::runtime_error(std::string(dest_file) + "failed to open");
	// kseq init
	kseq_t *kseq = kseq_init(ifp);
	// extract
	while (kseq_read(kseq) >= 0)
	{
		num_total_seqs++;
		if (loaded_ids.find(kseq->name.s) != loaded_ids.end())
		{
			write_kseq(ofp, kseq);
			num_extracted++;
		}
	}
	// release resources
	fclose(ifp); ifp = NULL;
	fclose(ofp); ofp = NULL;
	kseq_destroy(kseq); kseq = NULL;

	std::cerr << num_extracted << " seqs extracted from '" << src_file << "'(" << num_total_seqs << " seqs total)" << std::endl;
}
