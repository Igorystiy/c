CNAME=test
CC=gcc
CPOSIX= -D_FLAG_POSIX_
CFLAGS= -g -Werror -Wall -Wextra -std=c11 $(CPOSIX)
CPPCHECK_FLAGS=cppcheck --enable=all --suppress=missingIncludeSystem

all: $(CNAME)

$(CNAME): $(CNAME).o list.o
	$(CC) $(CFLAGS) $? -o $@

test.o: main.c
	$(CC) $(CFLAGS) $? -c -o $@

list.o: list.c
	$(CC) $(CFLAGS) $? -c -o $@

check: cpp_check check_style

check_style: cpp_check
	clang-format -n *.c *.h

cpp_check:
	$(CPPCHECK_FLAGS) *.c *.h

clean:
	rm -rf *.o $(CNAME)
