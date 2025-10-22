# Variables pour la compilation
CC = g++
CFLAGS = $(shell pkg-config --cflags armadillo) -Wall -Werror -g -O2
LDLIBS = $(shell pkg-config --libs armadillo) -llapack -lblas
SDIR = src
HDIR = lib
BDIR = bin
TDIR = test
TARGET = $(BDIR)/main
TEST_TARGET = $(BDIR)/test_runner

# Variables pour Doxygen
DOXYGEN = doxygen
DOXYFILE = doc/Doxyfile
DOCDIR = doc/html

# Sources, objets, et fichiers de test
SRCS = $(wildcard $(SDIR)/*.cpp)
OBJS = $(patsubst $(SDIR)/%.cpp, $(BDIR)/%.o, $(filter-out $(SDIR)/main.cpp, $(SRCS)))
ALL_OBJS = $(wildcard $(BDIR)/*)
TEST_HEADERS = $(wildcard $(TDIR)/test_*.h)

RUNNER_CPP = $(BDIR)/runner.cpp
RUNNER_OBJ = $(BDIR)/runner.o

# Compilation principale
all: $(TARGET)

$(TARGET): $(OBJS) $(BDIR)/main.o | $(BDIR)
	$(CC) $(OBJS) $(BDIR)/main.o -o $(TARGET) $(LDLIBS)

$(BDIR)/main.o: $(SDIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SDIR)/main.cpp -o $@

# Génération et compilation des tests avec CxxTest
$(RUNNER_CPP): $(TEST_HEADERS)
	cxxtestgen --error-printer -o $(RUNNER_CPP) $(TEST_HEADERS)

$(RUNNER_OBJ): $(RUNNER_CPP)
	$(CC) $(CFLAGS) -c $(RUNNER_CPP) -o $@

tests: $(TEST_TARGET)

$(TEST_TARGET): $(RUNNER_OBJ) $(OBJS) | $(BDIR)
	$(CC) $(RUNNER_OBJ) $(OBJS) -o $(TEST_TARGET) $(LDLIBS)

$(BDIR)/%.o: $(SDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BDIR):
	mkdir -p $(BDIR)

# Génération de la documentation avec Doxygen
.PHONY: doc
doc:
	@echo "Génération de la documentation avec Doxygen..."
	$(DOXYGEN) $(DOXYFILE)
	@echo "La documentation HTML a été générée dans $(DOCDIR)"

# Nettoyage des fichiers objets, binaires, et documentation
.PHONY: clean
clean:
	rm -f $(OBJS) $(RUNNER_OBJ) $(TARGET) $(TEST_TARGET) $(RUNNER_CPP) $(ALL_OBJS) 
	rm -rf $(DOCDIR)
	rm output.txt output_graph.png
