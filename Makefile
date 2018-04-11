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


.PHONY: build
build: argparse.o extract.o main.o tiny_fastq_extractor

.PHONY: test
test: build
	$(MAKE) test -C testsuite

tiny_fastq_extractor: argparse.o extract.o main.o
	$(CXX) --std=c++11 -static -o tiny_fastq_extractor argparse.o extract.o main.o

main.o: main.cpp argparse.h extract.h string_hash.h kseq.h
	$(CXX) --std=c++11 -c -o main.o main.cpp

extract.o: extract.cpp extract.h string_hash.h kseq.h
	$(CXX) --std=c++11 -c -o extract.o extract.cpp

argparse.o: argparse.cpp argparse.h
	$(CXX) --std=c++11 -c -o argparse.o argparse.cpp

.PHONY: clean
clean:
	-rm -f tiny_fastq_extractor
	-rm -f *.o
	$(MAKE) clean -C testsuite
