#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

//template from https://stackoverflow.com/questions/7328327/how-to-get-files-owner-name-in-linux-using-c
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

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

  while(1) {
    char direktori[]="/home/andhika/sisop19/modul2/hatiku/elen.ku";
    char syarat[]="www-data";
    struct stat info;
    chmod (direktori, 0777);
    stat(direktori, &info);  // Error check omitted
    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);
    if(strcmp(pw->pw_name,syarat)==0 && strcmp(gr->gr_name,syarat)==0)
      remove(direktori);
    sleep(3);
  }

  exit(EXIT_SUCCESS);
}
