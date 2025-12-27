#ifndef UTILS_H
#define UTILS_H

#define _POSIX_C_SOURCE 200809L
#include "filesystem.h"
#include <time.h>
#define PATH_ROOT "/"


extern filesystem_t filesystem;

int inode_index_from_path(const char *path);

char *extraer_path_padre(const char *path);

char *extraer_path_relativo(const char *path);

int get_free_inode();

int crear_inodo(const char *path, mode_t mode, file_type_t type, inode_t *padre);

void remove_dentry_from_parent_data(inode_t *parent, const char *path_child);

void create_root();

int write_file(inode_t *inode, const char *buf, size_t size, off_t offset);

int read_file(inode_t *inode, char *buf, size_t size, off_t offset);

#endif