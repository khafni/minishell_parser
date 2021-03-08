/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aksh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:31:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/02/20 15:31:55 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"

# define AKSH_TOK_BUFSIZE 64
# define AKSH_TOK_DELIM " \t\r\n\a; "

/*
    List of builtin commands, followed by their corresponding functions.
 */
// char	*builtin_str[] = {
// 	"cd",
// 	"help",
// 	"exit"
// };

// int		(*builtin_func[]) (char **) = {
// 	&aksh_cd,
// 	&aksh_help,
// 	&aksh_exit
// };

// int		aksh_num_builtins()
// {
// 	return (sizeof(builtin_str) / sizeof(char *));
// }

// /*
//     Builtin function implementations.
// */
// int		aksh_cd(char **args)
// {
// 	if (args[1] == NULL)
// 		fprintf(stderr, "aksh: expected argument to \"cd\"\n");
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 			perror("aksh");
// 	}
// 	return (1);
// }

// int		aksh_help(char **args)
// {
// 	int     i;
// 	printf("Type program names and arguments, and hit enter.\n");
// 	printf("The following are built in:\n");

// 	(void)args;
// 	i = 0;
// 	while (i < aksh_num_builtins())
// 	{
// 		printf("  %s\n", builtin_str[i]);
// 		i++;
// 	}

// 	printf("Use the man command for information on other programs.\n");
// 	return (1);
// }

// int		aksh_exit(char **args)
// {
// 	(void)args;
// 	return (0);
// }

/*
	--------------------------------------------------------------------
*/

// char	**aksh_split_line(char *line, char c)
// {
// 	int		bufsize = AKSH_TOK_BUFSIZE;
// 	int		i = 0;
// 	char	**tokens = malloc(bufsize * sizeof(char*));
// 	char	*token;

// 	if (!tokens)
// 	{
// 		fprintf(stderr, "aksh: allocation error\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	token = ft_strtok(line, AKSH_TOK_DELIM);
// 	while (token != NULL)
// 	{
// 		tokens[i] = token;
// 		i++;
// 		if (i >= bufsize)
// 		{
// 			bufsize += AKSH_TOK_BUFSIZE;
// 			tokens = realloc(tokens, bufsize * sizeof(char *));
// 			if (!tokens)
// 			{
// 				fprintf(stderr, "aksh: allocation error\n");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		token = ft_strtok(NULL, ";");
// 	}
// 	tokens[i] = NULL;
// 	return (tokens);
// }

// int		aksh_launch(char **args)
// {
// 	pid_t	pid, wpid;
// 	int		status;

// 	pid = fork();
// 	if (pid == 0)		// Child process
// 	{
// 		if (execvp(args[0], args) == -1)
// 			perror("aksh");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid < 0)	// Error forking
// 		perror("aksh");
// 	else				// Parent process
// 	{
// 		do {
// 			wpid = waitpid(pid, &status, WUNTRACED);
// 		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
// 	}
// 	return (1);
// }

// int		aksh_execute(char **args)
// {
// 	int		i;

// 	if (args[0] == NULL)	// An empty command was entered.
// 		return (1);
// 	i = 0;
// 	while (i < aksh_num_builtins())
// 	{
// 		if (strcmp(args[0], builtin_str[i]) == 0)
// 			return (*builtin_func[i])(args);
// 		i++;
// 	}
// 	return (aksh_launch(args));
// }

void	aksh_loop(void)
{
	char	*line;
	char	**args;
	// int		status;
	int		i = 0;
	int		n;

	n = 1;
	while (n != 0)
	{
		line = NULL;
		write(2, "aksh-1.0$ ", 11);
		n = get_next_line(0, &line);
		args = ft_split(line, ';');
		while (args[i])
		{
			args[i] = ft_strtrim(args[i], " ");
			printf("%s\n", args[i]);
			i++;
		}
   		// status = aksh_execute(args);
		free(args);
		free(line);
	}
}

int		main(void)
{
	aksh_loop();
	return (EXIT_SUCCESS);
}
