#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>

# define ALIGN16(x)    (((x) + 15) & ~(size_t)15)
# define TINY_MAX      128
# define BLK_HDR       ALIGN16(sizeof(t_block))
# define ZONE_HDR      ALIGN16(sizeof(t_zone))
# define TINY_SLOT     (BLK_HDR + TINY_MAX)

typedef struct s_zone {
	struct s_zone	*next;
	size_t			size;
	int				type;
}	t_zone;

typedef struct s_block {
	struct s_block	*next;
	size_t			size;
	int				type;
}	t_block;

extern t_zone			*g_zones;
extern pthread_mutex_t	g_lock;

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

#endif
