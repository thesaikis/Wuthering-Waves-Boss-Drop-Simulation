CC = clang
CFLAGS = -Wall -Werror -Wextra -Werror -std=c99
SRCDIR = src
INCDIR = include
BUILDDIR = build
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
EXEC = calc

all: $(BUILDDIR) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(EXEC)

.PHONY: all clean