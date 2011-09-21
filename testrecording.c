#include "types.h"
#include "record.h"
#include "fcntl.h"
#include "user.h"

int main(int argc, char *argv[]){
  int fd;
  char *out;
  //int num_records = 20;
  
  fd = open("./tr.out", O_CREATE);
  close(fd);
	startrecording();
  fd = open("./tr.out", O_RDWR);
  printf(fd, "Incio dos testes\n");
  close(fd);
  sleep(20);
	uptime();
	printf(fd,"Gravações: %d\n",fetchrecords(0,0));


  exec("cat tr.out", &out);

  return 0;
}

