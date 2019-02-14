/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 09:10:15 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/14 09:10:21 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_add_process(t_game *game, int champ)
{
	t_process *new;
	t_process *last;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(1); //ft_error
	ft_bzero(new, sizeof(*new));
	new->index = game->champ[champ].start_index;
	new->champ = champ;
	new->reg[1] = champ;
	new->duration_set = ft_add_duration(game, new);
	new->alive = 0;
	if (!game->process)
		game->process = new;
	else
	{
		last = game->process;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void		ft_delete_process(t_process *process, t_game *game)
{
	t_process *tmp;

	tmp = game->process;
	game->process = game->process->next;
	free (tmp);
	tmp = NULL;
}

void		ft_delete_next_process(t_process *process)
{
	t_process	*tmp;

	tmp = process->next;
	process->next = process->next->next;
	free (tmp);
	tmp = NULL;
}

void		ft_kill_process(t_game *game)
{
	t_process	*process;

	process = game->process;
	if (process && !process->alive)
	{
		ft_delete_process(process, game);
		process = game->process;
	}
	while (process && process->next)
	{
		if (!process->next->alive)
			ft_delete_next_process(process);
		process = process->next;
	}
	process = game->process;
	while (process)
	{
		process->alive = 0;
		process = process->next;
	}
}

int		ft_count_process(t_game *game)
{
	t_process 	*process;
	int			count;

	count = 0;
	process = game->process;
	while (process)
	{
		count++;
		process = process->next;
	}
	return (count);
}