#include "utils.h"

#define ERROR -1

int
inode_index_from_path(const char *path)
{
	for (int32_t i = 0; i < MAX_INODES; i++) {
		if (filesystem.inode_bitmap[i] == true) {
			inode_t *inodo_actual = &filesystem.inodes[i];
			;

			if (strcmp(inodo_actual->path, path) == 0)
				return i;
		}
	}
	return -ENOENT;
}

char *
extraer_path_padre(const char *path)
{
	if (path == NULL || strlen(path) == 0 || strcmp(path, "/") == 0) {
		return NULL;  // No tiene padre
	}

	char *path_copy = strdup(path);
	if (path_copy == NULL) {
		return NULL;
	}

	char *last_slash = strrchr(path_copy, '/');
	if (last_slash == NULL) {
		free(path_copy);
		return NULL;
	}

	if (last_slash == path_copy) {
		// El padre es "/"
		path_copy[1] = '\0';
		return path_copy;
	}

	*last_slash = '\0';
	return path_copy;
}

char *
extraer_path_relativo(const char *path)
{
	const char *slash = strrchr(path, '/');
	const char *base = slash ? (slash + 1) : path;

	if (*base == '\0')
		return strdup("");

	return strdup(base);  // devuelve puntero justo al nombre
}

int
get_free_inode()
{
	for (int i = 0; i < MAX_INODES; i++) {
		if (!filesystem.inode_bitmap[i])
			return i;
	}

	printf("[debug] get_free_inode - no left inodes");
	return -ENOSPC;
}

int
crear_inodo(const char *path, mode_t mode, file_type_t type, inode_t *padre)
{
	// Agregar una "dentry" a la data del padre. Guarda el indice a los inodos hijos.
	char *path_relativo = extraer_path_relativo(path);
	size_t n = strlen(path_relativo) + 1;

	if (padre->size + n > BLOCK_SIZE) {
		printf("[debug] crear_inodo - parent cannot fit relative "
		       "path\n");
		return -ENOSPC;
	}

	memcpy(&padre->data[padre->size], path_relativo, n);
	(padre->size) += n;

	int free_index = get_free_inode();
	if (free_index < 0)
		return free_index;

	inode_t *new_inode = &filesystem.inodes[free_index];
	memset(new_inode,
	       0,
	       sizeof(inode_t));  // Para que no hayan errores con basura

	new_inode->file_type = type;
	new_inode->mode = mode;
	new_inode->nlink =
	        type == DIRECTORY
	                ? 2
	                : 1;  // Recordar que sólo el root tiene dos links
	strcpy(new_inode->path, path);

	new_inode->gid = getgid();
	new_inode->uid = getuid();

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] create-root - could not get time\n");
	} else {
		new_inode->atime = start.tv_sec;
		new_inode->mtime = start.tv_sec;
		new_inode->ctime = start.tv_sec;
	}

	++(filesystem.used_inodes);
	filesystem.inode_bitmap[free_index] = true;

	free(path_relativo);
	return free_index;
}

void
remove_dentry_from_parent_data(inode_t *parent, const char *path_child)
{
	// extraemos solo el nombre del hijo
	char *name_to_remove = extraer_path_relativo(path_child);
	if (!name_to_remove)
		return;

	char new_data[BLOCK_SIZE];
	size_t new_size = 0;

	// recorremos las entradas actuales
	size_t off = 0;
	while (off < (size_t) parent->size) {
		char *entry = &parent->data[off];
		size_t len = strlen(entry) + 1;

		if (strcmp(entry, name_to_remove) != 0) {
			// copiar solo las entradas distintas de la que queremos eliminar
			memcpy(&new_data[new_size], entry, len);
			new_size += len;
		}

		off += len;
	}

	// sustituimos el data viejo por el nuevo
	memcpy(parent->data, new_data, new_size);
	parent->size = new_size;

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] create-root - could not get time\n");
	} else {
		parent->mtime = start.tv_sec;
		parent->ctime = start.tv_sec;
	}

	free(name_to_remove);
}

void
create_root()
{
	inode_t *root = &filesystem.inodes[0];
	memset(root, 0, sizeof(inode_t));  // Para que no hayan errores con basura
	strcpy(root->path, PATH_ROOT);
	root->ino = 0;
	root->nlink = 2;
	root->file_type = DIRECTORY;
	root->mode = __S_IFDIR | 0755;
	root->uid = getuid();
	root->gid = getgid();
	root->size = 0;

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] create-root - could not get time\n");
	} else {
		root->atime = start.tv_sec;
		root->mtime = start.tv_sec;
		root->ctime = start.tv_sec;
	}

	filesystem.inode_bitmap[0] = true;
	++(filesystem.used_inodes);
}

int
write_file(inode_t *inode, const char *buf, size_t size, off_t offset)
{
	if (offset + size > BLOCK_SIZE) {
		printf("[debug] write_file - path: %s does not have memory "
		       "space\n",
		       inode->path);
		return -ENOSPC;
	}

	memcpy(&inode->data[offset], buf, size);
	inode->size = offset + size;

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] crear_inodo - could not get time\n");
	} else {
		inode->atime = start.tv_sec;
		inode->mtime = start.tv_sec;
	}


	return size;
}

int
read_file(inode_t *inode, char *buf, size_t size, off_t offset)
{
	if ((size_t) offset >= inode->size) {
		printf("[debug] read_file - path: %s EOF, nothing to read\n",
		       inode->path);
		return 0;
	}

	if (offset + size > inode->size) {
		size = inode->size - offset;
	}

	if (inode->size == 0) {
		printf("[debug] read_file - path: %s does not have data\n",
		       inode->path);
		return -ENODATA;
	}

	memcpy(buf, &inode->data[offset], size);

	struct timespec start;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		printf("[debug] crear_inodo - could not get time\n");
	} else {
		inode->atime = start.tv_sec;
	}

	return size;
}