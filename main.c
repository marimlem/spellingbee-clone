#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct wordlist {
	char *word;
	int	found;
	struct wordlist *next;
} t_wordlist;

void add_to_list(char *word, t_wordlist **head) {
	t_wordlist *new_word = malloc(sizeof(t_wordlist));
	new_word->word = strdup(word);
	new_word->found = 0;
	new_word->next = NULL;
	
	if (*head == NULL) {
		*head = new_word;
	} else {
		t_wordlist *current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_word;
	}
}

int	word_with_chars(char *word, char *argv[])
{
	int i = 0;

	if (strrchr(word, argv[2][0]) == NULL)
		return (1);
	while (word && word[i] && (strrchr(argv[1], word[i]) != NULL || word[i] == argv[2][0]))
		i++;
	if (!word || word[i] == '\n' || word[i] == '\0')
		return (0);
	return (1);
}

void	game_print(t_wordlist *head, int words_left, int word_amount)
{
	t_wordlist *current = head;

	printf("==================\nWords left: %d\n", words_left);
	printf("found words:\n");
	while (current)
	{
		if (current->found == 1)
		{
			printf("  %s", current->word);
		}
		current = current->next;
	}
	printf("\n=========\n");
}

int	handle_options(char *input, t_wordlist *head, int words_left, int word_amount)
{
	t_wordlist *current = head;
	size_t len = 0;
	
	if (strcmp(input, "-q\n") == 0)
	{
		printf("you found %d of %d words!\nexit game\n", word_amount - words_left, word_amount);
		return 1;
	}
	if (strcmp(input, "-p\n") == 0)
	{
		game_print(head, words_left, word_amount);
		return 2;
	}
	if (strcmp(input, "-cheat\n") == 0)
	{
		int i = 0;
		int found = 0;
		while (current)
		{
			if (current->found == 0)
			{
				printf("❌  %s", current->word);
			}
			else
			{
				printf("✅  %s", current->word);
				found++;
			}
			i++;
			current = current->next;
		}
		printf("you found %d of %d words!\nwant to keep going?", found, word_amount);
		free(input);
		input = NULL;
		if (getline(&input, &len, stdin) == -1)
			return 1;
		if (strcmp(input, "yes\n") == 0 || strcmp(input, "y\n") == 0)
			return 2;
		else
			return 1;
	}
	if (strcmp(input, "-h\n") == 0)
	{
		printf("Commands:\n");
		printf("  -q: quit\n");
		printf("  -p: print found words\n");
		printf("  -cheat: show all words\n");
		printf("  -h: help\n");
		return 2;
	}
	return 0;
}

int	input_handler(char *input, t_wordlist *head, int *words_left, int word_amount)
{
	int var = 0;
	t_wordlist *current = head;

	var = handle_options(input, head, *words_left, word_amount);
	if (var != 0)
		return var;
	while (current && strcmp(input, current->word) != 0)
	{
		current = current->next;
	}
	if (current && current->word)
	{
		if (current->found == 1)
		{
			printf("  👈 Already found!\n");
		}
		else
		{
			current->found = 1;
			*words_left = *words_left - 1;
			printf("  ✅ Correct! (%d left)\n", *words_left);
			if (*words_left == 0)
			{
				printf("You won!\n");
				return 1;
			}
		}
	}
	else
		printf("  ❌ Wrong!\n");
	return 0;
}


void	game_loop(t_wordlist *head, int word_amount)
{
	t_wordlist *current = head;

	char *input = NULL;
	size_t len = 0;
	ssize_t nread;
	int words_left = word_amount;
	int var = 0;

	while(1 && var != 1)
	{
		current = head;
		nread = getline(&input, &len, stdin);
		if (nread == -1)
			break;
		var = input_handler(input, head, &words_left, word_amount);
		free(input);
		input = NULL;
	}
}

	

int main(int argc, char *argv[]) {
    int fd;
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
	t_wordlist *head = NULL;
	int word_amount = 0;
    
	if (argv[1] == NULL || argv[2] == NULL)
		return (1);
    fd = open("/usr/share/dict/american-english", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    stream = fdopen(fd, "r");
    if (stream == NULL) {
        perror("fdopen");
        close(fd);
        exit(1);
    }
    while ((nread = getline(&line, &len, stream)) != -1) {
		if (strlen(line) > 4 && word_with_chars(line, argv) == 0)
		{
			add_to_list(line, &head);
			word_amount++;
		}
    }

	game_loop(head, word_amount);
    free(line);
    fclose(stream); // This also closes the file descriptor fd
    return 0;
}