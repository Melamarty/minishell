int	read_heredoc(char *limiter, t_data *data)
{
	int		fd[2];
	char	*buffer;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(limiter, "\n");
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		i = 0;
		buffer = get_next_line(0);
		if (!buffer)
			return (free(tmp), close(fd[0]), close(fd[1]), fd[0]);
		if (!ft_strncmp(buffer, tmp, ft_strlen(tmp) + 1))
			return (free(buffer), free(tmp), close(fd[1]), fd[0]);
		write(fd[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (0);
}