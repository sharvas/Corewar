#include "vm.h"

void	ft_get_index(unsigned char	*process, int size, short *index)
{
	int sign;

	sign = 1;
	*index = ft_reverse_bytes(process, size);
	if (index < 0)
	{
		sign = -1;
		*index = -(*index);
	}
	*index = (*index % IDX_MOD) * sign;
}

void	ft_index_sum(short index1, short index2, short *total)
{
	int sign;

	sign = 1;
	*total = index1 + index2;
	if (*total < 0)
	{
		sign = -1;
		*total = -(*total);
	}
	*total = (*total % IDX_MOD) * sign;
}