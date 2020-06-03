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

int main() {
  Student *students[10];
  int to;

  for (int i = 0; i < 10; i++) {
    students[i] = (Student *)malloc(sizeof(Student));
    students[i]->id = i;
    students[i]->semester = 4;
    sprintf(students[i]->firstName, "%s%d", "Luis", i);
    sprintf(students[i]->lastName, "%s%d", "Palomino", i);
  }

  unlink("class.bin");

  if ((to = creat("class.bin", 0666)) < 0) {
    perror("Creation error");
    exit(1);
  }

  for (int i = 0; i < 10; i++) {
    if (write(to, students[i], sizeof(Student)) < 0) {
      perror("Error writing destination file");
      exit(2);
    }
  }

  close(to);
  for (int i = 0; i < 10; i++) {
    free(students[i]);
  }
  return 1;
}
