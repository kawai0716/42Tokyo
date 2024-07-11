#include "get_next_line_bonus.h"

char *get_next_line(int fd)
{
    char *save;
    char *str;
    char *c;
	size_t i;
	size_t j;
    size_t subread;
    str = (char *)malloc(BUFFER_SIZE + 1);
    save = NULL;
    if(!str || fd != 0)
        return (NULL);
    while(strchr(save, '\n') == NULL)
    {
        subread = read (fd, str, BUFFER_SIZE);
        if(subread = 0)
            break;
        c = save;
        save = strjoin(save, str);
        free (c);
	}
	if(strchr(save, '\n') == '\n')
	{
		i = strlen(save);
		j = strlen2(save);
		char *answer = ft_substr(save, 0, j);
		c = save;
		save = ft_substr(save, j, i-j);
		free (c);
		return (answer);
	}
	else if(save)
	{
		char *answer = strdup(save);
		free (save);
		save = NULL;
		return (answer);
	}
	return (0);
}
