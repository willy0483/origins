CC = gcc
INCDIRS = 
OPT = -O0
CFLAGS = -Wall -Wextra -g -ggdb -pedantic $(INCDIRS) $(OPT)
LIBS = $(shell pkg-config --cflags --libs sdl3 sdl3_image cglm)

SRCDIR   = src
BUILDDIR = build

MODULES = 
CFILES = $(SRCDIR)/main.c $(foreach module,$(MODULES),$(wildcard $(SRCDIR)/$(module)/*.c))
OBJECTS = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(CFILES)))
BINARY = $(BUILDDIR)/origins

VPATH = $(dir $(CFILES))

.PHONY: all run clean debug

all: $(BINARY)

run: $(BINARY)
	$(BINARY)

$(BINARY): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)

debug: $(BINARY) 
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(BINARY)

info:
	@echo "Source files: $(CFILES)"
	@echo "Object files: $(OBJECTS)"
	@echo "Moduel folders: $(MODULES)"
	@echo "VPATH:  $(VPATH)"

