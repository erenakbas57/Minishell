/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:30 by makbas            #+#    #+#             */
/*   Updated: 2023/08/23 09:08:24 by makbas           ###   ########.fr       */
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

# define RESET	    "\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"


#define TRUE           1
#define FALSE          0
#define DOLLAR         '$'
#define DOUBLE_QUOTE   '"'
#define SINGLE_QUOTE   '\''
#define CHILD_PROCESS  0
#define MAIN_PROCESS   1
#define REPLACE        1
#define APPEND         0

enum token_type
{
	PIPE        = 1, // |
	STRING, // char *
	HERE_DOC, // <<
	RED_INPUT, // <
	RED_APPEND, // >>
	RED_OUTPUT
};

typedef struct s_process{
	pid_t				pid;
	int					fd[2];			// input ve output dosyası (SOR)
	int					heredoc_fd[2];	// (SOR)
	char				**execute;		// execute kısmı
	char				**redirects;	// > & >> işaretlerini ve sonraki dosyayı tutuyor tutuyor
	struct s_process	*prev;			// önceki process
	struct s_process	*next;			// sonraki **
}				t_process;

typedef struct s_token
{
	char			*str;
	enum token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;


typedef struct s_minishell{
	char		**paths;
	char		**env;
	t_process	*process;
    t_token     *token;
	
}       t_minishell;

extern t_minishell	m_shell;

void		init_env(char **env);


// ENVIRONMENT
void		append_env(char **env);
void    	append_paths();

// LIBFT
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *str);
size_t		ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char*		ft_strlcpy(char *dst, const char *src, int dstsize);

// CONTROL
int 		is_redirects(char *str);
int			is_whitespace(char c);
int			is_char(char c);

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
#endif