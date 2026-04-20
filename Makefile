##
## EPITECH PROJECT, 2026
## MY-TEAMS-1
## File description:
## Makefile
##

SRC  =   $(wildcard src/*.cpp)

SRC_TESTS   =   $(wildcard tests/*.cpp)

OBJ  =   $(SRC:.cpp=.o)

NAME =   raytracer
TEST_NAME   =   unit_tests

CXXFLAGS    =   -Wall -Wextra -Iinclude -g
CPPFLAGS    =   -Iinclude

CXX         =   g++
RM          =   rm -f

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno *.gcda

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

tests_run:
	@$(RM) *.gcda *.gcno 
	$(CXX) -o $(TEST_NAME) $(SRC_TESTS) $(SRC_SERVER) $(SRC_CLI) \
		$(CXXFLAGS) -DUNIT_TEST --coverage -lcriterion $(LDFLAGS) $(LDLIBS)
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

.PHONY: all clean fclean re tests_run