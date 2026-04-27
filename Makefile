##
## EPITECH PROJECT, 2026
## MY-TEAMS-1
## File description:
## Makefile
##

SRC  =   $(wildcard src/*.cpp) \
        $(wildcard src/objects/*.cpp) \
        $(wildcard src/plugins/renderer/*.cpp) \
        $(wildcard src/utils/*.cpp) \
		$(wildcard src/scene_loaders/*.cpp)


PRIMITIVE_SRC   =   $(wildcard src/plugins/primitives/*.cpp)
# LIGHT_SRC   =   $(wildcard src/plugins/lights/*.cpp)
# MATERIAL_SRC    =   $(wildcard src/plugins/materials/*.cpp)


PLUGIN_DIR = plugins
# Générer un .so par primitive automatiquement
PRIMITIVE_SO = $(patsubst src/plugins/primitives/%.cpp,$(PLUGIN_DIR)/lib%.so,$(PRIMITIVE_SRC))
# LIGHT_SO = $(PLUGIN_DIR)/liblight.so
# MATERIAL_SO = $(PLUGIN_DIR)/libmaterial.so

SRC_TESTS   =   $(wildcard tests/*.cpp)

OBJ  =   $(SRC:.cpp=.o)

NAME =   raytracer
TEST_NAME   =   unit_tests

CXXFLAGS    =   -Wall -Wextra -Iinclude -g
CPPFLAGS    =   -Iinclude

CXX         =   g++
RM          =   rm -f

all:    $(NAME) $(PRIMITIVE_SO)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)


# Règle générique pour chaque .so de primitive
$(PLUGIN_DIR)/lib%.so: src/plugins/primitives/%.cpp
	mkdir -p $(PLUGIN_DIR)
	$(CXX) -shared -fPIC -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

##$(LIGHT_SO): $(LIGHT_SRC)
#	mkdir -p $(PLUGIN_DIR)
#	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS) $(CPPFLAGS)
#
#$(MATERIAL_SO): $(MATERIAL_SRC)
#	mkdir -p $(PLUGIN_DIR)
#	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS) $(CPPFLAGS)


clean:
	$(RM) $(OBJ)
	$(RM) *.gcno *.gcda
	$(RM) $(PRIMITIVE_SO)

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