/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: description.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "description.pb-c.h"
void   blizzard__plugin__description__plugin_description__init
                     (Blizzard__Plugin__Description__PluginDescription         *message)
{
  static const Blizzard__Plugin__Description__PluginDescription init_value = BLIZZARD__PLUGIN__DESCRIPTION__PLUGIN_DESCRIPTION__INIT;
  *message = init_value;
}
size_t blizzard__plugin__description__plugin_description__get_packed_size
                     (const Blizzard__Plugin__Description__PluginDescription *message)
{
  assert(message->base.descriptor == &blizzard__plugin__description__plugin_description__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t blizzard__plugin__description__plugin_description__pack
                     (const Blizzard__Plugin__Description__PluginDescription *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &blizzard__plugin__description__plugin_description__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t blizzard__plugin__description__plugin_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__PluginDescription *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &blizzard__plugin__description__plugin_description__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Blizzard__Plugin__Description__PluginDescription *
       blizzard__plugin__description__plugin_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Blizzard__Plugin__Description__PluginDescription *)
     protobuf_c_message_unpack (&blizzard__plugin__description__plugin_description__descriptor,
                                allocator, len, data);
}
void   blizzard__plugin__description__plugin_description__free_unpacked
                     (Blizzard__Plugin__Description__PluginDescription *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &blizzard__plugin__description__plugin_description__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   blizzard__plugin__description__method_description__init
                     (Blizzard__Plugin__Description__MethodDescription         *message)
{
  static const Blizzard__Plugin__Description__MethodDescription init_value = BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT;
  *message = init_value;
}
size_t blizzard__plugin__description__method_description__get_packed_size
                     (const Blizzard__Plugin__Description__MethodDescription *message)
{
  assert(message->base.descriptor == &blizzard__plugin__description__method_description__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t blizzard__plugin__description__method_description__pack
                     (const Blizzard__Plugin__Description__MethodDescription *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &blizzard__plugin__description__method_description__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t blizzard__plugin__description__method_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__MethodDescription *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &blizzard__plugin__description__method_description__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Blizzard__Plugin__Description__MethodDescription *
       blizzard__plugin__description__method_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Blizzard__Plugin__Description__MethodDescription *)
     protobuf_c_message_unpack (&blizzard__plugin__description__method_description__descriptor,
                                allocator, len, data);
}
void   blizzard__plugin__description__method_description__free_unpacked
                     (Blizzard__Plugin__Description__MethodDescription *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &blizzard__plugin__description__method_description__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   blizzard__plugin__description__property_description__init
                     (Blizzard__Plugin__Description__PropertyDescription         *message)
{
  static const Blizzard__Plugin__Description__PropertyDescription init_value = BLIZZARD__PLUGIN__DESCRIPTION__PROPERTY_DESCRIPTION__INIT;
  *message = init_value;
}
size_t blizzard__plugin__description__property_description__get_packed_size
                     (const Blizzard__Plugin__Description__PropertyDescription *message)
{
  assert(message->base.descriptor == &blizzard__plugin__description__property_description__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t blizzard__plugin__description__property_description__pack
                     (const Blizzard__Plugin__Description__PropertyDescription *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &blizzard__plugin__description__property_description__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t blizzard__plugin__description__property_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__PropertyDescription *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &blizzard__plugin__description__property_description__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Blizzard__Plugin__Description__PropertyDescription *
       blizzard__plugin__description__property_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Blizzard__Plugin__Description__PropertyDescription *)
     protobuf_c_message_unpack (&blizzard__plugin__description__property_description__descriptor,
                                allocator, len, data);
}
void   blizzard__plugin__description__property_description__free_unpacked
                     (Blizzard__Plugin__Description__PropertyDescription *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &blizzard__plugin__description__property_description__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   blizzard__plugin__description__event_description__init
                     (Blizzard__Plugin__Description__EventDescription         *message)
{
  static const Blizzard__Plugin__Description__EventDescription init_value = BLIZZARD__PLUGIN__DESCRIPTION__EVENT_DESCRIPTION__INIT;
  *message = init_value;
}
size_t blizzard__plugin__description__event_description__get_packed_size
                     (const Blizzard__Plugin__Description__EventDescription *message)
{
  assert(message->base.descriptor == &blizzard__plugin__description__event_description__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t blizzard__plugin__description__event_description__pack
                     (const Blizzard__Plugin__Description__EventDescription *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &blizzard__plugin__description__event_description__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t blizzard__plugin__description__event_description__pack_to_buffer
                     (const Blizzard__Plugin__Description__EventDescription *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &blizzard__plugin__description__event_description__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Blizzard__Plugin__Description__EventDescription *
       blizzard__plugin__description__event_description__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Blizzard__Plugin__Description__EventDescription *)
     protobuf_c_message_unpack (&blizzard__plugin__description__event_description__descriptor,
                                allocator, len, data);
}
void   blizzard__plugin__description__event_description__free_unpacked
                     (Blizzard__Plugin__Description__EventDescription *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &blizzard__plugin__description__event_description__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor blizzard__plugin__description__plugin_description__field_descriptors[5] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__PluginDescription, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "methods",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Blizzard__Plugin__Description__PluginDescription, n_methods),
    offsetof(Blizzard__Plugin__Description__PluginDescription, methods),
    &blizzard__plugin__description__method_description__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "properties",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Blizzard__Plugin__Description__PluginDescription, n_properties),
    offsetof(Blizzard__Plugin__Description__PluginDescription, properties),
    &blizzard__plugin__description__property_description__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "events",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Blizzard__Plugin__Description__PluginDescription, n_events),
    offsetof(Blizzard__Plugin__Description__PluginDescription, events),
    &blizzard__plugin__description__event_description__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "permissions",
    5,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Blizzard__Plugin__Description__PluginDescription, n_permissions),
    offsetof(Blizzard__Plugin__Description__PluginDescription, permissions),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned blizzard__plugin__description__plugin_description__field_indices_by_name[] = {
  3,   /* field[3] = events */
  1,   /* field[1] = methods */
  0,   /* field[0] = name */
  4,   /* field[4] = permissions */
  2,   /* field[2] = properties */
};
static const ProtobufCIntRange blizzard__plugin__description__plugin_description__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor blizzard__plugin__description__plugin_description__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "blizzard.plugin.description.PluginDescription",
  "PluginDescription",
  "Blizzard__Plugin__Description__PluginDescription",
  "blizzard.plugin.description",
  sizeof(Blizzard__Plugin__Description__PluginDescription),
  5,
  blizzard__plugin__description__plugin_description__field_descriptors,
  blizzard__plugin__description__plugin_description__field_indices_by_name,
  1,  blizzard__plugin__description__plugin_description__number_ranges,
  (ProtobufCMessageInit) blizzard__plugin__description__plugin_description__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor blizzard__plugin__description__method_description__field_descriptors[4] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__MethodDescription, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "parameters_schema",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__MethodDescription, parameters_schema),
    &google__protobuf__any__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "result_schema",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__MethodDescription, result_schema),
    &google__protobuf__any__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "permissions",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Blizzard__Plugin__Description__MethodDescription, n_permissions),
    offsetof(Blizzard__Plugin__Description__MethodDescription, permissions),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned blizzard__plugin__description__method_description__field_indices_by_name[] = {
  0,   /* field[0] = name */
  1,   /* field[1] = parameters_schema */
  3,   /* field[3] = permissions */
  2,   /* field[2] = result_schema */
};
static const ProtobufCIntRange blizzard__plugin__description__method_description__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor blizzard__plugin__description__method_description__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "blizzard.plugin.description.MethodDescription",
  "MethodDescription",
  "Blizzard__Plugin__Description__MethodDescription",
  "blizzard.plugin.description",
  sizeof(Blizzard__Plugin__Description__MethodDescription),
  4,
  blizzard__plugin__description__method_description__field_descriptors,
  blizzard__plugin__description__method_description__field_indices_by_name,
  1,  blizzard__plugin__description__method_description__number_ranges,
  (ProtobufCMessageInit) blizzard__plugin__description__method_description__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor blizzard__plugin__description__property_description__field_descriptors[6] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__PropertyDescription, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "schema",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__PropertyDescription, schema),
    &google__protobuf__any__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "read",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__PropertyDescription, read),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "write",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__PropertyDescription, write),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "read_permissions",
    5,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Blizzard__Plugin__Description__PropertyDescription, n_read_permissions),
    offsetof(Blizzard__Plugin__Description__PropertyDescription, read_permissions),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "write_permissions",
    6,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Blizzard__Plugin__Description__PropertyDescription, n_write_permissions),
    offsetof(Blizzard__Plugin__Description__PropertyDescription, write_permissions),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned blizzard__plugin__description__property_description__field_indices_by_name[] = {
  0,   /* field[0] = name */
  2,   /* field[2] = read */
  4,   /* field[4] = read_permissions */
  1,   /* field[1] = schema */
  3,   /* field[3] = write */
  5,   /* field[5] = write_permissions */
};
static const ProtobufCIntRange blizzard__plugin__description__property_description__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor blizzard__plugin__description__property_description__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "blizzard.plugin.description.PropertyDescription",
  "PropertyDescription",
  "Blizzard__Plugin__Description__PropertyDescription",
  "blizzard.plugin.description",
  sizeof(Blizzard__Plugin__Description__PropertyDescription),
  6,
  blizzard__plugin__description__property_description__field_descriptors,
  blizzard__plugin__description__property_description__field_indices_by_name,
  1,  blizzard__plugin__description__property_description__number_ranges,
  (ProtobufCMessageInit) blizzard__plugin__description__property_description__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor blizzard__plugin__description__event_description__field_descriptors[3] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__EventDescription, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "schema",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Blizzard__Plugin__Description__EventDescription, schema),
    &google__protobuf__any__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "permissions",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Blizzard__Plugin__Description__EventDescription, n_permissions),
    offsetof(Blizzard__Plugin__Description__EventDescription, permissions),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned blizzard__plugin__description__event_description__field_indices_by_name[] = {
  0,   /* field[0] = name */
  2,   /* field[2] = permissions */
  1,   /* field[1] = schema */
};
static const ProtobufCIntRange blizzard__plugin__description__event_description__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor blizzard__plugin__description__event_description__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "blizzard.plugin.description.EventDescription",
  "EventDescription",
  "Blizzard__Plugin__Description__EventDescription",
  "blizzard.plugin.description",
  sizeof(Blizzard__Plugin__Description__EventDescription),
  3,
  blizzard__plugin__description__event_description__field_descriptors,
  blizzard__plugin__description__event_description__field_indices_by_name,
  1,  blizzard__plugin__description__event_description__number_ranges,
  (ProtobufCMessageInit) blizzard__plugin__description__event_description__init,
  NULL,NULL,NULL    /* reserved[123] */
};
