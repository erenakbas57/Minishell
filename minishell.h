/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:30 by makbas            #+#    #+#             */
/*   Updated: 2023/09/09 16:45:32 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>

# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED 			"\033[31m"
# define LIGHT_RED 		"\033[91m"
# define GREEN 			"\033[32m"
# define LIGHT_GREEN 	"\033[92m"
# define YELLOW 		"\033[33m"
# define LIGHT_YELLOW 	"\033[93m"
# define BLUE 			"\033[34m"
# define LIGHT_BLUE 	"\033[94m"
# define MAGENTA 		"\033[35m"
# define LIGHT_MAGENTA 	"\033[95m"
# define CYAN 			"\033[36m"
# define LIGHT_CYAN 	"\033[96m"
# define WHITE 			"\033[37m"
# define GREY 			"\033[90m"
# define LIGHT_GREY 	"\033[37m"

# define BLACK_BOLD 	"\033[1;30m"
# define RED_BOLD 		"\033[1;31m"
# define GREEN_BOLD 	"\033[1;32m"
# define YELLOW_BOLD 	"\033[1;33m"
# define BLUE_BOLD 		"\033[1;34m"
# define MAGENTA_BOLD 	"\033[1;35m"
# define CYAN_BOLD 		"\033[1;36m"
# define WHITE_BOLD 	"\033[1;37m"

# define WELCOME "\033[34m\
	╔═══════════════════════════════════════════════════════════════════════╗    \n \
	║"RED"   ███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██       \033[34m║\n \
	║"RED"   ████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██       \033[34m║\n \
	║"RED"   ██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██       \033[34m║\n \
	║"RED"   ██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██       \033[34m║\n \
	║"RED"   ██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████  \033[34m║\n \
	╚═══════════════════════════════════════════════════════════════════════╝"
	
#define TRUE	1
#define FALSE			0
#define DOLLAR			'$'
#define DOUBLE_QUOTE	'"'
#define SINGLE_QUOTE	'\''
#define CHILD_PROCESS	0
#define MAIN_PROCESS	1

#define ERROR			0
#define VARIABLE		1
#define EQUAL			2
#define VALUE 3

enum	token_type
{
	PIPE = 1,
	STRING,
	HERE_DOC,
	RED_INPUT,
	RED_APPEND,
	RED_OUTPUT
};

typedef struct	s_process{
	pid_t				pid;
	int					fd[2];
	int					heredoc_fd[2];
	char				**execute;
	char				**redirects;
	struct s_process	*prev;
	struct s_process	*next;
}				t_process;

typedef struct s_export
{
	char			*str;
	struct s_export	*next;
}				t_export;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*str;
	enum token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell{
	int			process_count;
	char		**paths;
	t_env		*env;
	t_export	*export;
	t_process	*process;
	t_token		*token;
}		t_minishell;

extern	t_minishell	m_shell;

void		init_env(char **env);

// ENVIRONMENT
void		append_env(char **env);
t_env		*last_env(t_env *env);
t_env		*new_env(char *str);
void		env_add_back(t_env **env, t_env *new);
t_env		*find_env(t_env *env, char *find);

void		append_paths(void);
void		init_env(char **env);
int			count_value(char **str);

void		add_export(void);
t_export	*last_export(t_export *export);
t_export	*new_export(char *str);
void		export_add_back(t_export **export, t_export *new);
t_export	*find_export(t_export *export, char *find);

// LIBFT
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

size_t		ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);


char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char*		ft_strlcpy(char *dst, const char *src, int dstsize);

char		*ft_strdup_two(const char *str, int size, int choose);
char		*ft_strdup(const char *str);

char		*ft_strjoin_two(char const *s1);
char		*ft_strjoin(char const *s1, char const *s2);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strcmp_ex(const char *s1, const char *s2);
int			ft_strcmp_env(const char *s1, const char *s2);

void		add_declare(char **join);

// FREE
void		free_process(void);
void		free_array(char **arr);

// CONTROL
int 		is_redirects(char *str);
int			is_whitespace(char c);
int			is_char(char c);
int			is_number(char *nbr);

// TOKEN_LST
int			token_add_back(t_token **token, t_token *new, int plus);
t_token		*new_token(char *str, enum token_type type);
t_token		*last_token(t_token *token);

// TOKENIZE
void    	tokenize(char *input);
void    	parse_string(char **str);
int     	end_token_two(char *str);
void    	end_token(char **str, char type);


// LEXER_LST
t_process	*process_init();
t_process	*last_process(t_process *process);
void		process_add_back(t_process **process, t_process *new);

// LEXERIZE
int     	append_process(t_token **token, t_process *process);
char    	**add_array(char **exe_red, char *token);
int    		lexerize();
void    	free_token();

// QUOTE
char    	*clear_quote(char *token);
char    	*take_sub_text(char *str, int *i, char type);
void    	add_text(char **array, char *new);

// DOLLAR
char*   	dollar_control(char* token);
int     	quote_control(char* quote);
char*     	env_add(char* env);
int     	env_control(char* token, char** str, int* i);



// BUILTIN
int     	is_builtin(char *input);
void		run_builtin(t_process *process);

int     	b_pwd();

int     	b_cd();

int			b_exit();

void    	env_write(char* str);
int 		b_env();

int     	b_echo(char **input);

int			b_export(char **exe);
void    	show_export();
void    	new_value_export(char *new, int choose);
int     	export_control(char *str);
void    	export_update(char *upt, int choose);


#endif