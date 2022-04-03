#include "db_adaptor.h"
#include <stdlib.h>
#include "leveldb/c.h"


struct db_adaptor* create_db() {
  struct db_adaptor *adaptor = malloc(sizeof(struct db_adaptor));
  leveldb_t *db;
  leveldb_options_t *options;
  char *err = NULL;
  
  options = leveldb_options_create();
  leveldb_options_set_create_if_missing(options, 1);
  db = leveldb_open(options, "testdb3", &err);

  if (err != NULL) {
    fprintf(err, "Open fail.\n");
    return(1);
  }

  adaptor->db = db;

  return adaptor;
}
