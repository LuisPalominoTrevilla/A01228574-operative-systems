#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s {
  unsigned char id;
  unsigned char semester;
  char firstName[20];
  char lastName[20];
} Student;

int main(int argc, char **argv) {
  Student *student;
  int src, idx;
  char *newLastName;

  if (argc < 3) {
    printf("Read: Missing student index and new last name\n");
    exit(1);
  }

  idx = atoi(argv[1]);
  newLastName = argv[2];
  if (idx < 0 || idx > 9) {
    printf("Update last name: Index out of bounds\n");
    exit(2);
  }

  student = (Student *)malloc(sizeof(Student));

  if ((src = open("class.bin", O_RDWR)) < 0) {
    perror("Read error");
    exit(3);
  }

  lseek(src, idx * sizeof(Student), SEEK_CUR);

  if (read(src, student, sizeof(Student)) < 0) {
    perror("Error writing destination file");
    exit(4);
  }

  strcpy(student->lastName, newLastName);
  for (int i = strlen(student->lastName); i < 20; i++) {
    student->lastName[i] = 0;
  }

  lseek(src, -1 * sizeof(Student), SEEK_CUR);

  if (write(src, student, sizeof(Student)) < 0) {
    perror("Error writing destination file");
    exit(5);
  }

  close(src);
  free(student);
  return 1;
}
