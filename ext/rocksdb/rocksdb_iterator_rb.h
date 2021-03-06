#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"

extern "C" {

#include <ruby.h>
  
  typedef VALUE (*METHOD)(...);

  VALUE rocksdb_iterator_seek_to_first(VALUE klass);
  VALUE rocksdb_iterator_seek_to_last(VALUE klass);
  VALUE rocksdb_iterator_seek(VALUE klass, VALUE v_target);
  VALUE rocksdb_iterator_alloc(VALUE klass);
  VALUE rocksdb_iterator_valid(VALUE klass);
  VALUE rocksdb_iterator_key(VALUE klass);
  VALUE rocksdb_iterator_value(VALUE klass);
  VALUE rocksdb_iterator_next(VALUE klass);
  VALUE rocksdb_iterator_close(VALUE klass);

} 
 
