SRCLIST	= mlx_render.c mlx_hooks.c mlx_argb.c vector3_translate.c \
		  vector3_multiply.c vector3_rotate.c vector3_angles.c \
		  vector3_utils.c vector3_unit.c vector3_convert.c raytrace.c \
		  material.c light.c shape.c sphere.c plane.c disk.c tube.c \
		  cylinder.c texture.c perlin2.c main.c

SRCDIR	= ./

SRCS	= ${addprefix ${SRCDIR}, ${SRCLIST}}

OBJS	= ${SRCS:.c=.o}

INCS	= -iquote mlx

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

NAME	= raytrace

MAKE	= make

LIBMLX	= mlx/libmlx.a

LFLAGS	= -lm -Lmlx -lmlx -framework OpenGL -framework Appkit

all:	${NAME}

bonus:	${NAME}

.c.o:
	${CC} ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${LIBMLX}
	${CC} ${CFLAGS} ${LFLAGS} ${INCS} -o ${NAME} ${OBJS} ${LIBMLX}

${LIBMLX}:
	${MAKE} -C mlx

clean:
	${RM} ${OBJS}
	${MAKE} -C mlx clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -C mlx fclean

re:	fclean all

.PHONY:	all clean fclean re bonus
