#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "Reiniciando la computadora, nos vemos pronto\n");
  reboot();
  exit();
}
