default: all
#==============================================================================#
#--------------------------------- Shell --------------------------------------#
#==============================================================================#
SHELL		:= /bin/sh
OS			 = $(shell uname)
#==============================================================================#
#------------------------------ Directories -----------------------------------#
#==============================================================================#
INCS_DIR	= includes/
SRCS_DIR	= sources/
OBJS_DIR	= obj/

#==============================================================================#
#--------------------------------- Files --------------------------------------#
#==============================================================================#
INCS_NAME	= main.h

#------------------------------------------------------------------------------#
SRCS_NAME	 = main.c
SRCS_NAME	 += utils.c
SRCS_NAME	 += ping.c
SRCS_NAME	 += logger.c

#------------------------------------------------------------------------------#
SRCS		= $(addprefix ${SRCS_DIR},${SRCS_NAME})
OBJS		= $(patsubst ${SRCS_DIR}%.c,${OBJS_DIR}%.o,${SRCS})
INCS		= $(addprefix ${INCS_DIR},${INCS_NAME})
#------------------------------------------------------------------------------#

#==============================================================================#
#--------------------------------- UNIX ---------------------------------------#
#==============================================================================#
MKDIR		= mkdir -p
RM			= rm -rf
OS			= $(shell uname)

#==============================================================================#
#-------------------------------- Compiler ------------------------------------#
#==============================================================================#
ifeq (${OS}, FreeBSD)
CC			 = cc
endif
ifeq (${OS}, Linux)
CC			 = clang
endif
ifeq (${OS}, Darwin)
CC			 = cc
endif

#------------------------------------------------------------------------------#
CFLAGS		= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Werror
CFLAGS		+= -pedantic
#------------------------------------------------------------------------------#
NAME		= ft_ping

#==============================================================================#
#--------------------------------- Rules --------------------------------------#
#==============================================================================#
${OBJS_DIR}%.o: ${SRCS_DIR}%.c $(INCS)
	${CC} -c ${CFLAGS} -o $@ $<
#------------------------------------------------------------------------------#
${OBJS_DIR}%.o: ${SRCS_DIR}%.s
#------------------------------------------------------------------------------#
${OBJS_DIR}:
	${MKDIR} ${OBJS_DIR}

#------------------------------------------------------------------------------#
${NAME}: ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
#------------------------------------------------------------------------------#
all: ${OBJS_DIR} ${NAME}
#------------------------------------------------------------------------------#
debug: CFLAGS += -glldb
debug: all
#------------------------------------------------------------------------------#
asan: CFLAGS += -glldb
asan: CFLAGS += -fsanitize=address
asan: all
#------------------------------------------------------------------------------#
msan: CFLAGS += -glldb
msan: CFLAGS += -fsanitize=memory
msan: CFLAGS += -fsanitize-memory-track-origins
msan: CFLAGS += -fno-common
msan: CFLAGS += -fno-omit-frame-pointer
msan: LFTRULE = msan
msan: all
#------------------------------------------------------------------------------#
clean:
	${RM} ${OBJS_DIR}
#------------------------------------------------------------------------------#
fclean: clean
	${RM} ${NAME}
#------------------------------------------------------------------------------#
re: fclean all
#------------------------------------------------------------------------------#
.PHONY:	all clean clean fclean re run default
#==================================== EOF =====================================#
