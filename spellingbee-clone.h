#ifndef SPELLINGBEE_CLONE_H
#define SPELLINGBEE_CLONE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


typedef struct s_wordlist {
	char	*word;
	int		found;
	struct s_wordlist *next;
} t_wordlist;

typedef struct s_data{
	int		word_amount;
	int		fd;
	char	*input;
	t_wordlist	*head;
    FILE *stream;

} t_data;

void	add_to_list(char *word, t_data *data);
int		word_with_chars(char *word, char *argv[]);
void	game_print(t_wordlist *head, int words_left, int word_amount);
int		handle_options(char *input, t_wordlist *head, int words_left, int word_amount);
int		input_handler(char *input, t_wordlist *head, int *words_left, int word_amount);
void	game_loop(t_data *data);
int		main(int argc, char *argv[]);


int	setup_game(int argc, char *argv[], t_data *data);


#endif // SPELLINGBEE_CLONE_H