#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  // Crear el bloque de memoria
  int shmId = shmget(600, 400, 0644 | IPC_CREAT);
  int children[5];
  for (int i = 0; i < 5; i++) {
    int pid = fork();
    if (pid != 0) {
      children[i] = pid;
      shmId = shmget(600, 400, 0644);
      int *var = (int *)shmat(shmId, NULL, 0);
      var = &var[i * 10];
      for (int j = 0; j < 10; j++) {
        var[j] = i + '0';
      }
      return 0;
    }
  }
  for (int i = 0; i < 5; i++) {
    waitpid(children[i], 0, 0);
  }
  int *var = (int *)shmat(shmId, NULL, 0);
  printf("El contenido es ");
  for (int i = 0; i < 5*10; i++) {
    printf("%d ", var[i]);
  }
  printf("\n");
  return 0;
}
