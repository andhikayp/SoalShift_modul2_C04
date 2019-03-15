#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <time.h>
//template from modul 2 daemon
int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int i=1;
  while(1) 
  {
    
    char direktori[]="/home/andhika/Documents/makanan/makan_enak.txt";
    struct stat nama;
    stat(direktori, &nama);
    time_t x = nama.st_atime; //waktu akses
    time_t y = time(NULL); //waktu program berjalan
    
    if(difftime(y, x)<=30) // kiri-kanan
    {
      char x[100];
      sprintf(x, "%d", i);

      char direktori2[]="/home/andhika/Documents/makanan/makan_sehat";
      strcat(direktori2, x);
      strcat(direktori2,".txt");
      
      FILE *makanan = fopen(direktori2, "w"); 
      fclose(makanan);
      i++;
    }
    //waktu program
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
