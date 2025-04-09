Target = btc

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp BitcoinExchange.cpp

OBJS = ${SRCS:.cpp=.o}

RM = rm -rf

all : ${Target}

${Target} : ${OBJS}
		${CXX} ${CXXFLAGS} -o ${Target} ${OBJS}

%.o:%.cpp
		${CXX} ${CXXFLAGS} -c $< -o $@

clean :
		${RM} ${OBJS}

fclean : clean
		${RM} ${Target}

re : fclean all

.PHONY : all clean fclean re
