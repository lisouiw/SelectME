#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>


int		main()
{
	int s;

	while (42)
	printf("%i\n",s = ioctl(0, SIGWINCH ));
	return (0);
}

/*
void sighandler(int);



int main()
{
	printf("ENTREE\n");
	signal(SIGTSTP, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	while(1) 
	{
		printf("Going to sleep for a second...\n");
		sleep(1); 
	}
	return(0);
}

void sighandler(int signum)
{
	printf("AAH\n");
	printf("Caught signal %d, coming out...\n", signum);
	printf("NICE !\n");
	exit(signum);
}*/
