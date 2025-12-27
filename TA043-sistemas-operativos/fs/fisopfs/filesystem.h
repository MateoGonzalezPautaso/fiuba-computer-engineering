#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_PATH 100
#define MAX_INODES 1024
#define BLOCK_SIZE 4096  // 4KB

typedef enum file_type { REGULAR_FILE, DIRECTORY } file_type_t;

typedef struct inode {
	file_type_t file_type;
	char path[MAX_PATH];
	char data[BLOCK_SIZE];

	ino_t ino;      // Inode number
	nlink_t nlink;  // Hardlink count
	mode_t mode;    // Mode

	uid_t uid;   // User ID
	gid_t gid;   // Group ID
	off_t size;  // Total size, in bytes

	time_t atime;  // Last access
	time_t mtime;  // Last modification
	time_t ctime;  // Last status change
} inode_t;

typedef struct filesystem {
	inode_t inodes[MAX_INODES];
	bool inode_bitmap[MAX_INODES];  // true = ocupado - false = libre
	int32_t used_inodes;
} filesystem_t;


#endif