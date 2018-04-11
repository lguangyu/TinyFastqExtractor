Tiny Fastq/Fasta Sequence Extract Program
=========================================

Synopsis
--------

Extract unique seqs in a FASTQ/FASTA file by a list of interested id's.

Prerequisites
-------------

g++ (compatible with C++11 standard)

Build
-----

To build and install the executables, simply do:

```
$make
$cp tiny_fastq_extractor path/to/install/directory
```

The build executable is by default statically linked to g++ library for portability.


How to use
----------

```
./tiny_fastq_extractor [-h] -x file -i input1 -o output1 [-i input2 -o output2 ...]

synopsis:
  extract fasta/fastq seqs from the input file according to a extract list
  output file has ONLY unique seqs despite the redundancy in the extracting list

arguments:
  -h, --help   show this help and exit
  -x file      file contains ids to extract; each line is an id (required)
  -i input     input fastq/fasta, must appear in pair with -o (required)
  -o output    output fastq/fasta, must appear in pair with -i (required)
```

Note:

The redundancy in the input extraction list (i.e. same ids appeared more than once) will be ignored.


Example
-------

```
./tiny_fastq_extractor -x ids.list -i input.fastq -o output.fastq
```

or, extract multiple files:

```
./tiny_fastq_extractor -x ids.list -i input.1.fastq -o output.1.fastq -i input.2.fastq -o output.2.fastq
```
