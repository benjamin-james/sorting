CC = gcc
CFLAGS += -W -Wall -g3 -ggdb -O2
SORTING_SOURCES = build/util.o build/main.o
GEN_SOURCES = build/generate.o
DESTDIR = /
PREFIX = /usr/local

LOCATION = $(addprefix $(DESTDIR), $(addprefix $(PREFIX), /bin))
all: build sorting gen

sorting: $(SORTING_SOURCES)
	$(CC) $(CFLAGS) $(SORTING_SOURCES) -o $@
gen: $(GEN_SOURCES)
	$(CC) $(CFLAGS) $(GEN_SOURCES) -o $@

build/%.o: src/%.c build
	$(CC) $(CFLAGS) -c $< -o $@
build:
	mkdir build
clean:
	$(RM) $(SORTING_SOURCES)
	$(RM) $(GEN_SOURCES)
	$(RM) sorting
	$(RM) gen
install: sorting gen
	mkdir -p $(LOCATION)
	install -c sorting $(LOCATION)
	install -c gen $(LOCATION)
doc:
	doxygen Doxyfile
