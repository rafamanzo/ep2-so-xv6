#include "types.h"
#include "record.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
  int fd;
  char *out;
  //int num_records = 20;
  
  fd = open("./tr.out", O_CREATE);
  close(fd);

  fd = open("./tr.out", O_RDWR);

  printf(fd, "Oi\n");

  close(fd);

  exec("cat tr.ou", &out);

  return 0;
}
