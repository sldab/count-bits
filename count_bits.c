#include <ctype.h>
#include "postgres.h"
#include "fmgr.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

Datum count_common_bits(PG_FUNCTION_ARGS);
Datum count_unique_bits(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(count_common_bits);
PG_FUNCTION_INFO_V1(count_unique_bits);

Datum count_common_bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);

  PG_RETURN_INT16(__builtin_popcountll(a & b));
}

Datum count_unique_bits(PG_FUNCTION_ARGS) {
  uint64_t a  = PG_GETARG_INT64(0);
  uint64_t b  = PG_GETARG_INT64(1);

  PG_RETURN_INT16(__builtin_popcountll(a ^ b));
}
