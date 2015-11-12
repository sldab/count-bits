#include <ctype.h>
#include "postgres.h"
#include "fmgr.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

Datum common_1bits(PG_FUNCTION_ARGS);
Datum unique_1bits(PG_FUNCTION_ARGS);
Datum leading_common_1bits(PG_FUNCTION_ARGS);
Datum trailing_common_1bits(PG_FUNCTION_ARGS);
Datum leading_common_bits(PG_FUNCTION_ARGS);
Datum leading_unique_bits(PG_FUNCTION_ARGS);
Datum trailing_common_bits(PG_FUNCTION_ARGS);
Datum trailing_unique_bits(PG_FUNCTION_ARGS);


PG_FUNCTION_INFO_V1(common_1bits);
PG_FUNCTION_INFO_V1(unique_1bits);
PG_FUNCTION_INFO_V1(leading_common_1bits);
PG_FUNCTION_INFO_V1(trailing_common_1bits);
PG_FUNCTION_INFO_V1(leading_common_bits);
PG_FUNCTION_INFO_V1(leading_unique_bits);
PG_FUNCTION_INFO_V1(trailing_common_bits);
PG_FUNCTION_INFO_V1(trailing_unique_bits);


Datum common_1bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);

  PG_RETURN_INT16(__builtin_popcountll(a & b));
}

Datum unique_1bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);

  PG_RETURN_INT16(__builtin_popcountll(a ^ b));
}

Datum leading_common_1bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);
  PG_RETURN_INT16(__builtin_clzll(~(a & b)));
}

Datum trailing_common_1bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);
  PG_RETURN_INT16(__builtin_ctzll(~(a & b)));
}

Datum leading_common_bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);
  PG_RETURN_INT16(__builtin_clzll(a ^ b));
}

Datum trailing_common_bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);
  PG_RETURN_INT16(__builtin_ctzll(a ^ b));
}

Datum leading_unique_bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);
  PG_RETURN_INT16(__builtin_clzll(~(a ^ b)));
}

Datum trailing_unique_bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);
  PG_RETURN_INT16(__builtin_ctzll(~(a ^ b)));
}
