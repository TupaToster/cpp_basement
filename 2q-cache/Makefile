# Var for compiler
CC=g++

# Compiler flags i guess
CFLAGS=-std=c++20 -fpermissive

# auto generated directories for .o and .d files (deleted on make clean)
OBJDIR=_objs/
DEPSDIR=_deps/

# error file
ERRFL=_err.log

EXECEXT=lol

ifeq ($(OS), Windows_NT)
	EXECEXT=.exe
else
	EXECEXT=.out
endif

# This is just some debug-related pieces of code that i like to take with me when starting any new project
LIB=lib.cpp

TEST=tester.cpp
PERF=perfect_cache.cpp

TEST_OUT=$(TEST:.cpp=$(EXECEXT))
PERF_OUT=$(PERF:.cpp=$(EXECEXT))

# "make" scenario
all: $(ERRFL) $(DEPSDIR) $(OBJDIR) $(ERRFL) $(TEST_OUT)

# include all dependency files (i don't know how it works, so don't change)
-include $(addprefix $(DEPSDIR),*.d)

# generates .o and .d files from all .cpp files in call dir (works funny, don't change - will break)
$(OBJDIR)%.o: %.cpp
	$(CC) -M $(CFLAGS) $< -o $(DEPSDIR)$(@F:.o=.d) 2>> $(ERRFL)
	echo '' >> $(ERRFL)
	echo "$(OBJDIR)" > line.tmp
	mv $(DEPSDIR)$(@F:.o=.d) input.tmp
	head -c -1 -q line.tmp input.tmp > $(DEPSDIR)$(@F:.o=.d)
	rm input.tmp line.tmp
	$(CC) -c $(CFLAGS) $< -o $@ 2>> $(ERRFL)
	echo '' >> $(ERRFL)


# change stuff from here...

$(TEST_OUT): $(addprefix $(OBJDIR), $(TEST:.cpp=.o) $(LIB:.cpp=.o))
	$(CC) $(CFLAGS) $< -o $@ 2>> $(ERRFL)

# ... to here


# create _err.log (actually rm this file to clean it)
$(ERRFL):
	rm -rf $(ERRFL)

# create _deps
$(DEPSDIR):
	mkdir $(DEPSDIR)

# create _objs
$(OBJDIR):
	mkdir $(OBJDIR)

# erases unneeded files !(includes .exe and .out)!
clean:
	rm -rf $(DEPSDIR) $(OBJDIR) $(ERRFL)
	rm -rf *.exe* *.png *.dot *.o *.out
	clear

.PHONY: clean $(ERRFL)