# @Author: daniel_b
# @Date:   2017-08-03T16:45:05+02:00
# @Last modified by:   daniel_b
# @Last modified time: 2017-11-13T01:17:55+01:00



SRCS 	= 	main.cpp \
					Map.cpp

OBJS	=		$(SRCS:.cpp=.o)

LDFLAGS	=	-lfse -lSDL2 -lGL -lGLU -lGLEW

CPPFLAGS	=	-std=c++11 -g

NAME 	=	MyGame

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
