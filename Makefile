##
## EPITECH PROJECT, 2026
## MY-TEAMS-1
## File description:
## Makefile
##

SRC  =  $(wildcard src/*.cpp) \
		    $(wildcard src/plugins/spacePartitionning/*.cpp) \
        $(wildcard src/plugins/renderer/*.cpp) \
        $(wildcard src/utils/*.cpp) \
        $(wildcard src/optical_effects/*.cpp) \
		    $(wildcard src/scene_loaders/*.cpp) \
        $(wildcard src/plugins/interface/*.cpp) \
        $(wildcard src/display/*.cpp)

LDLIBS      =   -lsfml-graphics -lsfml-window -lsfml-system

PRIMITIVE_SRC   =   $(wildcard src/plugins/primitives/*.cpp)
LIGHT_SRC   =   $(wildcard src/plugins/lights/*.cpp)
MATERIAL_SRC    =   $(wildcard src/plugins/Materials/*.cpp)

PLUGIN_DIR = plugins
PRIMITIVE_SO = $(patsubst src/plugins/primitives/%.cpp,$(PLUGIN_DIR)/lib%.so,$(PRIMITIVE_SRC))
LIGHT_SO = $(patsubst src/plugins/lights/%.cpp,$(PLUGIN_DIR)/lib%.so,$(LIGHT_SRC))
MATERIAL_SO = $(patsubst src/plugins/Materials/%.cpp,$(PLUGIN_DIR)/lib%.so,$(MATERIAL_SRC))
SRC_TESTS   =   $(wildcard tests/*.cpp)

OBJ  =   $(SRC:.cpp=.o)

NAME =   raytracer
TEST_NAME   =   unit_tests

CXXFLAGS    =   -Wall -Wextra -Iinclude -g -std=c++20
CPPFLAGS    =   -Iinclude
LDFLAGS     =   -rdynamic

CXX         =   g++
RM          =   rm -f

all:    $(NAME) $(PRIMITIVE_SO) $(LIGHT_SO) $(MATERIAL_SO)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)


$(PLUGIN_DIR)/lib%.so: src/plugins/primitives/%.cpp
	mkdir -p $(PLUGIN_DIR)
	$(CXX) -shared -fPIC -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(PLUGIN_DIR)/lib%.so: src/plugins/lights/%.cpp
	mkdir -p $(PLUGIN_DIR)
	$(CXX) -shared -fPIC -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(PLUGIN_DIR)/lib%.so: src/plugins/Materials/%.cpp
	mkdir -p $(PLUGIN_DIR)
	$(CXX) -shared -fPIC -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno *.gcda
	$(RM) $(PRIMITIVE_SO) $(LIGHT_SO) $(MATERIAL_SO)

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