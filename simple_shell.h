#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOWERCASE 1
#define TO_UNSIGNED 2

#define BUFFER_CLEARING -1
#define BUFFER_FOR_WRITE_FUNCTION 1024
#define BUFFER_FOR_READ_FUNCTION 1024

#define GETLINE_USING 0

#define HISTORY_DOCUMENT ".simple_shell_history"
#define MAXIMUM_LENGTH_HISTORY 4096

#define NORMAL_MODE_COMMAND 0
#define OR_MODE_COMMAND 1
#define AND_MODE_COMMAND 2
#define END_MODE_COMMAND 3

extern char **environ;

/**
 *  struct sll - singly linked list
 *  @num: number of nodes
 *  @ns: string
 *  @nxt: pointer to the next node
 */

typedef struct sll
{
	int num;
	char *ns;
	struct sll *nxt;
} linked_list;

/**
 * struct info_shape - data model for functions
 * @s_cmd: string of arguments from getline function
 * @argv: array of strings from s_cmd
 * @path: string for current command
 * @argc: arguments count
 * @counter_row: error count
 * @err_code: error code for exit function
 * @counter_flag: count line of input
 * @file_name: program file name
 * @env: environment linked list
 * @environ: custom environment from environment linked list
 * @history: history node
 * @alias: alias node
 * @changedflag: flag for changing environment
 * @feedback: feedback for last command
 * @chainning_buffer: pointer to chainning buffer
 * @mode_command: input for || && ;
 * @fd_read: flag for reading line
 * @history_counter_row: line counter for history file
 */

typedef struct info_shape
{
	linked_list *env;
	linked_list *history;
	linked_list *alias;
	char *s_cmd;
	char **argv;
	char *path;
	int argc;
	unsigned int counter_row;
	int err_code;
	int changedflag;
	int feedback;
	int counter_flag;
	char *file_name;
	char **environ;
	char **chainning_buffer;
	int mode_command;
	int fd_read;
	int history_counter_row;
} sample_type;

/**
 * struct func_call - contains a function string and related function
 * @flag_name: the builtin command flag
 * @func_name: the function
 */

typedef struct func_call
{
	char *flag_name;
	int (*func_name)(sample_type *);
} function_table;

int _atoi(char *);
int _isalpha(int);
int _isdeterm(char, char *);
int play(sample_type *);

int ss_cd(sample_type *);
int ss_exit(sample_type *);
int ss_help(sample_type *);

int ss_alias(sample_type *);
int print_alias(linked_list *);
int add_alias(sample_type *, char *);
int remove_alias(sample_type *, char *);
int ss_history(sample_type *);

int ss_env(sample_type *);
int ss_add_env(sample_type *);
int ss_remove_env(sample_type *);
int linked_list_env(sample_type *);
char *env_value(sample_type *, const char *);

int character_print(char c, int fd);
int string_print(char *str, int fd);
void error_string_print(char *);
int error_putchar(char);

int decimal_print(int, int);
char *number_to_string(long int, int, int);
void remove_comments(char *);
int error_atoi(char *);
void error_print(sample_type *, char *);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

void ctrl_c(int);
ssize_t chained_buffers(sample_type *, char **, size_t *);
ssize_t read_chained_buffers(sample_type *, char *, size_t *);
ssize_t input_get_line(sample_type *);
int ss_getline(sample_type *, char **, size_t *);

char **get_environ(sample_type *);
int remove_env(sample_type *, char *);
int add_env(sample_type *, char *, char *);

void clear_func_data(sample_type *);
void add_func_data(sample_type *, char **);
void remove_func_data(sample_type *, int);

char *get_history_file(sample_type *);
int add_history(sample_type *);
int history_row(sample_type *);
int linked_list_history(sample_type *, char *, int);
int history_arrangement(sample_type *);

linked_list *add_node_start(linked_list **, const char *, int);
linked_list *add_node_end(linked_list **, const char *, int);
size_t print_linked_list(const linked_list *);
int remove_node_index(linked_list **, unsigned int);
void clear_list(linked_list **);

size_t linked_list_length(const linked_list *);
char **linked_list_array(linked_list *);
size_t print_list(const linked_list *);
linked_list *get_node_prefix(linked_list *, char *, char);
ssize_t node_index(linked_list *, linked_list *);

int clear_memory(void **);

int exe_command_checker(sample_type *, char *);
char *character_duplicate(char *, int, int);
char *find_in_dir(sample_type *, char *, char *);

char *alocate_memory(char *, char, unsigned int);
void string_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

int ss_main(sample_type *, char **);
int command_call(sample_type *);
void find_command(sample_type *);
void fork_command(sample_type *);

int string_length(char *);
int string_compare(char *, char *);
char *haystack_start(const char *, const char *);
char *string_cat(char *, char *);

char *string_copy(char *, char *);
char *string_duplicate(const char *);
void _puts(char *);
int _putchar(char);

char **string_split_2(char *, char *);
char **string_split(char *, char);

int chaining_delimeter(sample_type *, char *, size_t *);
void chaining_continue(sample_type *, char *, size_t *, size_t, size_t);
int change_ss_alias(sample_type *);
int change_ss_vars(sample_type *);
int change_string(char **, char *);

#endif
