#define FUSE_USE_VERSION 30
#define ERROR -1
#define EXITO 0
#define _POSIX_C_SOURCE 200809L
#define PATH_ROOT "/"

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "filesystem.h"
#include "utils.h"

#define DEFAULT_FILE_DISK "persistence_file.fisopfs"

char *filedisk = DEFAULT_FILE_DISK;
filesystem_t filesystem = { 0 };

static int
fisopfs_getattr(const char *path, struct stat *st)
{
	printf("[debug] fisopfs_getattr - path: %s\n", path);
	memset(st, 0, sizeof(struct stat));

	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_getattr - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	if (strcmp(path, "/") == 0) {
		st->st_mode = __S_IFDIR | 0755;
		st->st_nlink = 2;  // . y ..
		st->st_uid = getuid();
		st->st_gid = getgid();
		return 0;
	}

	int inode_index = inode_index_from_path(path);
	if (inode_index < 0) {
		printf("[debug] fisopfs_getattr - path: %s NO ENCONTRÓ EL "
		       "INDICE O ESTA VACIO\n",
		       path);
		return -ENOENT;  // -2 Error No Entry
	}

	inode_t inode = filesystem.inodes[inode_index];

	st->st_ino = inode.ino;
	st->st_nlink = inode.nlink;

	// Ver como calcular nlinks, un solo nivel de profundidad o varios
	if (inode.file_type == REGULAR_FILE) {
		st->st_mode = __S_IFREG | 0644;
		st->st_nlink = 1;
	} else {
		st->st_mode = __S_IFDIR | 0755;
		st->st_nlink = 2;  // . y ..
	}


	st->st_uid = inode.uid;
	st->st_gid = inode.gid;
	st->st_size = inode.size;

	st->st_atime = inode.atime;
	st->st_ctime = inode.ctime;
	st->st_mtime = inode.mtime;

	return EXITO;
}

static int
fisopfs_readdir(const char *path,
                void *buffer,
                fuse_fill_dir_t filler,
                off_t offset,
                struct fuse_file_info *fi)
{
	printf("[debug] fisopfs_readdir - path: %s\n", path);

	// Los directorios '.' y '..'
	filler(buffer, ".", NULL, 0);
	filler(buffer, "..", NULL, 0);

	int inode_index = inode_index_from_path(path);
	if (inode_index < 0) {
		printf("[debug] fisopfs_readdir - %s NOT FOUND\n", path);
		return -ENOENT;
	}

	inode_t *inodo_dir = &filesystem.inodes[inode_index];
	if (inodo_dir->file_type != DIRECTORY) {
		printf("[debug] fisopfs_readdir - %s IS NOT A DIRECTORY\n", path);
		return -ENOTDIR;
	}

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] create-root - could not get time\n");
	} else {
		inodo_dir->atime = start.tv_sec;
	}

	off_t off_aux = 0;
	while (inodo_dir->size > off_aux) {
		char *name = strdup(&inodo_dir->data[off_aux]);
		if (!name) {
			printf("[debug] fisopfs_readdir - ERROR ASSIGNATING "
			       "MEMORY\n");
			return -ENOMEM;
		}

		filler(buffer, name, NULL, 0);

		off_aux += (strlen(name) + 1);
		free(name);
	}

	return EXITO;
}

static int
fisopfs_read(const char *path,
             char *buffer,
             size_t size,
             off_t offset,
             struct fuse_file_info *fi)
{
	printf("[debug] fisopfs_read - path: %s, offset: %lu, size: %lu\n",
	       path,
	       offset,
	       size);


	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_read - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	int inode_index = inode_index_from_path(path);

	if (inode_index < 0) {
		printf("[debug] fisopfs_read - path: %s NO ENCONTRÓ EL INDICE "
		       "O ESTA VACIO\n",
		       path);
		return -ENOENT;  // -2 Error No Entry
	}

	inode_t *inode = &filesystem.inodes[inode_index];
	if (inode->file_type != REGULAR_FILE) {
		printf("[debug] fisopfs_read - path: %s is not a regular "
		       "file\n",
		       path);
		return ERROR;
	}

	int read_size = read_file(inode, buffer, size, offset);
	if (read_size < 0) {
		printf("[debug] fisopfs_read - path: %s could not be read\n",
		       path);
		return ERROR;
	}

	return read_size;
}

static int
fisopfs_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	printf("[debug] fisopfs_create - path: %s, mode: %u\n", path, mode);

	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_create - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	char *ruta_padre = extraer_path_padre(path);
	int inode_index_padre = inode_index_from_path(ruta_padre);
	free(ruta_padre);
	inode_t *inode_padre = &filesystem.inodes[inode_index_padre];

	int new_inode_index = crear_inodo(path, mode, REGULAR_FILE, inode_padre);
	if (new_inode_index < 0) {
		printf("[debug] fisopfs_create - crear_inodo has failed\n");
		return ERROR;  // codigo de error
	}

	return EXITO;
}

static int
fisopfs_mkdir(const char *path, mode_t mode)
{
	printf("[debug] fisopfs_mkdir - path: %s, mode: %u\n", path, mode);

	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_mkdir - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	if (inode_index_from_path(path) >= 0) {
		printf("[debug] fisopfs_mkdir - path: %s DIRECTORY ALREADY "
		       "EXISTS\n",
		       path);
		return ERROR;  // codigo de error
	}

	char *path_padre = extraer_path_padre(path);
	if (!path_padre) {
		printf("[debug] fisopfs_mkdir - path: %s PARENT PATH IS NULL\n",
		       path);
		return ERROR;  // codigo de error
	}

	int index_padre = inode_index_from_path(path_padre);
	free(path_padre);

	if (index_padre < 0) {
		printf("[debug] fisopfs_mkdir - path: %s INVALID PARENT "
		       "INDEX\n",
		       path);
		return ERROR;  // codigo de error
	}

	inode_t *padre = &filesystem.inodes[index_padre];
	if (padre->file_type != DIRECTORY) {
		printf("[debug] fisopfs_mkdir - path: %s PARENT IS NOT A "
		       "DIRECTORY\n",
		       path);
		return ERROR;  // codigo de error
	}

	int index = crear_inodo(path, mode, DIRECTORY, padre);
	if (index < 0)
		return ERROR;  // codigo de error

	printf("[debug] fisopfs_mkdir - success in fisopfs_mkdir\n");

	return EXITO;
}

static int
fisopfs_write(const char *path,
              const char *buffer,
              size_t size,
              off_t offset,
              struct fuse_file_info *fi)
{
	printf("[debug] fisopfs_write - path: %s\n", path);

	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_write - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	int inode_index = inode_index_from_path(path);

	if (inode_index < 0) {
		printf("[debug] fisopfs_write - path: %s NO ENCONTRÓ EL INDICE "
		       "O ESTA VACIO\n",
		       path);
		return -ENOENT;  // -2 Error No Entry
	}

	inode_t *inode = &filesystem.inodes[inode_index];
	if (inode->file_type != REGULAR_FILE) {
		printf("[debug] fisopfs_write - path: %s is not a regular "
		       "file\n",
		       path);
		return ERROR;
	}

	int written_size = write_file(inode, buffer, size, offset);
	if (written_size < 0) {
		printf("[debug] fisopfs_write - path: %s could not be "
		       "written\n",
		       path);
		return ERROR;
	}

	return written_size;
}

static int
fisopfs_utimens(const char *path, const struct timespec tv[2])
{
	printf("[debug] fisopfs_utimens - path: %s\n", path);

	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_utimens - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	int i = inode_index_from_path(path);
	if (i < 0) {
		printf("[debug] fisopfs_utimens - path: %s does not exist\n",
		       path);
		return -ENOENT;
	}
	inode_t *inode = &filesystem.inodes[i];

	inode->atime = tv[0].tv_sec;
	inode->mtime = tv[1].tv_sec;

	return EXITO;
}

static int
fisopfs_rmdir(const char *path)
{
	printf("[debug] fisopfs_rmdir - path: %s\n", path);

	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_rmdir - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	int i = inode_index_from_path(path);
	if (i < 0) {
		printf("[debug] fisopfs_rmdir - path: %s does not exist\n", path);
		return -ENOENT;  // codigo de error
	}

	inode_t *inode_to_remove = &(filesystem.inodes[i]);
	if (inode_to_remove->file_type != DIRECTORY) {
		printf("[debug] fisopfs_rmdir - path: %s is not a directory\n",
		       path);
		return -ENOTDIR;
	}

	if (inode_to_remove->size != 0) {
		printf("[debug] fisopfs_rmdir - path: %s is not empty\n", path);
		return -ENOTEMPTY;
	}

	char *path_padre = extraer_path_padre(path);
	if (!path_padre) {
		printf("[debug] fisopfs_rmdir - path: %s PARENT PATH IS NULL\n",
		       path);
		return ERROR;  // codigo de error
	}

	int i_parent = inode_index_from_path(path_padre);
	free(path_padre);

	inode_t *inode_parent = &(filesystem.inodes[i_parent]);
	remove_dentry_from_parent_data(inode_parent, path);

	filesystem.inode_bitmap[i] = false;
	--(filesystem.used_inodes);

	printf("[debug] fisopfs_rmdir - success in fisopfs_rmdir\n");

	return EXITO;
}

static int
fisopfs_unlink(const char *path)
{
	printf("[debug] fisopfs_unlink - path: %s\n", path);

	int inode_index = inode_index_from_path(path);
	if (inode_index < 0) {
		printf("[debug] fisopfs_unlink - path: %s does not exist\n", path);
		return -ENOENT;  // codigo de error
	}

	char *ruta_padre = extraer_path_padre(path);
	int inode_index_padre = inode_index_from_path(ruta_padre);
	free(ruta_padre);
	inode_t *inode_padre = &filesystem.inodes[inode_index_padre];

	remove_dentry_from_parent_data(inode_padre, path);
	filesystem.inode_bitmap[inode_index] = false;
	--(filesystem.used_inodes);

	printf("[debug] fisopfs_unlink - success in fisopfs_unlink\n");

	return EXITO;
}

void
fisopfs_destroy(void *private_data)
{
	printf("[debug] fisopfs_destroy\n");

	FILE *fs = fopen(filedisk, "w");
	if (!fs) {
		printf("[debug] fisopfs_destroy - error opening filedisk\n");
		exit(ERROR);
	}

	size_t written_elements = fwrite(&filesystem, sizeof(filesystem), 1, fs);
	if (written_elements < 0) {
		printf("[debug] fisopfs_destroy - error writing on filedisk\n");
		exit(ERROR);
	}

	fflush(fs);
	fclose(fs);
	printf("[debug] fisopfs_destroy - success in fisopfs_destroy\n");
}

static int
fisopfs_flush(const char *path, struct fuse_file_info *fi)
{
	printf("[debug] fisopfs_flush - path: %s\n", path);

	fisopfs_destroy(NULL);
	return EXITO;
}

static void *
fisopfs_init(struct fuse_conn_info *conn)
{
	printf("[debug] fisopfs_init\n");

	FILE *fs = fopen(filedisk, "r");
	if (!fs) {
		FILE *new_fs = fopen(filedisk, "w");
		fclose(new_fs);
		create_root();  // Agrega el root
	} else {
		size_t read_elements =
		        fread(&filesystem, sizeof(filesystem), 1, fs);
		fclose(fs);
		if (read_elements < 0) {
			printf("[debug] fisopfs_init - error loading existing "
			       "data\n");
			return NULL;
		}
	}
	printf("[debug] fisopfs_init - success in fisopfs_init\n");
	return EXITO;
}

static int
fisopfs_truncate(const char *path, off_t size)
{
	printf("[debug] fisopfs_truncate - path: %s\n", path);


	if (strlen(path) > MAX_PATH) {
		printf("[debug] fisopfs_trucate - path: %s PATH EXCEDEED SIZE, "
		       "índice invalido\n",
		       path);
		return ERROR;  // codigo de error
	}

	int i = inode_index_from_path(path);
	if (i < 0) {
		printf("[debug] fisopfs_truncate - path: %s does not exist\n",
		       path);
		return -ENOENT;
	}
	inode_t *inode = &filesystem.inodes[i];

	if (size > inode->size) {
		printf("[debug] fisopfs_truncate - path: %s - size is greater "
		       "than file size\n",
		       path);
		return -ENOENT;
	}

	inode->size = size;

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] create-root - could not get time\n");
	} else
		inode->mtime = start.tv_sec;

	return EXITO;
}

static struct fuse_operations operations = { .getattr = fisopfs_getattr,
	                                     .readdir = fisopfs_readdir,
	                                     .read = fisopfs_read,

	                                     // operations
	                                     .create = fisopfs_create,
	                                     .mkdir = fisopfs_mkdir,
	                                     .write = fisopfs_write,
	                                     .utimens = fisopfs_utimens,
	                                     .rmdir = fisopfs_rmdir,
	                                     .unlink = fisopfs_unlink,
	                                     .flush = fisopfs_flush,
	                                     .destroy = fisopfs_destroy,
	                                     .init = fisopfs_init,
	                                     .truncate = fisopfs_truncate };

int
main(int argc, char *argv[])
{
	for (int i = 1; i < argc - 1; i++) {
		if (strcmp(argv[i], "--filedisk") == 0) {
			filedisk = argv[i + 1];

			// We remove the argument so that fuse doesn't use our
			// argument or name as folder.
			// Equivalent to a pop.
			for (int j = i; j < argc - 1; j++) {
				argv[j] = argv[j + 2];
			}

			argc = argc - 2;
			break;
		}
	}

	if (filedisk[0] != '/') {
		char cwd[MAX_PATH];
		if (!getcwd(cwd, sizeof(cwd))) {
			exit(-ENOMEM);
		}

		size_t len_path_total = strlen(cwd) + 1 + strlen(filedisk) + 1;
		char *abs_path = malloc(len_path_total);
		if (!abs_path) {
			exit(-ENOMEM);
		}

		memcpy(abs_path, cwd, strlen(cwd));
		abs_path[strlen(cwd)] = '/';
		memcpy(abs_path + strlen(cwd) + 1, filedisk, strlen(filedisk) + 1);

		filedisk = abs_path;
	}

	return fuse_main(argc, argv, &operations, NULL);
}