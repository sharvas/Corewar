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