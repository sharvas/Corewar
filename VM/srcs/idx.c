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