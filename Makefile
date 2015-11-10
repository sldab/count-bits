CC=cc
#CFLAGS = -fPIC -march=native -O3 -Wall
INC = -I$(shell pg_config --includedir-server)

PG_CONFIG = pg_config
PGXS = $(shell $(PG_CONFIG) --pgxs)
INCLUDEDIR = $(shell $(PG_CONFIG) --includedir-server)
PKGLIBDIR = $(shell $(PG_CONFIG) --pkglibdir)
include $(PGXS)

all: count_bits.so

count_bits.so: count_bits.o
	$(CC) -shared -o count_bits.so count_bits.o

count_bits.o: count_bits.c
	$(CC) $(CFLAGS) -march=native -I$(INCLUDEDIR) -c count_bits.c

copy: count_bits.so
	cp count_bits.so $(PKGLIBDIR)

install: copy
	psql -c \
		"CREATE OR REPLACE FUNCTION count_common_bits(bigint, bigint) RETURNS int \
		 AS 'count_bits', 'count_common_bits' LANGUAGE C STRICT; \
		 CREATE OR REPLACE FUNCTION count_unique_bits(bigint, bigint) RETURNS int \
		 AS 'count_bits', 'count_unique_bits' LANGUAGE C STRICT;"

delete:
	rm -f $(PKGLIBDIR)/count_bits.so

uninstall: delete
	psql -c \
		"DROP FUNCTION IF EXISTS count_common_bits(bigint, bigint); \
		 DROP FUNCTION IF EXISTS count_unique_bits(bigint, bigint);"

clean:
	rm -f *.so *.o
