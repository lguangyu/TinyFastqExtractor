#*******************************************************************************
# Tiny Fasta/Fastq Line Filter
#   Filter seqs in fasta/fastq format by providing a list of wanted seq names
# File: Makefile
#*******************************************************************************
# Author: Guangyu Li
# Dep. of Civil and Environmental Engeering, Northeastern University
# 360 Huntington Ave, Boston, MA, 02115, United States
#*******************************************************************************
# This is a free software under GPL v3 lisence.
# View LICENSE for more detailed information
#*******************************************************************************

LBOOST_PROGOPT = -lboost_program_options

.PHONY: build
build: tiny_fastq_extractor

.PHONY: test
test: tiny_fastq_extractor
	./tiny_fastq_extractor -x test/fasta.ex.txt test/test.fasta
	./tiny_fastq_extractor -x test/fastq.ex.txt test/test.fastq

tiny_fastq_extractor: extract.o main.o
	$(CXX) -o tiny_fastq_extractor extract.o main.o $(LBOOST_PROGOPT)

extract.o: extract.cpp extract.h kseq.h
	$(CXX) -c -o extract.o extract.cpp

main.o: main.cpp extract.h kseq.h
	$(CXX) -c -o main.o main.cpp

.PHONY: clean
clean:
	-rm -f tiny_fastq_extractor
	-rm -f *.o
