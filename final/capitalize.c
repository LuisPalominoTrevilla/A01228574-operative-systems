#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv) {
  int input_file, tmp_file;
  char *filename;
  char character;
  char *tmpFilename = "./tmp.txt";

  if (argc < 2) {
    printf("Usage: a.out filename\n");
    exit(1);
  }

  filename = argv[1];

  if ((input_file = open(filename, O_RDONLY)) < 0) {
    perror("Can't open file");
    exit(1);
  }

  if ((tmp_file = open(tmpFilename, O_WRONLY | O_CREAT, 0600)) < 0) {
    perror("Creation error");
    exit(2);
  }

  while (read(input_file, &character, 1)) {
    char transformed_char = toupper(character);
    write(tmp_file, &transformed_char, sizeof(char));
  }

  close(input_file);
  close(tmp_file);
  unlink(filename);
  link(tmpFilename, filename);
  unlink(tmpFilename);
  exit(0);
}
