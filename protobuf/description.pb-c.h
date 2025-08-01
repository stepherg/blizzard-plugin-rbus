/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: description.proto */

#ifndef PROTOBUF_C_description_2eproto__INCLUDED
#define PROTOBUF_C_description_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protobuf-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1005002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protobuf-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protobuf-c.
#endif

#include "google/protobuf/any.pb-c.h"

typedef struct Blizzard__Plugin__Description__PluginDescription Blizzard__Plugin__Description__PluginDescription;
typedef struct Blizzard__Plugin__Description__MethodDescription Blizzard__Plugin__Description__MethodDescription;
typedef struct Blizzard__Plugin__Description__PropertyDescription Blizzard__Plugin__Description__PropertyDescription;
typedef struct Blizzard__Plugin__Description__EventDescription Blizzard__Plugin__Description__EventDescription;


/* --- enums --- */


/* --- messages --- */

struct  Blizzard__Plugin__Description__PluginDescription
{
  ProtobufCMessage base;
  char *name;
  size_t n_methods;
  Blizzard__Plugin__Description__MethodDescription **methods;
  size_t n_properties;
  Blizzard__Plugin__Description__PropertyDescription **properties;
  size_t n_events;
  Blizzard__Plugin__Description__EventDescription **events;
  size_t n_permissions;
  char **permissions;
};
#define BLIZZARD__PLUGIN__DESCRIPTION__PLUGIN_DESCRIPTION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&blizzard__plugin__description__plugin_description__descriptor) \
, (char *)protobuf_c_empty_string, 0,NULL, 0,NULL, 0,NULL, 0,NULL }


struct  Blizzard__Plugin__Description__MethodDescription
{
  ProtobufCMessage base;
  char *name;
  Google__Protobuf__Any *parameters_schema;
  Google__Protobuf__Any *result_schema;
  size_t n_permissions;
  char **permissions;
};
#define BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&blizzard__plugin__description__method_description__descriptor) \
, (char *)protobuf_c_empty_string, NULL, NULL, 0,NULL }


struct  Blizzard__Plugin__Description__PropertyDescription
{
  ProtobufCMessage base;
  char *name;
  Google__Protobuf__Any *schema;
  protobuf_c_boolean read;
  protobuf_c_boolean write;
  size_t n_read_permissions;
  char **read_permissions;
  size_t n_write_permissions;
  char **write_permissions;
};
#define BLIZZARD__PLUGIN__DESCRIPTION__PROPERTY_DESCRIPTION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&blizzard__plugin__description__property_description__descriptor) \
, (char *)protobuf_c_empty_string, NULL, 0, 0, 0,NULL, 0,NULL }


struct  Blizzard__Plugin__Description__EventDescription
{
  ProtobufCMessage base;
  char *name;
  Google__Protobuf__Any *schema;
  size_t n_permissions;
  char **permissions;
};
#define BLIZZARD__PLUGIN__DESCRIPTION__EVENT_DESCRIPTION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&blizzard__plugin__description__event_description__descriptor) \
, (char *)protobuf_c_empty_string, NULL, 0,NULL }


/* Blizzard__Plugin__Description__PluginDescription methods */
void   blizzard__plugin__description__plugin_description__init
                     (Blizzard__Plugin__Description__PluginDescription         *message);
size_t blizzard__plugin__description__plugin_description__get_packed_size
                     (const Blizzard__Plugin__Description__PluginDescription   *message);
size_t blizzard__plugin__description__plugin_description__pack
                     (const Blizzard__Plugin__Description__PluginDescription   *message,
                      uint8_t             *out);
size_t blizzard__plugin__description__plugin_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__PluginDescription   *message,
                      ProtobufCBuffer     *buffer);
Blizzard__Plugin__Description__PluginDescription *
       blizzard__plugin__description__plugin_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   blizzard__plugin__description__plugin_description__free_unpacked
                     (Blizzard__Plugin__Description__PluginDescription *message,
                      ProtobufCAllocator *allocator);
/* Blizzard__Plugin__Description__MethodDescription methods */
void   blizzard__plugin__description__method_description__init
                     (Blizzard__Plugin__Description__MethodDescription         *message);
size_t blizzard__plugin__description__method_description__get_packed_size
                     (const Blizzard__Plugin__Description__MethodDescription   *message);
size_t blizzard__plugin__description__method_description__pack
                     (const Blizzard__Plugin__Description__MethodDescription   *message,
                      uint8_t             *out);
size_t blizzard__plugin__description__method_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__MethodDescription   *message,
                      ProtobufCBuffer     *buffer);
Blizzard__Plugin__Description__MethodDescription *
       blizzard__plugin__description__method_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   blizzard__plugin__description__method_description__free_unpacked
                     (Blizzard__Plugin__Description__MethodDescription *message,
                      ProtobufCAllocator *allocator);
/* Blizzard__Plugin__Description__PropertyDescription methods */
void   blizzard__plugin__description__property_description__init
                     (Blizzard__Plugin__Description__PropertyDescription         *message);
size_t blizzard__plugin__description__property_description__get_packed_size
                     (const Blizzard__Plugin__Description__PropertyDescription   *message);
size_t blizzard__plugin__description__property_description__pack
                     (const Blizzard__Plugin__Description__PropertyDescription   *message,
                      uint8_t             *out);
size_t blizzard__plugin__description__property_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__PropertyDescription   *message,
                      ProtobufCBuffer     *buffer);
Blizzard__Plugin__Description__PropertyDescription *
       blizzard__plugin__description__property_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   blizzard__plugin__description__property_description__free_unpacked
                     (Blizzard__Plugin__Description__PropertyDescription *message,
                      ProtobufCAllocator *allocator);
/* Blizzard__Plugin__Description__EventDescription methods */
void   blizzard__plugin__description__event_description__init
                     (Blizzard__Plugin__Description__EventDescription         *message);
size_t blizzard__plugin__description__event_description__get_packed_size
                     (const Blizzard__Plugin__Description__EventDescription   *message);
size_t blizzard__plugin__description__event_description__pack
                     (const Blizzard__Plugin__Description__EventDescription   *message,
                      uint8_t             *out);
size_t blizzard__plugin__description__event_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__EventDescription   *message,
                      ProtobufCBuffer     *buffer);
Blizzard__Plugin__Description__EventDescription *
       blizzard__plugin__description__event_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   blizzard__plugin__description__event_description__free_unpacked
                     (Blizzard__Plugin__Description__EventDescription *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Blizzard__Plugin__Description__PluginDescription_Closure)
                 (const Blizzard__Plugin__Description__PluginDescription *message,
                  void *closure_data);
typedef void (*Blizzard__Plugin__Description__MethodDescription_Closure)
                 (const Blizzard__Plugin__Description__MethodDescription *message,
                  void *closure_data);
typedef void (*Blizzard__Plugin__Description__PropertyDescription_Closure)
                 (const Blizzard__Plugin__Description__PropertyDescription *message,
                  void *closure_data);
typedef void (*Blizzard__Plugin__Description__EventDescription_Closure)
                 (const Blizzard__Plugin__Description__EventDescription *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor blizzard__plugin__description__plugin_description__descriptor;
extern const ProtobufCMessageDescriptor blizzard__plugin__description__method_description__descriptor;
extern const ProtobufCMessageDescriptor blizzard__plugin__description__property_description__descriptor;
extern const ProtobufCMessageDescriptor blizzard__plugin__description__event_description__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_description_2eproto__INCLUDED */
