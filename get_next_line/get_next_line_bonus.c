#include "get_next_line_bonus.h"

char *result(char *save)
{
	size_t i;
	size_t j;
	char *nl;
	char *answer;
	char *c;
	if(nl = strchr(save, '\n') != NULL)
	{
		i = strlen(save[fd]);
		j = nl - save[fd] + 1;
		answer = ft_substr(save[fd], 0, j);
		c = save[fd];
		save = ft_substr(save[fd], j, i-j);
		free (c);
		return (answer);
	}
	else
	{
		answer = strdup(save[fd]);
		free (save[fd]);
		save[fd] = NULL;
		return (answer);
	}
	return (0); 
}

char *get_next_line(int fd)
{
    char *save[OPEN_MAX];
    char *str;
	char *c;
    size_t subread;
    str = (char *)malloc(BUFFER_SIZE + 1);
    save[fd] = NULL;
    if(!str || fd < 0 || fd >= OPEN_MAX)
        return (NULL);
    while(strchr(save[fd], '\n') == NULL)
    {
        subread = read (fd, str, BUFFER_SIZE);
        if(subread <= 0)
		{
			free (str);
			free (save[fd]);
			return (NULL);
		}
        c = save[fd];
        save[fd] = strjoin(save[fd], str);
        free (c);
	}
	free (str);
	return (result(save));
}
