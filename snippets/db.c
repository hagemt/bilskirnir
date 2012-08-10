#include <assert.h>
#include <stdio.h>
#include "sqlite3.h"

int main(void) {
  sqlite3 * db;
  sqlite3_stmt * stmt;
  const char * r;
  int status;

  assert(sqlite3_open("./test.db", &db) == SQLITE_OK);
  assert(sqlite3_prepare_v2(db, "SELECT balance FROM accounts WHERE name=?;", -1, &stmt, &r) == SQLITE_OK && *r == '\0');
  assert(sqlite3_bind_text(stmt, 1, "Alice", -1, SQLITE_STATIC) == SQLITE_OK);
  fprintf(stderr, "Step: '%i'\n", status = sqlite3_step(stmt));
  assert(status == SQLITE_ROW);
  fprintf(stderr, "Result: '%i'\n", sqlite3_column_int(stmt, 0));
  assert(sqlite3_finalize(stmt) == SQLITE_OK);
  assert(sqlite3_close(db) == SQLITE_OK);
  return 0;
}
