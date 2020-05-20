#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd, rd, ptr;
  unsigned int lines, words, chars;
  char space = 0;
  char *filename = argv[1];
  char curr;
  char buf;

  if (argc < 2) {
    printf("Lee: Missing file operand\n");
    exit(1);
  }

  if ((fd = open(filename, O_RDONLY)) < 0) {
    perror("Creation error");
    exit(1);
  }

  lines = 0;
  words = 0;
  chars = 0;

  while (read(fd, &buf, 1)) {
    chars++;
    if (buf == '\n') lines++;
    if ((buf == ' ' || buf == '\n' || buf == EOF) && !space) {
        space = 1;
        words++;
    } else if (buf != ' ' && buf != '\n' && buf != EOF) {
        space = 0;
    }
  }
  printf("%d %d %d\n", lines, words, chars);

  close(fd);
  exit(0);
}
