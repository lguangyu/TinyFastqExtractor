#include "../extract.h"
#include <iostream>

int main(const int argc, const char *argv[])
{
	if (argc > 1)
	{
		Extractor ex;
		ex.load_ids_from_file(argv[1]);
		// this line requires -D_TEST enabled
		Extractor::hash& loaded_ids = ex.test_get_loaded_ids();
		//
		for (Extractor::hash::iterator it = loaded_ids.begin();
			it != loaded_ids.end(); it++)
			std::cout << it->first << "\t" << it->second << std::endl;
	}
	return 0;
}
