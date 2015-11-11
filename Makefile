CC = cc
INC = -I$(shell pg_config --includedir-server)

PG_CONFIG = pg_config
PGXS = $(shell $(PG_CONFIG) --pgxs)
INCLUDEDIR = $(shell $(PG_CONFIG) --includedir-server)
PKGLIBDIR = $(shell $(PG_CONFIG) --pkglibdir)

CREATE_FUNCTION = CREATE OR REPLACE FUNCTION $(1)(bigint, bigint) \
	RETURNS int AS 'count_bits', '$(1)' LANGUAGE C STRICT;

DROP_FUNCTION = DROP FUNCTION IF EXISTS $(1)(bigint, bigint);

include $(PGXS)

all: count_bits.so

count_bits.so: count_bits.o
	$(CC) -shared -o count_bits.so count_bits.o

count_bits.o: count_bits.c
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -c count_bits.c

install: count_bits.so
	cp count_bits.so $(PKGLIBDIR)
	chmod 644 $(PKGLIBDIR)/count_bits.so

create_functions: install
	psql -c "\
		$(call CREATE_FUNCTION,common_1bits) \
		$(call CREATE_FUNCTION,unique_1bits) \
		$(call CREATE_FUNCTION,leading_common_1bits) \
		$(call CREATE_FUNCTION,leading_unique_1bits) \
		$(call CREATE_FUNCTION,trailing_common_1bits) \
		$(call CREATE_FUNCTION,trailing_unique_1bits)"

uninstall: drop_functions
	rm -f $(PKGLIBDIR)/count_bits.so

drop_functions:
	psql -c "\
		$(call DROP_FUNCTION,common_1bits) \
		$(call DROP_FUNCTION,unique_1bits) \
		$(call DROP_FUNCTION,leading_common_1bits) \
		$(call DROP_FUNCTION,leading_unique_1bits) \
		$(call DROP_FUNCTION,trailing_common_1bits) \
		$(call DROP_FUNCTION,trailing_unique_1bits)"

clean:
	rm -f *.so *.o
