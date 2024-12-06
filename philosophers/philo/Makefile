# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryagoub <ryagoub@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 20:28:43 by ryagoub           #+#    #+#              #
#    Updated: 2024/04/25 11:53:26 by ryagoub          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFILES = philo_utils.c main.c routine.c clean_up_and_time.c
CFLAGS = -Wall -Wextra -Werror -g3 -pthread
OFILES = $(CFILES:.c=.o)
CC = cc

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
