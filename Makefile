# @Author: daniel_b
# @Date:   2017-08-03T16:45:05+02:00
# @Last modified by:   daniel_b
# @Last modified time: 2017-09-12T23:08:56+02:00



SRCS 	= 	main.cpp \
					Map.cpp

OBJS	=		$(SRCS:.cpp=.o)

LDFLAGS	=	-lmxe -lSDL2 -lGL -lGLU -lGLEW

CPPFLAGS	=	-std=c++11 -I../MyEngine -g

NAME 	=	MyGame

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
