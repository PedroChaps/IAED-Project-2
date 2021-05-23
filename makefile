CC  := gcc
CFLAGS   := -Wall -Wextra -pedantic -ansi

ifneq ($(strip $(DEBUG)), no)
    CFLAGS += -g
endif
ifneq ($(strip $(OPTIM)), no)
    CFLAGS += -O2
endif


.PHONY: all
all: proj2

proj2: $(wildcard *.c)
	$(CC) $(CFLAGS)  -o $@ $^

.PHONY: clean
clean:
	@rm -f $(OBJECTS) proj2
