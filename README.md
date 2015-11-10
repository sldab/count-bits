# count-bits

PostgreSQL extension providing simple functions for counting bits:

- `count_common_bits`:

  Counts the common bits in two 64 bit integers.

  Example:
  `count_common_bits(5,7)` will return `2`.
  ```
  5: 0000000000000000000000000000000000000000000000000000000000000101
  7: 0000000000000000000000000000000000000000000000000000000000000111
  ```
- `count_unique_bits`:

  Counts the unique bits in two 64 bit integers.
  This is also known as the Hamming distance.

  Example:
  `count_common_bits(5,7)` will return `1`.

## Implementation

The implementation relies on the `__builtin_popcountll` intrinsic available
in gcc and clang. `-march=native` is passed as a compile option. This will
use the `popcntq` instruction on newer CPUs for best performance.

Caution: Be sure to compile on the same CPU type as you are going to use in
your production system or change the `-march` parameter to a broader option.

## Installation

The PostgreSQL headers `postgres.h` and `fmgr.h` must be available for
compilation. They can be found in the `libpq-dev` package on Debian/Ubuntu or in
`postgresql-libs` on RedHat/CentOS.

Also the `pg_config` binary must be available.

Install the functions to your database with:

```
PGDATABASE=<database name> make install
```
The shared library will be copied to your PostgreSQL location for dynamically
loadable modules determined by running `pg_config --pkglibdir`.
