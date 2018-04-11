#*******************************************************************************
# Tiny Fasta/Fastq Line Filter
#   Filter seqs in fasta/fastq format by providing a list of wanted seq names
# File: testsuite/Makefile
#*******************************************************************************
# Author: Guangyu Li
# Dep. of Civil and Environmental Engeering, Northeastern University
# 360 Huntington Ave, Boston, MA, 02115, United States
#*******************************************************************************
# This is a free software under GPL v3 lisence.
# View LICENSE for more detailed information
#*******************************************************************************

LGTEST = -lgtest -lgtest_main
TEST_FLAG = -D_TEST

.PHONY: build
build: argparse.test argparse.interactive.test extract.test

.PHONY: test
test: build
	./argparse.test
	./extract.test data/fastq.ex.txt
	./extract.test data/fasta.ex.txt


################################################################################
# argparse.test
################################################################################
# regular test cases for argparse using gtest
argparse.test: argparse.test.o ../argparse.o
	$(CXX) --std=c++11 -o argparse.test argparse.test.o ../argparse.o $(LGTEST)

argparse.test.o: argparse.test.cpp ../argparse.h
	$(CXX) --std=c++11 $(TEST_FLAG) -c -o argparse.test.o argparse.test.cpp

################################################################################
# argparse.interactive.test
################################################################################
# incase want to test the parser interactively
# this program will only contain the argument parser functional
argparse.interactive.test: argparse.interactive.test.o ../argparse.o
	$(CXX) --std=c++11 -o argparse.interactive.test argparse.interactive.test.o ../argparse.o

argparse.interactive.test.o: argparse.test.cpp ../argparse.h
	$(CXX) --std=c++11 $(TEST_FLAG) -c -DINTERACTIVE_TEST -o argparse.interactive.test.o argparse.test.cpp

################################################################################
# extract.test
################################################################################
# regular test cases for argparse using gtest
extract.test: extract.test.o ../extract.o
	$(CXX) --std=c++11 -o extract.test extract.test.o ../extract.o $(LGTEST)

extract.test.o: extract.test.cpp ../extract.h  ../string_hash.h ../kseq.h
	$(CXX) --std=c++11 $(TEST_FLAG) -c -o extract.test.o extract.test.cpp


.PHONY: clean
clean:
	-rm -f *.test
	-rm -f *.test.o
