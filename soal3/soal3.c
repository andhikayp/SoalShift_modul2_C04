#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t child1;
	pid_t child2;
	pid_t child3;
	int ini_pipe1[2], ini_pipe2[2];
	pipe(ini_pipe1);
	pipe(ini_pipe2);
	
	// Process1
	child1 = fork();
	if (child1 < 0){
		exit(EXIT_FAILURE);
	}
	if (child1 == 0) {
		char *zip[] = {"unzip", "/home/haikal/Modul2/campur2.zip", NULL};
		execvp(zip[0], zip);
	} else {
		while(wait(NULL) > 0); //tunggu Process1 selesai
		// Process2
		child2 = fork();
		if (child2 < 0){
			exit(EXIT_FAILURE);
		} 
		if(child2 == 0){
			dup2(ini_pipe1[1], STDOUT_FILENO); 
			close(ini_pipe1[1]);
			close(ini_pipe1[0]);
			char *ls[] = {"ls", "/home/haikal/Modul2/campur2", NULL};
			execvp(ls[0], ls);
		}		
		else{
			while(wait(NULL) > 0); //tunggu Process2 selesai
			// Process3
			child3 = fork();
			if(child3 < 0){
				exit(EXIT_FAILURE);
			}
			if(child3 == 0){
				dup2(ini_pipe1[0], STDIN_FILENO);
				dup2(ini_pipe2[1], STDOUT_FILENO); 
				close(ini_pipe1[0]);
				close(ini_pipe1[1]);
				close(ini_pipe2[0]); 
				close(ini_pipe2[1]);
				char *grep[] = {"grep", ".txt$", NULL};
				execvp(grep[0], grep);
			}
			else{
				char outp[99999];
				close(ini_pipe1[0]);
				close(ini_pipe1[1]);
				close(ini_pipe2[1]);
				read(ini_pipe2[0], outp, sizeof(outp));
				FILE *f1 = fopen("/home/haikal/Modul2/daftar.txt", "w");
				fputs(outp, f1);
				fclose(f1);
			}
		}
	}
	return 0;
}
