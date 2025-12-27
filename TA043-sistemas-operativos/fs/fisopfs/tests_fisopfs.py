import os

MOUNT = "dir"

def clean_mount():
    for root, dirs, files in os.walk(MOUNT, topdown=False):
        for file in files:
            os.remove(os.path.join(root, file))
        for dir in dirs:
            os.rmdir(os.path.join(root, dir))

def print_result(ok, msg):
    result = f"\033[92m[OK]\033[0m {msg}" if ok else f"\033[91m[FAIL]\033[0m {msg}"
    print(f"{result}")

# Test Directorios

def test_getattr_root():
    print("\nTest: getattr sobre root")
    ok = os.path.isdir(MOUNT)
    print_result(ok, "Root es un directorio")

def test_mkdir_root():
    print("\nTest: mkdir en root")
    clean_mount()
    path = os.path.join(MOUNT, "dir1")
    os.mkdir(path)
    ok = "dir1" in os.listdir(MOUNT)
    print_result(ok, "mkdir crea directorio en root")

def test_readdir_root():
    print("\nTest: readdir en root")
    clean_mount()
    os.mkdir(os.path.join(MOUNT, "d1"))
    os.mkdir(os.path.join(MOUNT, "d2"))
    entries = os.listdir(MOUNT)
    ok = set(entries) == {"d1", "d2"}
    print_result(ok, "readdir lista directorios en root correctamente")

def test_readdir():
    print("Test readdir")
    clean_mount()
    os.mkdir(os.path.join(MOUNT, "d1"))
    os.mkdir(os.path.join(MOUNT, "d2"))
    files = os.listdir(MOUNT)
    ok = "d1" in files and "d2" in files
    print_result(ok, "readdir lista directorios correctamente")

def test_rmdir_empty():
    print("\nTest: rmdir de directorio vacío")
    clean_mount()
    path = os.path.join(MOUNT, "dir1")
    os.mkdir(path)
    os.rmdir(path)
    ok = "dir1" not in os.listdir(MOUNT)
    print_result(ok, "rmdir elimina directorio vacío")

def test_mkdir():
    print("Test mkdir")
    clean_mount()
    path = os.path.join(MOUNT, "dir1")
    os.mkdir(path)
    print_result("dir1" in os.listdir(MOUNT), "mkdir crea directorio en root")

def test_rmdir_not_empty():
    print("\nTest: rmdir de directorio no vacío")
    clean_mount()
    dir_path = os.path.join(MOUNT, "dir1")
    os.mkdir(dir_path)
    with open(os.path.join(dir_path, "file.txt"), "w") as f:
        f.write("data")
    try:
        os.rmdir(dir_path)
        ok = False
    except OSError:
        ok = True
    print_result(ok, "rmdir falla al intentar eliminar directorio no vacío")

def test_mkdir_multinivel():
    print("\nTest: mkdir multinivel")
    clean_mount()
    p1 = os.path.join(MOUNT, "a")
    p2 = os.path.join(p1, "b")
    os.mkdir(p1)
    os.mkdir(p2)
    ok = os.path.isdir(p2)
    print_result(ok, "mkdir multinivel funciona")

# Test Archivos

def test_utimens_file():
    print("Test: utimens de archivo")
    clean_mount()
    path = os.path.join(MOUNT, "f_utimens.txt")
    # crear archivo
    with open(path, "w") as f:
        f.write("x")
    # establecer timestamps específicos
    atime = 1000000000
    mtime = 1000000500
    os.utime(path, (atime, mtime))
    st = os.stat(path)
    ok = (int(st.st_atime) == atime and int(st.st_mtime) == mtime)
    print_result(ok, "utimens actualiza atime y mtime correctamente")

def test_create_file():
    print("\nTest: creación de archivo en root")
    clean_mount()
    path = os.path.join(MOUNT, "f1.txt")
    # abrir en modo escritura invoca create
    with open(path, "w"):
        pass
    ok = "f1.txt" in os.listdir(MOUNT)
    print_result(ok, "create() crea archivo en root")

def test_write_read_file():
    print("\nTest: write y read de archivo")
    clean_mount()
    path = os.path.join(MOUNT, "f1.txt")
    data = "Hola FS\n"
    with open(path, "w") as f:
        f.write(data)
    with open(path, "r") as f:
        contenido = f.read()
    ok = (contenido == data)
    print_result(ok, "write/read conservan datos correctamente")

def test_remove_file():
    print("\nTest: unlink de archivo")
    clean_mount()
    path = os.path.join(MOUNT, "f1.txt")
    with open(path, "w"):
        pass
    os.remove(path)
    ok = "f1.txt" not in os.listdir(MOUNT)
    print_result(ok, "unlink elimina archivo correctamente")

def test_truncate_achicar():
    print("Test: truncate (achicar)")
    clean_mount()
    path = os.path.join(MOUNT, "test_truncate.txt")
    data = "hola como estas"
    with open(path, "w") as f:
        f.write(data)
    # reducir tamaño a 5 bytes
    os.truncate(path, 5)
    st = os.stat(path)
    content = open(path, "r").read()
    ok = (st.st_size == 5 and content == data[:5])
    print_result(ok, "truncate restringe tamaño correctamente")

def run_all():

    # directorios
    test_getattr_root()
    test_mkdir_root()
    test_readdir_root()
    test_readdir()
    test_rmdir_empty()
    test_mkdir()
    test_rmdir_not_empty()
    test_mkdir_multinivel()

    # archivos
    test_utimens_file()
    test_create_file()
    test_write_read_file()
    test_remove_file()

    test_truncate_achicar()

if __name__ == "__main__":
    run_all()