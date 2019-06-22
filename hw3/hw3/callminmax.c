/*
 * This program creates a child process that it communicates
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char * argv[]) {
    int cp[4][2];     // integer two dimensional array for the pipes
    int pid = 0;   // process id of this proccess
    char ch;       // character read from the pipe
    int numForks; // the number of times to fork
    
    clock_t start_time, end_time;
    double cpu_time_used;
    //struct tms { clock_t tms_stime; clock_t tms_cstime;};
    
    if (argc < 3){
		printf("Usage: hw3 <num of fork> <filename>\n");
		return -1;
	}

	start_time = clock();
	for (numForks = 0; numForks < atoi(argv[1]); numForks++){
		printf("This is before the fork.\n");
		if (pipe(cp[numForks]) < 0) {
			printf("didn't work, couldn't not establish pipe.\n");
			return -1;
		}
			

		pid = fork();
		if (pid == 0) {
			printf("this is the child. not the original\n");
			close(1);       //close stdout
			dup2(cp[numForks][1], 1); //move stdout to pipe of cp[1]
			close(0);       //close stdin
			close(cp[numForks][0]);   //close pipe in
			 
			//note: All the arguments in exec have to be strings.
			// with an extra null string to end the args
			execl("minmax","minmax", "input1.txt",(char *) 0);  
		} 
		else 
		{
			close(cp[numForks][1]); //if you don't close this part of the pipe 
				// then the while loop (three lines down) will never return
			printf("this is the parent. the 'original.'\n");
			while( read(cp[numForks][0], &ch, 1) == 1) {
				printf("%c",ch);
				//write(1, &ch, 1);
				
			}
		}
	}
	
	end_time = clock();
	cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
	printf("all done.\n");
	printf("The amount of time to process the file is %f\n", cpu_time_used);
    
    printf("This is after the fork.\n");
    return 0;
}
