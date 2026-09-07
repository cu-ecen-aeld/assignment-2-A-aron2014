#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int fd;
	ssize_t nr;
	//open syslog
	openlog("writer",LOG_PID,LOG_USER);
	//Parse input args and verify both were provided
	if (argc<3){
		syslog(LOG_ERR, "Incorrect number of arguments provided");
		return 1;
	}
	else if (strlen(argv[1])==0){
		syslog(LOG_ERR, "Empty file path provided");
		return 1;
	}
	else if (strlen(argv[2])==0){
		syslog(LOG_ERR, "Empty message to write provided");
		return 1;
	}

	int flags=O_WRONLY|O_CREAT|O_TRUNC|O_SYNC;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const char *writefile = argv[1];
	const char *writestr  = argv[2];
	if((fd=open(writefile, flags, mode))==-1){

		syslog(LOG_ERR, "Can't open %s", writefile);
		return 1;
	}
	if((nr=write(fd,writestr, strlen(writestr)))==-1){
		syslog(LOG_ERR, "Unable to write to file %d", fd);
	}
	else{
		syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
	}
	
	//Close file and clean up data
	close(fd);
	closelog();

	return 0;
}
