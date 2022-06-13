#include "get_next_line.h"

void	check(void)
{
	system("leaks a.out");
}

int main()
{
	int	fd;
	char	*line;
	//int i = 10;

	//atexit(check);
	fd = open("texto.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}