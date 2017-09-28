#include <unistd.h>
#include <stdio.h>
#include <string.h>

int		main()
{
	char *ret, tty[40];

	if ((ret = ttyname(STDIN_FILENO)) == NULL)
		perror("ttyname() error");
	else {
		strcpy(tty, ret);
		printf("The ttyname associated with my stdin is %s\n", tty);
	}
	printf("Je me trouve %i\n", ttyslot());
	return (0);
}

