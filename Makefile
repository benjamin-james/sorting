CC = gcc
CPPFLAGS += -D_GNU_SOURCE
CFLAGS += -W -Wall -ggdb3 -O2 -std=gnu99
LDFLAGS += -ggdb3 -O2
SORTING_SOURCES = util.o main.o sorting.o test.o tree.o input.o
GEN_SOURCES = generate.o
DESTDIR = /
PREFIX = /usr/local
INSTALL = install -c
LOCATION = $(addprefix $(DESTDIR), $(addprefix $(PREFIX), /bin))
all: sorting gen

sorting: $(SORTING_SOURCES)
	$(CC) $(LDFLAGS) $^ -o $@
gen: $(GEN_SOURCES)
	$(CC) $(LDFLAGS) $^ -o $@
%.o: src/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
clean:
	$(RM) $(SORTING_SOURCES)
	$(RM) $(GEN_SOURCES)
	$(RM) sorting
	$(RM) gen
install: sorting gen
	mkdir -p $(LOCATION)
	$(INSTALL) sorting $(LOCATION)
	$(INSTALL) gen $(LOCATION)
doc:
	doxygen Doxyfile
