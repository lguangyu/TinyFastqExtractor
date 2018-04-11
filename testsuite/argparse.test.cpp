#include "../argparse.h"


// define INTERACTIVE_TEST to run as a sole interactive command-line parser
// otherwise, use google test
#ifndef INTERACTIVE_TEST

#include <gtest/gtest.h>

TEST(argparse, fail_cases)
{
	int _argc = 0;
	const char *_argv[10] = {"", "", "", "", "", "", "", "", "", ""};

	{
		// should fail for no arguments passed
		_argc = 1;
		_argv[0] = "program";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no argument passed to -x
		_argc = 2;
		_argv[1] = "-x";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no argument passed to -x
		_argc = 3;
		_argv[2] = "-i";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no -i/-o set
		_argc = 3;
		_argv[2] = "extract.file";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for excessive -x
		_argc = 5;
		_argv[3] = "-x";
		_argv[4] = "another.extract.file";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no argument passed to -i
		_argc = 4;
		_argv[3] = "-i";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no argument passed to -i
		_argc = 5;
		_argv[4] = "-i";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no argument passed to -o
		_argc = 4;
		_argv[3] = "-o";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no argument passed to -o
		_argc = 5;
		_argv[4] = "-o";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no input/output not match
		_argc = 5;
		_argv[3] = "-i";
		_argv[4] = "input.file";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no input/output not match
		_argc = 5;
		_argv[3] = "-o";
		_argv[4] = "output.file";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
	{
		// should fail for no -x set (input and output are ok)
		_argc = 5;
		_argv[1] = "-i";
		_argv[2] = "input.file";
		_argv[3] = "-o";
		_argv[4] = "output.file";
		ExtractorArgs args;
		EXPECT_THROW(args.parse_args(_argc, _argv), std::invalid_argument);
	}
};


TEST(argparse, good_cases)
{
	int _argc = 0;
	const char *_argv[11] = {"", "", "", "", "", "", "", "", "", "", ""};

	{
		// good parse
		_argc = 7;
		_argv[0] = "program";
		_argv[1] = "-x";
		_argv[2] = "extract.file";
		_argv[3] = "-i";
		_argv[4] = "input.1.file";
		_argv[5] = "-o";
		_argv[6] = "output.1.file";
		ExtractorArgs args;
		EXPECT_NO_THROW(args.parse_args(_argc, _argv));
		ASSERT_STREQ(args.id_file, "extract.file");
		ASSERT_STREQ(args.task_queue[0].src_file, "input.1.file");
		ASSERT_STREQ(args.task_queue[0].dest_file, "output.1.file");
	}
	{
		// the same thing as above, but with shuffled order
		_argc = 7;
		_argv[0] = "program";
		_argv[1] = "-o";
		_argv[2] = "output.1.file";
		_argv[3] = "-i";
		_argv[4] = "input.1.file";
		_argv[5] = "-x";
		_argv[6] = "extract.file";
		ExtractorArgs args;
		EXPECT_NO_THROW(args.parse_args(_argc, _argv));
		ASSERT_STREQ(args.id_file, "extract.file");
		ASSERT_STREQ(args.task_queue[0].src_file, "input.1.file");
		ASSERT_STREQ(args.task_queue[0].dest_file, "output.1.file");
	}
	{
		// with more pairs of input/output
		_argc = 11;
		_argv[0] = "program";
		_argv[1] = "-x";
		_argv[2] = "extract.file";
		_argv[3] = "-i";
		_argv[4] = "input.1.file";
		_argv[5] = "-o";
		_argv[6] = "output.1.file";
		_argv[7] = "-i";
		_argv[8] = "input.2.file";
		_argv[9] = "-o";
		_argv[10] = "output.2.file";
		ExtractorArgs args;
		EXPECT_NO_THROW(args.parse_args(_argc, _argv));
		ASSERT_STREQ(args.id_file, "extract.file");
		ASSERT_STREQ(args.task_queue[0].src_file, "input.1.file");
		ASSERT_STREQ(args.task_queue[0].dest_file, "output.1.file");
		ASSERT_STREQ(args.task_queue[1].src_file, "input.2.file");
		ASSERT_STREQ(args.task_queue[1].dest_file, "output.2.file");
	}
	{
		// the same thing as above, but with shuffled order
		_argc = 11;
		_argv[0] = "program";
		_argv[1] = "-o";
		_argv[2] = "output.1.file";
		_argv[3] = "-x";
		_argv[4] = "extract.file";
		_argv[5] = "-o";
		_argv[6] = "output.2.file";
		_argv[7] = "-i";
		_argv[8] = "input.1.file";
		_argv[9] = "-i";
		_argv[10] = "input.2.file";
		ExtractorArgs args;
		EXPECT_NO_THROW(args.parse_args(_argc, _argv));
		ASSERT_STREQ(args.id_file, "extract.file");
		ASSERT_STREQ(args.task_queue[0].src_file, "input.1.file");
		ASSERT_STREQ(args.task_queue[0].dest_file, "output.1.file");
		ASSERT_STREQ(args.task_queue[1].src_file, "input.2.file");
		ASSERT_STREQ(args.task_queue[1].dest_file, "output.2.file");
	}
};


int main(const int argc, const char *argv[])
{
	int _argc = argc;
	::testing::InitGoogleTest(&_argc, (char**)argv);
	return RUN_ALL_TESTS();
}

#else

#include <iostream>

int main(const int argc, const char *argv[])
{
	std::cout << "argument received:" << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;

	ExtractorArgs args;
	try
	{
		args.parse_args(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
		args.print_help();
		return 0;
	}

	std::cout << "extract from: " << args.id_file << std::endl;
	for (std::vector< ExtractorArgs::task >::iterator it = args.task_queue.begin();
		it != args.task_queue.end(); it++)
		std::cout << "input: " << it->src_file << "; output: " << it->dest_file << std::endl;
	return 0;
}

#endif /* INTERACTIVE_TEST */
