#include <stdlib.h>
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
		<< "<num_of_dirs> <num_of_files>"
        << std::endl;
}


int main(int argc, char *argv[])
{  try
  {

    clock_t begin_m;
    clock_t end_m;
    clock_t begin_s;
    clock_t end_s;

    const char *test_dir_prefix = "/mlfs";

    char *file_prefix = "/file";
    char *dir_prefix = "/dir16a";
    srand(time(NULL));
    std::string test_dir;
    std::string test_file;
    
    int fd;

    if(argc != 2)
        show_usage("create_files");

    int count = atoi(argv[1]);
    int files_count = atoi(argv[2]);
    std::string paths[count];
    clock_t begin = clock();
    test_dir.assign(test_dir_prefix);
    for (int j=1; j<count+1;j++) {
        begin_m = clock();
	    test_dir += (std::string(dir_prefix) + std::to_string(j));
        paths[j - 1] = test_dir;
        // printf("Creating dir %s\n", test_dir.c_str());
        mkdir(test_dir.c_str(), 0777);
        end_m = clock();
        // printf("Time elapsed for dir mk %d: %.3f\n", j, (double)(end_m - begin_m)  * 1000.0 / CLOCKS_PER_SEC);
    }
    std::string path;
    for(int i=1; i<files_count + 1; i++) {
        begin_s = clock();
        int index = (rand() % count);
        // printf("index chosen %d\n", index);
        path = paths[index];

	    test_file.assign(std::string(path) + std::string(file_prefix) + std::to_string(i));

      // printf("Creating file %s\n", test_file.c_str());
    	fd = open(test_file.c_str(), O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		
        if (fd < 0) {
                err(1, "open");
        }
        end_s = clock();
        // printf("Time elapsed for file %s: %.3f\n", test_file.c_str(), (double)(end_s - begin_s)  * 1000.0 / CLOCKS_PER_SEC);

    }
    clock_t end = clock();
    double time_spent = (double)(end - begin)  * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed: %.3f\n", time_spent);
      }
  catch (std::bad_alloc& ba)
  {
    std::cerr << "bad_alloc caught: " << ba.what() << '\n';
  }
    return 0;
}
