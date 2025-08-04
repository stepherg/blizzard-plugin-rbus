#ifndef RBUS_PLUGIN_H
#define RBUS_PLUGIN_H

#include <rbus.h>
#include <stdint.h>

typedef enum {
   VALUE_TYPE_STRING,
   VALUE_TYPE_INTEGER,
   VALUE_TYPE_DOUBLE,
   VALUE_TYPE_BOOLEAN,
   VALUE_TYPE_BYTES
} ValueType;

typedef struct {
   char* key;
   ValueType type;
   union {
      char* string;
      int64_t integer;
      double double_val;
      bool boolean;
      struct {
         uint8_t* data;
         size_t len;
      } bytes;
   } value;
} KeyValuePair;

void rbus_init(void);
rbusError_t rbus_get_values(const char** propertyNames, int numProperties, int* numPairs, KeyValuePair** pairs);
rbusError_t rbus_set_value(const char* propertyName, const char* val_str);
rbusError_t rbus_invoke_method(const char* methodName, int numParams, KeyValuePair* inParams, int* numResults, KeyValuePair** results);

#define VALUE_TYPE_SIZE 32

#endif