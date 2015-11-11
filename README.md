# count-bits

PostgreSQL extension providing simple functions for counting bits:

- `common_1bits`:

  Counts the common 1-bits in two 64 bit integers.

  __Examples__:

      common_1bits(5,7) = 2

      5: 0000000000000000000000000000000000000000000000000000000000000101
      7: 0000000000000000000000000000000000000000000000000000000000000111

      common_1bits(7,8) = 0

      7: 0000000000000000000000000000000000000000000000000000000000000111
      8: 0000000000000000000000000000000000000000000000000000000000001000

- `unique_1bits`:

  Counts the unique 1-bits in two 64 bit integers.
  This is also known as the Hamming distance.

  __Examples__:

      unique_1bits(5,7) = 1
      unique_1bits(7,8) = 4

- `leading_common_1bits`:

  Counts the leading common 1-bits in two 64 bit integers.

  __Examples__:

      leading_common_1bits(5,7) = 0
      leading_common_1bits(7,8) = 0

- `leading_unique_1bits`:

  Counts the leading unique 1-bits in two 64 bit integers.

  __Examples__:

      leading_unique_1bits(5,7) = 0
      leading_unique_1bits(7,8) = 0

- `trailing_common_1bits`:

  Counts the trailing common 1-bits in two 64 bit integers.

  __Examples__:

      trailing_common_1bits(5,7) = 1
      trailing_common_1bits(7,8) = 0

- `trailing_unique_1bits`:

  Counts the trailing unique 1-bits in two 64 bit integers.

  __Examples__:

      trailing_unique_1bits(5,7) = 0
      trailing_unique_1bits(7,8) = 4

## Implementation

The implementation relies on the `__builtin_popcountll` and `__builtin_ctzll`
intrinsics available in gcc and clang.

`__builtin_popcountll` will use the efficient `popcntq` (popcount quick)
instruction if available and your target architecture and `__builtin_ctzll` will
use `bsfq` (bit scan forward quick).

## Installation

The PostgreSQL headers `postgres.h` and `fmgr.h` must be available for
compilation. They can be found in the `libpq-dev` package on Debian/Ubuntu or in `postgresql-libs` on RedHat/CentOS. Also the `pg_config` binary must be available.

Compile the shared library:

```
make
```

You may want to run `objdump -d count_bits.so` to make sure that the `popcntq`
instruction will be used for best performance.
If it isn't, try compiling with `make CFLAGS='-march=native'`.
Caution: The code may not run on other CPUs.

Next, install it to your PostgreSQL location for dynamically loadable modules.
You'll most likely need to be root to do this.

```
make install
```

Run the following to make all functions available in your database.
You'll most likely need to do this as the postgres user or as a user with the
necessary rights to access the database.

```
PGDATABASE=<database name> make create_functions
```
