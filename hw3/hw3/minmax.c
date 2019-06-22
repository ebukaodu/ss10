/*
 * This is a program to find the min and max values from a binary integer file.  
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

 int main(int argc, char * argv[]) {
	const char * filename;  // name of file to read
	FILE * ft;  // file handle for the file
	int pid,    // process id of this process
	    num,    // the number of integer values in the file
	    i,      // loop control variable for reading values
	    temp=0; // used to store each value read from the file
    int min = 1000000; // we will replace this as we read the file
    int max = 0; // we will replace this as we read the file
	long size;  // size in bytes of the input file
/*********************************************************************/
   
    if (argc<2) {  // not enough arguments, need output file name
        printf("Usage: readfile <filename>\n");
        return 1;
    }
    filename = argv[1];  // read the file named on the command line
	
	ft= fopen(filename, "rb") ;
	if (ft) {
		pid = getpid();
		fseek (ft,0,SEEK_END); //go to end of file
		size = ftell(ft);      //what byte in file am I at?
		fseek (ft,0,SEEK_SET); //go to beginning of file
		num = (int)size / (int)sizeof(int); // number of integer values
		
		// now read and print out the values
		for(i = 0; i < num; i++){
			fread(&temp,sizeof(int),1,ft);
			
            if (temp > max) max = temp;
            if (temp < min) min = temp;
		}
		fclose(ft);  // close the file now that we're done
	}
    printf("Chukwuebuka Odu \n");
    printf("Process ID is: %d\n", pid);
	printf("The minimum value is: %d\n", min);  
    printf("The maximum value is: %d\n", max);
	return 0;
}
