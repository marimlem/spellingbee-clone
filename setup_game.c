#include "spellingbee-clone.h"

int	setup_game(int argc, char *argv[], t_data *data)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;


	if (argc < 2 || argv[1] == NULL || argv[2] == NULL)
	{
		printf("Usage: %s <several chars that are allowed> <one char that is necessary in all words>\ne.g.: ./a.out otnaiy m\n", argv[0]);
		return (1);
	}
	data->word_amount = 0;
	data->head = NULL;
	data->input = NULL;
    data->fd = open("/usr/share/dict/american-english", O_RDONLY);
    if (data->fd == -1) {
        perror("open");
        return(1);
    }
    data->stream = fdopen(data->fd, "r");
    if (data->stream == NULL) {
        perror("fdopen");
        close(data->fd);
        return(1);
    }
    while (getline(&line, &len, data->stream) != -1) 
	{
		if (strlen(line) > 4 && word_with_chars(line, argv) == 0)
		{
			add_to_list(line, data);
			data->word_amount++;
		}
    }
	return (0);
}