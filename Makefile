CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include
SRCDIR = src
OBJDIR = obj
TESTDIR = tests

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = nordvm

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET)

repl: $(TARGET)
	./$(TARGET) -repl

test: $(TARGET) test_run

test_run: tests/test_lexer
	./tests/test_lexer

tests/test_lexer: $(SRCS) tests/test_lexer.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all dirs clean repl test test_run