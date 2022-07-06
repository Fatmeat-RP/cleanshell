/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:01:21 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/06 17:13:35 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ****************************************************************************
-----------------------------------INCLUDES-----------------------------------
* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>

/* ****************************************************************************
------------------------------------DEFINE-----------------------------------
* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define REDIR_IN_FLAG 1

# define REDIR_OUT_FLAG 2

# define HERE_DOC_FLAG 3

# define REDIR_OUT_ADD_FLAG 4

# define CMD_FLAG 5

# define ARGS_FLAG 6

# define PIPE_FLAG 7

# define EMPTY_LINE 8

# define SIMPLE_QUOTE 10

# define DOUBLE_QUOTE 11

# define PARSE_ERROR 12

# define PIPE_ERROR 13

# define FILE_NAME 14

# define DELIM_NAME 15

# define BUILTIN_FLAG 16

# define LAST_PIPE_STATUS 17

/* ****************************************************************************
-------------------------------------ENUM-------------------------------------
* ************************************************************************** */

typedef enum s_bool
{
	false,
	true
}			t_bool;

/* ****************************************************************************
------------------------------------STRUCT------------------------------------
* ************************************************************************** */

typedef struct s_var
{
	char			*varname;
	char			*value;
	struct s_var	*start;
	struct s_var	*next;
}				t_var;

typedef struct s_instance
{
	char	**envp;
	char	*prompt;
	char	*line;
}				t_instance;

typedef struct s_execution
{
	char	**cmd;
	char	*in;
	char	*out;
	t_bool	is_pipe;
	void	*next;
}				t_exec;

typedef struct s_parsing
{
	char	*elem;
	int		flag;
	size_t	pos_dol;
	char	*varname;
	void	*next;
}				t_parse;

typedef struct s_control_parse
{
	t_parse	*first;
	t_parse	*iter;
	t_parse	*size;
}				t_control_parse;

typedef struct s_exec_control
{
	t_exec	*first;
	t_exec	*iter;
	t_exec	*size;
}				t_exec_control;

/* ****************************************************************************
-----------------------------PROTOTYPES FUNCTIONS-----------------------------
* ************************************************************************** */

t_control_parse		*parsing(char *line, char **envp);
int					parsing_printer(t_control_parse *parse_list);
t_bool				first_check(char *line);
t_bool				check_empty_line(char *line);
t_bool				check_last_pipe(char *line);
t_bool				check_last_chev(char *line);
t_bool				check_first_pipe(char *line);
size_t				ft_strlen(char *s);
t_bool				check_quote(char *line);
char				**ft_split_it(char *line, char c, size_t i, int q);
int					tote(char c, int q);
t_bool				check_consec_pipe(char *line);
char				*ft_strdup(char *s1);
t_control_parse		*split_block(char *elem, int x);
void				splitter(t_control_parse *parsing, t_control_parse *rep);
void				tab_cleaner(char **tab);
void				flaggeur_redir(t_control_parse *parsing);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				flaggeur_file_name(t_control_parse *parsing);
void				cut_redir(t_control_parse *parsing);
void				universal_flaggeur(t_control_parse *parsing);
void				check_multi_chev(t_control_parse *parsing);
void				check_multi_node_chev(t_control_parse *parsing);
void				check_no_file_name(t_control_parse *parsing);
t_bool				printer_error(t_control_parse *parsing);
t_var				*set_var(char **env);
t_var				*fill_var(t_var *var, char **env);
t_var				*dispatch_var(t_var *var);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strjoin(char *s1, char *s2);
void				dollar(t_control_parse *parsing, char **env);
int					quote_supp(t_control_parse *parsing);

/* ****************************************************************************
----------------------------INCLUDES FUNCTIONS LST----------------------------
* ************************************************************************** */

t_exec_control		*exec_last(t_exec_control *lst);
t_parse				*parse_last(t_control_parse *lst);
void				parse_add_back(t_control_parse *lst, t_parse *add);
void				parse_add_just_back(t_control_parse *lst, t_parse *add);
void				exec_add_back(t_exec_control *lst, t_exec *add);
t_exec				*init_exe(void);
t_exec_control		*init_exec_control(void);
t_parse				*init_parse(char *elem, float flag);
t_control_parse		*init_control_parse(void);
size_t				ft_strlen(char *s);
t_control_parse		*set_parseur(t_control_parse *parsing, char **line_tab, char **envp);
void				cleaner(t_control_parse *parsing);
t_control_parse		*parse(t_control_parse *parsing, size_t x, char **env);
void				var_clear(t_var **var);

#endif
