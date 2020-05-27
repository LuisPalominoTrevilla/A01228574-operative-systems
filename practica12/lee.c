#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 100

int main(int argc, char **argv) {
  int fd, rd, ptr;
  char *filename = argv[1];
  char curr;
  char buf[BUFSIZE];

  if (argc < 2) {
    printf("Lee: Missing file operand\n");
    exit(1);
  }

  if ((fd = open(filename, O_RDONLY)) < 0) {
    perror("Creation error");
    exit(1);
  }

  while ((rd = read(fd, buf, sizeof(buf))) != 0) {
    if (rd < 0) {
      perror("Error reading source file");
      exit(3);
    }
    ptr = 0;

    do {
        printf("%c", buf[ptr]);
    } while (ptr++ < rd);
  }

  close(fd);
  return 1;
}
