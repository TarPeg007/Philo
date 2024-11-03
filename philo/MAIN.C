
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*str;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)dest;
	str = (const unsigned char *)src;
	if (ptr > str)
	{
		while (n--)
		{
			ptr[n] = str[n];
		}
	}
	else
	{
		while (i < n)
		{
			ptr[i] = str[i];
			i++;
		}
	}
	return (dest);
}
int main()
{
    char destt[9];
    char const *drcc = "hello man wekfmekwfmew";
    ft_memmove(destt,drcc,8);
    printf("%s",destt);
}