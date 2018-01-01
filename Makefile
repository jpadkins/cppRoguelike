###############################################################################
# Filename:       Makefile
# Author:         Jacob P Adkins (github.com/jpadkins)
###############################################################################

.SILENT:

CMAKE_DIR = build
EXEC = bin/roguelike

all: $(EXEC)

run: $(EXEC)
	$^

$(EXEC): $(wildcard src/*.cpp)
	cd $(CMAKE_DIR) && $(MAKE)

cmake: CMakeLists.txt
	cd $(CMAKE_DIR) && cmake ..

check: $(EXEC)
	valgrind --leak-check=full --suppressions=suppressions.supp $^

clean:
	rm -rf $(EXEC)
