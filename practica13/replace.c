#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void writeWordToFile(int, char *, char *, char *);

int main(int argc, char **argv) {
  int fd, rd;
  char space = 0;
  char *findWord = argv[1];
  char *replaceWord = argv[2];
  char *filename = argv[3];
  char *tmpFilename = "./replace.txt";
  int i = 0;
  char character;
  char word[100];

  if (argc < 4) {
    printf("Usage: a.out find replace filename\n");
    exit(1);
  }

  if ((fd = open(filename, O_RDONLY)) < 0) {
    perror("Creation error");
    exit(1);
  }

  if ((rd = open(tmpFilename, O_WRONLY | O_CREAT, 0600)) < 0) {
    perror("Creation error");
    exit(1);
  }

  while (read(fd, &character, 1)) {
    if ((character == ' ' || character == '\n') && !space) {
      space = 1;
      word[i] = '\0';
      i = 0;
      writeWordToFile(rd, word, findWord, replaceWord);
      write(rd, &character, sizeof(char));
    } else if (character != ' ' && character != '\n') {
      space = 0;
      word[i++] = character;
    } else if (space) {
      write(rd, &character, sizeof(char));
    }
  }
  word[i] = '\0';
  writeWordToFile(rd, word, findWord, replaceWord);
  close(fd);
  close(rd);
  unlink(filename);
  link(tmpFilename, filename);
  unlink(tmpFilename);
  exit(0);
}

void writeWordToFile(int fd, char *word, char *findWord, char *replaceWord) {
  if (strncmp(word, findWord, strlen(findWord)) == 0) {
    write(fd, replaceWord, strlen(replaceWord));
  } else {
    write(fd, word, strlen(word));
  }
}
