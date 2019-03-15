#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/home/haikal/Modul2/raw/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1)
  {
	long int i;
	struct dirent *file;
    	DIR *dr = opendir("/home/haikal/Modul2/raw/");
   	while ((file = readdir(dr)) != NULL)
	{
		char direct[256]="/home/haikal/Modul2/raw/";
		
		i=strlen(file->d_name);
       	 	char newdirect[256]="/home/haikal/Modul2/gambar/";
		char newName[256]="";

		if(file->d_name[i-1]=='g' && file->d_name[i-2]=='n' && file->d_name[i-3]=='p'&& file->d_name[i-4]=='.')
		{
			for(i=0;i<strlen(file->d_name)-4;i++)
			{
				newName[i]=file->d_name[i];
			}
		  strcat(direct,file->d_name);
		  strcat(newName,"_grey.png");
		  strcat(newdirect,newName);
		  rename(direct, newdirect);
		}
	}
 	sleep(5);
  }
  exit(EXIT_SUCCESS);
}
