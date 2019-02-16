#include "vm.h"

void	ft_get_index(unsigned char	*process, int size, short *index)
{
	*index = ft_reverse_bytes(process, size);
	*index = *index % IDX_MOD;
}

void	ft_index_sum(short index1, short index2, short *total)
{
	*total = index1 + index2;
	*total = *total % IDX_MOD;
}

int		ft_index_mod(int index)
{
	if (index < 0)
		index = MEM_SIZE + index;
	return (index);
}

int		ft_move_index(int index, t_arg_type *args, int op_id)
{
	t_op	op_tab;
	int		i;

	op_tab = ft_get_op(op_id - 1);
	i = 0;
	if (op_tab.ocp)
		index++;
	while (i < op_tab.argc)
	{
		if (args[i] == REG_CODE)
			index++;
		else if (args[i] == DIR_CODE && !op_tab.dir_size)
			index += DIR_SIZE;
		else if (args[i] == DIR_CODE && op_tab.dir_size)
			index += DIR_SIZE / 2;
		else if (args[i] == IND_CODE)
			index += IND_SIZE;
		i++;
	}
	return (index);
}