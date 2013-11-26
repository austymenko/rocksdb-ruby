#include "rocksdb/db.h"
#include <iostream>

extern "C" {

#include <stdio.h>
#include <ruby.h>
  
  typedef VALUE (*METHOD)(...);
  
  VALUE rocksdb_init(int argc, VALUE* argv, VALUE self);
  VALUE rocksdb_put(int argc, VALUE* argv, VALUE self);
  VALUE rocksdb_get(VALUE self, VALUE v_key);
  VALUE rocksdb_write(int argc, VALUE* argv, VALUE self);
  VALUE rocksdb_merge(int argc, VALUE* argv, VALUE self);
  VALUE rocksdb_delete(int argc, VALUE* argv, VALUE self);
  
  
  rocksdb::DB* db;

  void Init_RocksDB(){
    
    VALUE cRocksdb;
    
    cRocksdb = rb_define_class("RocksDB", rb_cObject);
    rb_define_private_method(cRocksdb, "initialize", (METHOD)rocksdb_init, -1);
    rb_define_method(cRocksdb, "Put", (METHOD)rocksdb_put, -1);
    rb_define_method(cRocksdb, "Get", (METHOD)rocksdb_get, 1);
    rb_define_method(cRocksdb, "Write", (METHOD)rocksdb_write, -1);
    rb_define_method(cRocksdb, "Merge", (METHOD)rocksdb_merge, -1);
    rb_define_method(cRocksdb, "Delete", (METHOD)rocksdb_delete, -1);
  }

  VALUE rocksdb_init(int argc, VALUE* argv, VALUE self) {
    VALUE v_db_file_name;
    rb_scan_args(argc, argv, "01", &v_db_file_name);
    Check_Type(v_db_file_name, T_STRING);
    std::string db_file_name = std::string((char*)RSTRING_PTR(v_db_file_name));
    
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, db_file_name, &db);

    return status.ok() ? Qtrue : Qfalse;
  }

  VALUE rocksdb_put(int argc, VALUE* argv, VALUE self) {
    VALUE v_key, v_value, v_options;
 
    rb_scan_args(argc, argv, "21", &v_key, &v_value, &v_options);
    Check_Type(v_key, T_STRING);
    Check_Type(v_value, T_STRING);

    std::string key = std::string((char*)RSTRING_PTR(v_key));
    std::string value = std::string((char*)RSTRING_PTR(v_value));

    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    
    std::cout<<  value << std::endl;
    return status.ok() ? Qtrue : Qfalse;
  }

  VALUE rocksdb_get(VALUE self, VALUE v_key){
    Check_Type(v_key, T_STRING);

    std::string key = std::string((char*)RSTRING_PTR(v_key));
    std::string value;
    db->Get(rocksdb::ReadOptions(), key, &value);    

    return rb_str_new(value.data(), value.size());
  }

  VALUE rocksdb_write(int argc, VALUE* argv, VALUE self){
    std::cout<<  ("Hello, Ruby World.\n");
    return Qnil;
  }
  VALUE rocksdb_merge(int argc, VALUE* argv, VALUE self){
    std::cout<<  ("Hello, Ruby World.\n");
    return Qnil;
  }
  VALUE rocksdb_delete(int argc, VALUE* argv, VALUE self){
    std::cout<<  ("Hello, Ruby World.\n");
    return Qnil;
  }
}
