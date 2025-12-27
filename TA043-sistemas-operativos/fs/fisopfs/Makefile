CC       := gcc
CFLAGS   := -ggdb3 -O2 -Wall -std=c11 -Wno-unused-function -Wvla
PKG_CFLAGS := $(shell pkg-config fuse --cflags)
PKG_LIBS   := $(shell pkg-config fuse --libs)

SRCS     := $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)

FS_NAME  := fisopfs

.PHONY: all build clean format docker-build docker-run docker-exec

all: build

build: $(FS_NAME)

$(FS_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PKG_CFLAGS) -o $@ $(OBJS) $(PKG_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(PKG_CFLAGS) -c $< -o $@

format: .clang-files .clang-format
	xargs -r clang-format -i <$<

docker-build:
	./dock build

docker-run:
	./dock run

docker-exec:
	./dock exec

clean:
	rm -f $(OBJS) $(FS_NAME) core vgcore.*