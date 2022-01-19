.PHONY: all clean fclean re
NAME = minitalk
SRCS_SERVER = server.c
SRCS_CLIENT = client.c ft_atoi.c
OBJS_SERVER = ${SRCS_SERVER:.c=.o}
OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
SERVER = server
CLIENT = client
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_SERVER)
		$(CC) -o $(SERVER) $(OBJS_SERVER)

$(CLIENT): $(OBJS_CLIENT)
		$(CC) -o $(CLIENT) $(OBJS_CLIENT)

clean:
	${RM} ${OBJS_CLIENT} ${OBJS_SERVER}

fclean: clean
	${RM} ${CLIENT} ${SERVER}

re: fclean all
