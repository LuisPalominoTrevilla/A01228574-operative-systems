#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct stat mystat, *sp = &mystat;
  struct dirent *myDir;
  int r;
  DIR *directory;
  char *filename, path[1024], cwd[256];
  filename = "./";
  if (argc > 1)
    filename = argv[1];
  if ((r = lstat(filename, sp) < 0)) {
    printf("no such file %s\n", filename);
    exit(1);
  }
  strcpy(path, filename);
  if (path[0] != '/') {
    getcwd(cwd, 256);
    strcpy(path, cwd);
    strcat(path, "/");
    strcat(path, filename);
  }
  if (S_ISDIR(sp->st_mode)) {
    directory = opendir(path);
    while ((myDir = readdir(directory)) != NULL) {
      printf("%s\n", myDir->d_name);
    }
    closedir(directory);
  } else {
    printf("Not a directory %s\n", path);
    exit(2);
  }
}
