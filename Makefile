# Makefile

# flags
CC := gcc
CFLAGS = -Wall -Wextra $(SANITIZER) -O1
LDFLAGS = $(SANITIZER)
MATH = -lm -ldl
LDLIBS = $(MATH)

FIND_O = $(subst .c,.o,$(shell find $(1) -name "*.c" -type f))
OBJ = main.o $(call FIND_O,src)

SANITIZER = -fsanitize=address
#SANITIZER =

.PHONY: all clean
.DEFAULT_GOAL := main

all: main

main: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(SDL) $(MATH) && (./$@ ; echo Exit status: $$? ; true) || echo Makefile: failed to build, launcing target aborted

clean:
	rm -rvf main $(OBJ)

# END
