#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <memory>
#include <fstream>


void show_usage(const char *prog)
{
	std::cerr << "usage: " << prog
		<< "<num_of_files> <create/not>"
        << std::endl;
}


int main(int argc, char *argv[])
{
    clock_t begin = clock();

    auto wcts = std::chrono::system_clock::now();

    const char *test_dir_prefix_1 = "/mlfs";
    const char *test_dir_prefix_2 = "/ap";

    char *test_file_name = "file1";

    std::string test_file;

    int fd;

    if(argc != 2)
        show_usage("create_files");

    int count = atoi(argv[1]);
               clock_t begin_m = clock();
    int is_c = atoi(argv[2]);
    
    mkdir(test_dir_prefix_1, 0777);
    int ret = mkdir(test_dir_prefix, 0777);
    clock_t end_m = clock();
    for(int i=1; i<count+1; i++) {
	    clock_t begin_s = clock();

	    test_file.assign(test_dir_prefix);

	    test_file += std::string(test_file_name) + std::to_string(5) + "-" + std::to_string(i);
        
        if (!is_c) {
            fd = open(test_file.c_str(), O_RDWR,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        } else {
            fd = open(test_file.c_str(), O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }

        if (fd < 0) {
                err(1, "open");
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin)  * 1000.0 / CLOCKS_PER_SEC;
    std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);
    printf("CPU Time: %.3f\n", time_spent);
    printf("Wall time %.3f ms\n", wctduration.count()*1000);
    return 0;
}
