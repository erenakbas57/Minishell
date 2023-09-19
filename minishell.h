/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:30 by makbas            #+#    #+#             */
/*   Updated: 2023/09/19 16:41:05 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define BLACK_BOLD 	"\033[1;30m"
# define RED_BOLD 		"\033[1;31m"
# define GREEN_BOLD 	"\033[1;32m"
# define YELLOW_BOLD 	"\033[1;33m"
# define BLUE_BOLD 		"\033[1;34m"
# define MAGENTA_BOLD 	"\033[1;35m"
# define CYAN_BOLD 		"\033[1;36m"
# define WHITE_BOLD 	"\033[1;37m"

# define TRUE			1
# define FALSE			0
# define DOLLAR			'$'
# define DOUBLE_QUOTE	'"'
# define SINGLE_QUOTE	'\''
# define CHILD_PROCESS	0
# define MAIN_PROCESS	1
# define REPLACE 1
# define APPEND 0

# define ERROR			0
# define VARIABLE		1
# define EQUAL			2
# define VALUE			3

enum e_token_type
{
	PIPE = 1,
	STRING = 2,
	HERE_DOC = 3,
	RED_INPUT = 4,
	RED_APPEND = 5,
	RED_OUTPUT = 6
};

typedef struct s_process
{
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
	char				*str;
	enum e_token_type	type;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_minishell
{
	int			process_count;
	int			parent_pid;
	int			ignore;
	char		**paths;
	char		**envo;
	t_env		*env;
	t_export	*export;
	t_process	*process;
	t_token		*token;
}		t_minishell;

t_minishell	g_mshell;

//main.c
void		init_env(char **env);
void	wait_cmd(void);
void	start_cmd(void);
void	launch_ms(char *input);

// add_environment.c
void		append_env(char **env);
int			count_value(char **str);
void		append_export(void);
void		append_paths(void);
char		**append_envo();


//lst_env.c
t_env		*new_env(char *str);
void		env_add_back(t_env **env, t_env *new);
t_env		*find_env(t_env *env, char *find);

//lst_export.c
t_export	*new_export(char *str);
void		export_add_back(t_export **export, t_export *new);
t_export	*find_export(t_export *export, char *find);

//libft
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strlcpy(char *dst, const char *src, int dstsize);

char		*ft_strdup_two(const char *str, int size, int choose);
char		*ft_strdup(const char *str);

char		*ft_strjoin_two(char const *s1);
char		*ft_strjoin(char const *s1, char const *s2);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strcmp(const char *s1, const char *s2);
int			ft_strcmp_ex(const char *s1, const char *s2);
int			ft_strcmp_env(const char *s1, const char *s2);

//is_Redirects.c
int			is_redirects(char *str);
int			is_whitespace(char c);
int			is_char(char c);
int			is_number(char *nbr);

//signals.c
void		ctrl_c(int sig);
void		ctrl_d(char *input);

//free.c

void		free_process(void);
void		free_array(char **arr);
void		free_token(void);

//error.c
void		token_error(int type);
void		command_error(char *str);
void		directory_error(char *str);
void		nofile_error(char *str);
int			is_parent(void);





//tokenize.c
void		tokenize(char *input);
void		parse_string(char **str);
int			end_token_two(char *str);
void		end_token(char **str, char type);

//token_lst.c
int			token_add_back(t_token **token, t_token *new, int plus);
t_token		*new_token(char *str, enum e_token_type type);


//process_lst.c
t_process	*new_process(void);
void		process_add_back(t_process **process, t_process *new);

//lexerize.c
int			append_process(t_token **token, t_process *process);
char		**add_array(char **exe_red, char *token);
int			lexerize(void);

//quote.c
char		*clear_quote(char *token);
char		*take_sub_text(char *str, int *i, char type);
void		add_text(char **array, char *new);
char		*take_text(char *str, int *i);

//dollar.c
char		*dollar_control(char *token);
int			quote_control(char *quote);
char		*env_add(char *env);
int			env_control(char *token, char **str, int *i);

//builtin.c
int			is_builtin(char *input);
void		run_builtin(t_process *process);

//builtin
int			b_pwd(void);
int			b_cd(void);
int			b_exit(void);

//env.c
int			b_env(void);
void		env_write(char *str);

//export.c
int			b_export(char **exe);
void		show_export(void);
void		new_value_export(char *new, int choose);
int			export_control(char *str);
void		update_export(char *upt, int choose);

//unset.c
int			b_unset(char **exe);
void		export_lst_delone(char *str);
void		env_lst_delone(char *str);

//cmd.c
void		run_cmd(t_process *process);
void 		get_builtin(t_process *process);


int			b_echo(char **input);
int	echo_parameter(char **prm);
void	put_char(char *input);


//hreredoc.c
void	is_heredoc(void);
void	start_heredoc(int *heredoc_fd, char *end_str);
void	close_heredoc(int sig);


//fd.c
int	contain_heredoc(t_process *process);
void	close_heredoc_fd(t_process *process);
void	close_all_fd(void);

//redirect.c
void 	get_inputs(t_process *process);
void	set_outputs(t_process *process);



//path.c
char	*get_path(char *cmd);
void	check_dir(char *cmd);


#endif