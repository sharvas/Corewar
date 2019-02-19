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

void		add_process(t_game *game, int champ)
{
	t_process *new;
	t_process *last;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		error_exit("Malloc fail in add_process", game);
	ft_bzero(new, sizeof(*new));
	new->index = game->champ[champ].start_index;
	new->champ = champ;
	new->reg[1] = champ;
	new->duration_set = add_duration(game, new);
	new->alive = 0;
	if (!game->process)
		game->process = new;
	else
	{
		last = game->process;
		game->process = new;
		game->process->next = last;
	}
}

static void	ft_delete_process(t_game *game)
{
	t_process *tmp;

	tmp = game->process;
	game->process = game->process->next;
	free(tmp);
	tmp = NULL;
}

static void	ft_delete_next_process(t_process *process)
{
	t_process	*tmp;

	tmp = process->next;
	process->next = process->next->next;
	free(tmp);
	tmp = NULL;
}

static void	reset_process_live(t_game *game)
{
	t_process	*process;

	process = game->process;
	while (process)
	{
		process->alive = 0;
		process = process->next;
	}
}

void		check_process(t_game *game)
{
	t_process	*process;
	int			killed;

	killed = 0;
	while (game->process && !game->process->alive)
	{
		ft_delete_process(game);
		killed++;
	}
	process = game->process;
	while (process && process->next)
	{
		if (!process->next->alive)
		{
			ft_delete_next_process(process);
			killed++;
		}
		process = process->next;
	}
	reset_process_live(game);
	if (game->flag_v && killed == 1 && game->flag_w < game->cycle_count)
		system("say kill");
	else if (game->flag_v && killed > 1 && game->flag_w < game->cycle_count)
		system("say massacre");
}
