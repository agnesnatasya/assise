#include <stdio.h>

#include "kernfs_interface.h"
#include <leveldb/c.h>

int main(void)
{
	printf("initialize file system\n");

	init_fs();

	shutdown_fs();
}
