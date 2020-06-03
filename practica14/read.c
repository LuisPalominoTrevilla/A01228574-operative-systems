#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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

  if (argc < 2) {
    printf("Read: Missing student index\n");
    exit(1);
  }

  idx = atoi(argv[1]);
  if (idx < 0 || idx > 9) {
    printf("Read: Index out of bounds\n");
    exit(2);
  }

  student = (Student *)malloc(sizeof(Student));

  if ((src = open("class.bin", O_RDONLY)) < 0) {
    perror("Read error");
    exit(3);
  }

  lseek(src, idx * sizeof(Student), SEEK_CUR);

  if (read(src, student, sizeof(Student)) < 0) {
    perror("Error writing destination file");
    exit(4);
  }
  close(src);

  printf("My student is %d, %d, %s, %s\n", student->id, student->semester,
         student->firstName, student->lastName);
  free(student);
  return 1;
}
