#include <stdio.h>
#include <string.h>
#include "malloc.h"

int	main(void)
{
	char	*tiny;
	char	*small;
	char	*large;

	tiny = malloc(42);
	small = malloc(1024);
	large = malloc(1024 * 1024);
	printf("tiny=%p small=%p large=%p\n", tiny, small, large);
	if (tiny)
		strcpy(tiny, "hola");
	tiny = realloc(tiny, 128);
	printf("realloc tiny=%p -> \"%s\"\n", tiny, tiny ? tiny : "(null)");
	show_alloc_mem();
	free(tiny);
	free(small);
	free(large);
	free(NULL);
	show_alloc_mem();
	return (0);
}
