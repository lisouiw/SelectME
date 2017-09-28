

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

void checktty(int fd, const char *name)
{
	/* isatty() always returns either 0 (error or it is not a terminal) or 1
	 *	 * (it is a terminal). */
	if(isatty(fd)==0)
	{
		/* See the man page for all of the possible error cases */
		if(errno == EINVAL || errno == ENOTTY)
			printf("%s is not a terminal.\n", name);
		else
		{
			printf("%s\n", name);
			perror("isatty");
		}
	}
	else 
		printf("%s is a terminal.\n", name);
}


int main(void)
{
	checktty(STDIN_FILENO,  "stdin");
	checktty(STDOUT_FILENO, "stdout");
	checktty(STDERR_FILENO, "stderr");
}
