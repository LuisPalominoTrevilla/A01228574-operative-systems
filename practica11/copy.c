#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int fo, fd, rd, wr, ptr;
  char *originFilename = argv[1];
  char *dstFilename = argv[2];
  char buf[1024];

  if (argc < 2) {
    printf("Copy: Missing file operand\n");
    exit (1); 
  }

  if (argc < 3) {
    printf("Copy: Missing destination file operand after '%s'\n", originFilename);
    exit (1); 
  }

  if ((fo = open(originFilename, O_RDONLY)) < 0) {
    perror("Creation error");
    exit (1);
  }

  if ((fd = creat(dstFilename, 0666)) < 0) {
    perror("Creation error");
    exit (2);
  }

  while ((rd = read(fo, buf, sizeof(buf))) != 0) {
    if (rd < 0) {
      perror("Error reading source file");
      exit (3);
    }

    wr = 0;

    do {
      if ((ptr = write(fd, &buf[wr], rd - wr)) < 0) {
        perror("Error writing destination file");
        exit (4);
      }
      wr += ptr;
    } while (wr < rd);
  }

  close(fo);
  close(fd);
  return 1;
}