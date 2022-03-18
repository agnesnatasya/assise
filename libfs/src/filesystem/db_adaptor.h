#ifndef DBADAPTOR_H_
#define DBADAPTOR_H_

#include "leveldb/c.h"

struct db_adaptor {
  leveldb_t *db;
};

struct db_adaptor* create_db();

#endif