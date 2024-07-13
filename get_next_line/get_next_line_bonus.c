#include "get_next_line_bonus.h"

char *get_next_line(int fd)
{
    char *save[OPEN_MAX];
    char *str;
    char *c;
	size_t i;
	size_t j;
    size_t subread;
    str = (char *)malloc(BUFFER_SIZE + 1);
    save = NULL;
    if(!str || fd < 0 || fd >= OPEN_MAX)
        return (NULL);
    while(strchr(save[fd], '\n') == NULL)
    {
        subread = read (fd, str, BUFFER_SIZE);
        if(subread == 0)
            break;
        c = save[fd];
        save[fd] = strjoin(save[fd], str);
        free (c);
	}
	if(strchr(save, '\n') != NULL)
	{
		i = strlen(save[fd]);
		j = strlen2(save[fd]);
		char *answer = ft_substr(save[fd], 0, j);
		c = save[fd];
		save = ft_substr(save[fd], j, i-j);
		free (c);
		return (answer);
	}
	else if(save[fd])
	{
		char *answer = strdup(save[fd]);
		free (save[fd]);
		save[fd] = NULL;
		return (answer);
	}
	return (0);
}
