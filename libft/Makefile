NAME = libft.a

HEADER = Includes/libft.h

SRC_DIR = SRC
LIBFT_DIR = $(SRC_DIR)/libft


SRCS =	$(LIBFT_DIR)/ft_atoi.c \
		$(LIBFT_DIR)/ft_bzero.c \
		$(LIBFT_DIR)/ft_calloc.c \
		$(LIBFT_DIR)/ft_isalnum.c \
		$(LIBFT_DIR)/ft_isalpha.c \
		$(LIBFT_DIR)/ft_isascii.c \
		$(LIBFT_DIR)/ft_isdigit.c \
		$(LIBFT_DIR)/ft_isprint.c \
		$(LIBFT_DIR)/ft_itoa.c \
		$(LIBFT_DIR)/ft_memchr.c \
		$(LIBFT_DIR)/ft_memcmp.c \
		$(LIBFT_DIR)/ft_memcpy.c \
		$(LIBFT_DIR)/ft_memmove.c \
		$(LIBFT_DIR)/ft_memset.c \
		$(LIBFT_DIR)/ft_putchar_fd.c \
		$(LIBFT_DIR)/ft_putendl_fd.c \
		$(LIBFT_DIR)/ft_putnbr_fd.c \
		$(LIBFT_DIR)/ft_putstr_fd.c \
		$(LIBFT_DIR)/ft_split.c \
		$(LIBFT_DIR)/ft_strdup.c \
		$(LIBFT_DIR)/ft_striteri.c \
		$(LIBFT_DIR)/ft_strlcat.c \
		$(LIBFT_DIR)/ft_strlcpy.c \
		$(LIBFT_DIR)/ft_strlen.c \
		$(LIBFT_DIR)/ft_strmapi.c \
		$(LIBFT_DIR)/ft_strncmp.c \
		$(LIBFT_DIR)/ft_strnstr.c \
		$(LIBFT_DIR)/ft_strtrim.c \
		$(LIBFT_DIR)/ft_substr.c \
		$(LIBFT_DIR)/ft_tolower.c \
		$(LIBFT_DIR)/ft_toupper.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I Includes
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re