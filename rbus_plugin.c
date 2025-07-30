#include <inttypes.h>
#include "google/protobuf/any.pb-c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

#include "description.pb-c.h"
#include "google/protobuf/any.pb-c.h"
#include "messages.pb-c.h"
#include "descriptor.pb-c.h"
#include "value.pb-c.h"
#include "google/protobuf/empty.pb-c.h"
#include "rbus_plugin.h"

#define SOCKET_PATH "/tmp/blizzard.sock"
#define PLUGIN_NAME "org.rdk.broadband.TR181.1"
#define READ_BUFFER_SIZE 32768


static void send_message(int sock, uint8_t *buf, size_t len) {
   write(sock, buf, len);
}

void send_property_get_response(int sock, uint64_t id) {
   Blizzard__Plugin__Messages__PropertyGetResponse resp = BLIZZARD__PLUGIN__MESSAGES__PROPERTY_GET_RESPONSE__INIT;
   resp.id = id;
   resp.status_case = BLIZZARD__PLUGIN__MESSAGES__PROPERTY_GET_RESPONSE__STATUS_ERROR;
   resp.error = "Property not found";

   Blizzard__Plugin__Messages__PluginToManagerMessage msg = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__INIT;
   msg.message_case = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__MESSAGE_PROPERTY_GET_RESPONSE;
   msg.property_get_response = &resp;

   size_t len = blizzard__plugin__messages__plugin_to_manager_message__get_packed_size(&msg);
   uint8_t *buf = malloc(len);
   if (!buf) {
      perror("malloc failed");
      return;
   }
   blizzard__plugin__messages__plugin_to_manager_message__pack(&msg, buf);

   printf("Sent property get error response for id=%" PRIu64 "\n", id);
   send_message(sock, buf, len);
   free(buf);
}

void send_property_set_response(int sock, uint64_t id) {
   Blizzard__Plugin__Messages__PropertySetResponse resp = BLIZZARD__PLUGIN__MESSAGES__PROPERTY_SET_RESPONSE__INIT;
   resp.id = id;
   resp.status_case = BLIZZARD__PLUGIN__MESSAGES__PROPERTY_SET_RESPONSE__STATUS_ERROR;
   resp.error = "Property not found";

   Blizzard__Plugin__Messages__PluginToManagerMessage msg = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__INIT;
   msg.message_case = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__MESSAGE_PROPERTY_SET_RESPONSE;
   msg.property_set_response = &resp;

   size_t len = blizzard__plugin__messages__plugin_to_manager_message__get_packed_size(&msg);
   uint8_t *buf = malloc(len);
   if (!buf) {
      perror("malloc failed");
      return;
   }
   blizzard__plugin__messages__plugin_to_manager_message__pack(&msg, buf);

   printf("Sent property set error response for id=%" PRIu64 "\n", id);
   send_message(sock, buf, len);
   free(buf);
}

static void send_registration_request(int sock) {
   // Static allocation for plugin description
   Blizzard__Plugin__Description__PluginDescription plugin_desc = BLIZZARD__PLUGIN__DESCRIPTION__PLUGIN_DESCRIPTION__INIT;

   // Static allocations for get method
   Blizzard__Plugin__Description__MethodDescription method_get = BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT;
   Google__Protobuf__Any param_any_get = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor param_schema_get = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object param_obj_get = BLIZZARD__DESCRIPTOR__OBJECT__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_get_path_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_get_path_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__List param_get_path_list = BLIZZARD__DESCRIPTOR__LIST__INIT;
   Blizzard__Descriptor__Descriptor param_get_path_list_items = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Google__Protobuf__Any result_any_get = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor result_schema_get = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__List result_list_get = BLIZZARD__DESCRIPTOR__LIST__INIT;
   Blizzard__Descriptor__Descriptor result_list_items_get = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object result_obj_get = BLIZZARD__DESCRIPTOR__OBJECT__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry result_get_key_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor result_get_key_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry result_get_value_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor result_get_value_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;

   // Static allocations for set method
   Blizzard__Plugin__Description__MethodDescription method_set = BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT;
   Google__Protobuf__Any param_any_set = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor param_schema_set = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object param_obj_set = BLIZZARD__DESCRIPTOR__OBJECT__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_set_key_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_set_key_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_set_value_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_set_value_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Google__Protobuf__Any result_any_set = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor result_schema_set = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;

   // Static allocations for invoke method
   Blizzard__Plugin__Description__MethodDescription method_invoke = BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT;
   Google__Protobuf__Any param_any_invoke = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor param_schema_invoke = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object param_obj_invoke = BLIZZARD__DESCRIPTOR__OBJECT__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_invoke_method_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_invoke_method_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_invoke_params_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_invoke_params_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__List param_invoke_params_list = BLIZZARD__DESCRIPTOR__LIST__INIT;
   Blizzard__Descriptor__Descriptor param_invoke_params_list_items = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object param_invoke_params_obj = BLIZZARD__DESCRIPTOR__OBJECT__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_invoke_params_key_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_invoke_params_key_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry param_invoke_params_value_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor param_invoke_params_value_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Google__Protobuf__Any result_any_invoke = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor result_schema_invoke = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__List result_list_invoke = BLIZZARD__DESCRIPTOR__LIST__INIT;
   Blizzard__Descriptor__Descriptor result_list_items_invoke = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object result_obj_invoke = BLIZZARD__DESCRIPTOR__OBJECT__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry result_invoke_key_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor result_invoke_key_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Blizzard__Descriptor__Object__PropertiesEntry result_invoke_value_entry = BLIZZARD__DESCRIPTOR__OBJECT__PROPERTIES_ENTRY__INIT;
   Blizzard__Descriptor__Descriptor result_invoke_value_value = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;

   // Initialize dynamic buffers
   uint8_t *param_buf_get = NULL;
   uint8_t *result_buf_get = NULL;
   uint8_t *param_buf_set = NULL;
   uint8_t *result_buf_set = NULL;
   uint8_t *param_buf_invoke = NULL;
   uint8_t *result_buf_invoke = NULL;
   uint8_t *desc_buf = NULL;
   uint8_t *buffer = NULL;

   // Initialize get method
   method_get.name = "get";
   method_get.n_permissions = 0;
   method_get.permissions = NULL;
   method_get.parameters_schema = &param_any_get;
   method_get.result_schema = &result_any_get;

   // Parameters schema for 'get': object { "path": list<string> }
   param_schema_get.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_OBJECT;
   param_schema_get.object = &param_obj_get;
   param_get_path_entry.key = "path";
   param_get_path_entry.value = &param_get_path_value;
   param_get_path_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_LIST;
   param_get_path_value.list = &param_get_path_list;
   param_get_path_list.items = &param_get_path_list_items;
   param_get_path_list_items.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_get_path_list_items.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   Blizzard__Descriptor__Object__PropertiesEntry *param_get_entries[] = {&param_get_path_entry};
   param_obj_get.n_properties = sizeof(param_get_entries) / sizeof(param_get_entries[0]);
   param_obj_get.properties = param_get_entries;

   size_t param_size_get = blizzard__descriptor__descriptor__get_packed_size(&param_schema_get);
   param_buf_get = malloc(param_size_get);
   if (!param_buf_get) {
      perror("malloc failed for param_buf_get");
      goto cleanup;
   }
   blizzard__descriptor__descriptor__pack(&param_schema_get, param_buf_get);
   param_any_get.type_url = "type.googleapis.com/blizzard.descriptor.Descriptor";
   param_any_get.value.len = param_size_get;
   param_any_get.value.data = param_buf_get;

   // Result schema for 'get': list of { "key": string, "value": string }
   result_schema_get.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_LIST;
   result_schema_get.list = &result_list_get;
   result_list_get.items = &result_list_items_get;
   result_list_items_get.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_OBJECT;
   result_list_items_get.object = &result_obj_get;
   result_get_key_entry.key = "key";
   result_get_key_entry.value = &result_get_key_value;
   result_get_key_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_get_key_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   result_get_value_entry.key = "value";
   result_get_value_entry.value = &result_get_value_value;
   result_get_value_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_get_value_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   Blizzard__Descriptor__Object__PropertiesEntry *result_get_entries[] = {&result_get_key_entry, &result_get_value_entry};
   result_obj_get.n_properties = sizeof(result_get_entries) / sizeof(result_get_entries[0]);
   result_obj_get.properties = result_get_entries;

   size_t result_size_get = blizzard__descriptor__descriptor__get_packed_size(&result_schema_get);
   result_buf_get = malloc(result_size_get);
   if (!result_buf_get) {
      perror("malloc failed for result_buf_get");
      goto cleanup;
   }
   blizzard__descriptor__descriptor__pack(&result_schema_get, result_buf_get);
   result_any_get.type_url = "type.googleapis.com/blizzard.descriptor.Descriptor";
   result_any_get.value.len = result_size_get;
   result_any_get.value.data = result_buf_get;

   // Initialize set method
   method_set.name = "set";
   method_set.n_permissions = 0;
   method_set.permissions = NULL;
   method_set.parameters_schema = &param_any_set;
   method_set.result_schema = &result_any_set;

   // Parameters schema for 'set': object { "key": string, "value": string }
   param_schema_set.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_OBJECT;
   param_schema_set.object = &param_obj_set;
   param_set_key_entry.key = "key";
   param_set_key_entry.value = &param_set_key_value;
   param_set_key_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_set_key_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   param_set_value_entry.key = "value";
   param_set_value_entry.value = &param_set_value_value;
   param_set_value_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_set_value_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   Blizzard__Descriptor__Object__PropertiesEntry *param_set_entries[] = {&param_set_key_entry, &param_set_value_entry};
   param_obj_set.n_properties = sizeof(param_set_entries) / sizeof(param_set_entries[0]);
   param_obj_set.properties = param_set_entries;

   size_t param_size_set = blizzard__descriptor__descriptor__get_packed_size(&param_schema_set);
   param_buf_set = malloc(param_size_set);
   if (!param_buf_set) {
      perror("malloc failed for param_buf_set");
      goto cleanup;
   }
   blizzard__descriptor__descriptor__pack(&param_schema_set, param_buf_set);
   param_any_set.type_url = "type.googleapis.com/blizzard.descriptor.Descriptor";
   param_any_set.value.len = param_size_set;
   param_any_set.value.data = param_buf_set;

   // Result schema for 'set': string
   result_schema_set.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_schema_set.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;

   size_t result_size_set = blizzard__descriptor__descriptor__get_packed_size(&result_schema_set);
   result_buf_set = malloc(result_size_set);
   if (!result_buf_set) {
      perror("malloc failed for result_buf_set");
      goto cleanup;
   }
   blizzard__descriptor__descriptor__pack(&result_schema_set, result_buf_set);
   result_any_set.type_url = "type.googleapis.com/blizzard.descriptor.Descriptor";
   result_any_set.value.len = result_size_set;
   result_any_set.value.data = result_buf_set;

   // Initialize invoke method
   method_invoke.name = "invoke";
   method_invoke.n_permissions = 0;
   method_invoke.permissions = NULL;
   method_invoke.parameters_schema = &param_any_invoke;
   method_invoke.result_schema = &result_any_invoke;

   // Parameters schema for 'invoke': object { "method": string, "params": list<{key: string, value: any}> }
   param_schema_invoke.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_OBJECT;
   param_schema_invoke.object = &param_obj_invoke;
   param_invoke_method_entry.key = "method";
   param_invoke_method_entry.value = &param_invoke_method_value;
   param_invoke_method_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_invoke_method_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   param_invoke_params_entry.key = "params";
   param_invoke_params_entry.value = &param_invoke_params_value;
   param_invoke_params_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_LIST;
   param_invoke_params_value.list = &param_invoke_params_list;
   param_invoke_params_list.items = &param_invoke_params_list_items;
   param_invoke_params_list_items.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_OBJECT;
   param_invoke_params_list_items.object = &param_invoke_params_obj;
   param_invoke_params_key_entry.key = "key";
   param_invoke_params_key_entry.value = &param_invoke_params_key_value;
   param_invoke_params_key_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_invoke_params_key_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   param_invoke_params_value_entry.key = "value";
   param_invoke_params_value_entry.value = &param_invoke_params_value_value;
   param_invoke_params_value_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_invoke_params_value_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__ANY;
   Blizzard__Descriptor__Object__PropertiesEntry *param_invoke_params_entries[] = {&param_invoke_params_key_entry, &param_invoke_params_value_entry};
   param_invoke_params_obj.n_properties = sizeof(param_invoke_params_entries) / sizeof(param_invoke_params_entries[0]);
   param_invoke_params_obj.properties = param_invoke_params_entries;
   Blizzard__Descriptor__Object__PropertiesEntry *param_invoke_entries[] = {&param_invoke_method_entry, &param_invoke_params_entry};
   param_obj_invoke.n_properties = sizeof(param_invoke_entries) / sizeof(param_invoke_entries[0]);
   param_obj_invoke.properties = param_invoke_entries;

   size_t param_size_invoke = blizzard__descriptor__descriptor__get_packed_size(&param_schema_invoke);
   param_buf_invoke = malloc(param_size_invoke);
   if (!param_buf_invoke) {
      perror("malloc failed for param_buf_invoke");
      goto cleanup;
   }
   blizzard__descriptor__descriptor__pack(&param_schema_invoke, param_buf_invoke);
   param_any_invoke.type_url = "type.googleapis.com/blizzard.descriptor.Descriptor";
   param_any_invoke.value.len = param_size_invoke;
   param_any_invoke.value.data = param_buf_invoke;

   // Result schema for 'invoke': list of { "key": string, "value": string }
   result_schema_invoke.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_LIST;
   result_schema_invoke.list = &result_list_invoke;
   result_list_invoke.items = &result_list_items_invoke;
   result_list_items_invoke.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_OBJECT;
   result_list_items_invoke.object = &result_obj_invoke;
   result_invoke_key_entry.key = "key";
   result_invoke_key_entry.value = &result_invoke_key_value;
   result_invoke_key_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_invoke_key_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   result_invoke_value_entry.key = "value";
   result_invoke_value_entry.value = &result_invoke_value_value;
   result_invoke_value_value.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_invoke_value_value.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__STRING;
   Blizzard__Descriptor__Object__PropertiesEntry *result_invoke_entries[] = {&result_invoke_key_entry, &result_invoke_value_entry};
   result_obj_invoke.n_properties = sizeof(result_invoke_entries) / sizeof(result_invoke_entries[0]);
   result_obj_invoke.properties = result_invoke_entries;

   size_t result_size_invoke = blizzard__descriptor__descriptor__get_packed_size(&result_schema_invoke);
   result_buf_invoke = malloc(result_size_invoke);
   if (!result_buf_invoke) {
      perror("malloc failed for result_buf_invoke");
      goto cleanup;
   }
   blizzard__descriptor__descriptor__pack(&result_schema_invoke, result_buf_invoke);
   result_any_invoke.type_url = "type.googleapis.com/blizzard.descriptor.Descriptor";
   result_any_invoke.value.len = result_size_invoke;
   result_any_invoke.value.data = result_buf_invoke;

   // Set methods array after initialization
   Blizzard__Plugin__Description__MethodDescription *methods[] = {
      &method_get,
      &method_set,
      &method_invoke
   };

   // Initialize plugin description
   plugin_desc.name = "org.rdk.broadband.TR181.1";
   plugin_desc.n_methods = sizeof(methods) / sizeof(methods[0]);
   plugin_desc.methods = methods;
   plugin_desc.n_properties = 0;
   plugin_desc.properties = NULL;
   plugin_desc.n_events = 0;
   plugin_desc.events = NULL;
   plugin_desc.n_permissions = 0;
   plugin_desc.permissions = NULL;

   // Pack plugin description
   size_t desc_size = blizzard__plugin__description__plugin_description__get_packed_size(&plugin_desc);
   desc_buf = malloc(desc_size);
   if (!desc_buf) {
      perror("malloc failed for desc_buf");
      goto cleanup;
   }
   blizzard__plugin__description__plugin_description__pack(&plugin_desc, desc_buf);

   Google__Protobuf__Any any = GOOGLE__PROTOBUF__ANY__INIT;
   any.type_url = "type.googleapis.com/blizzard.plugin.description.PluginDescription";
   any.value.len = desc_size;
   any.value.data = desc_buf;

   Blizzard__Plugin__Messages__RegistrationRequest reg_req = BLIZZARD__PLUGIN__MESSAGES__REGISTRATION_REQUEST__INIT;
   reg_req.description = &any;

   Blizzard__Plugin__Messages__PluginToManagerMessage msg = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__INIT;
   msg.message_case = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__MESSAGE_REGISTRATION_REQUEST;
   msg.registration_request = &reg_req;

   size_t total_size = blizzard__plugin__messages__plugin_to_manager_message__get_packed_size(&msg);
   buffer = malloc(total_size);
   if (!buffer) {
      perror("malloc failed for buffer");
      goto cleanup;
   }
   blizzard__plugin__messages__plugin_to_manager_message__pack(&msg, buffer);

   printf("Sent registration request (%zu bytes)\n", total_size);

   send_message(sock, buffer, total_size);

cleanup:
   free(buffer);
   free(desc_buf);
   free(result_buf_invoke);
   free(param_buf_invoke);
   free(result_buf_set);
   free(param_buf_set);
   free(result_buf_get);
   free(param_buf_get);
}

// Helper function to build key-value list for protobuf response
static bool build_keyvalue_list(KeyValuePair *results, int num_results, Blizzard__Value__Value *result_value, char **error_msg) {
   Blizzard__Value__List *result_list = malloc(sizeof(Blizzard__Value__List));
   if (!result_list) {
      *error_msg = "Malloc failed for result_list";
      return false;
   }
   blizzard__value__list__init(result_list);
   result_value->kind_case = BLIZZARD__VALUE__VALUE__KIND_LIST;
   result_value->list = result_list;

   Blizzard__Value__Value **result_elements = malloc(num_results * sizeof(Blizzard__Value__Value *));
   if (!result_elements) {
      *error_msg = "Malloc failed for result_elements";
      return false;
   }
   result_list->elements = result_elements;
   int valid_elements = 0;

   for (int i = 0; i < num_results; i++) {
      Blizzard__Value__Value *elem = malloc(sizeof(Blizzard__Value__Value));
      if (!elem) {
         *error_msg = "Malloc failed for elem";
         goto build_fail;
      }
      blizzard__value__value__init(elem);

      Blizzard__Value__Object *elem_obj = malloc(sizeof(Blizzard__Value__Object));
      if (!elem_obj) {
         *error_msg = "Malloc failed for elem_obj";
         free(elem);
         goto build_fail;
      }
      blizzard__value__object__init(elem_obj);
      elem->kind_case = BLIZZARD__VALUE__VALUE__KIND_OBJECT;
      elem->object = elem_obj;

      Blizzard__Value__Object__ChildrenEntry *key_entry = malloc(sizeof(Blizzard__Value__Object__ChildrenEntry));
      if (!key_entry) {
         *error_msg = "Malloc failed for key_entry";
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      blizzard__value__object__children_entry__init(key_entry);
      key_entry->key = strdup("key");
      if (!key_entry->key) {
         *error_msg = "strdup failed for key";
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }

      Blizzard__Value__Value *key_value = malloc(sizeof(Blizzard__Value__Value));
      if (!key_value) {
         *error_msg = "Malloc failed for key_value";
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      blizzard__value__value__init(key_value);
      key_value->kind_case = BLIZZARD__VALUE__VALUE__KIND_STRING;
      key_value->string = strdup(results[i].key);
      if (!key_value->string) {
         *error_msg = "strdup failed for key string";
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      key_entry->value = key_value;

      Blizzard__Value__Object__ChildrenEntry *value_entry = malloc(sizeof(Blizzard__Value__Object__ChildrenEntry));
      if (!value_entry) {
         *error_msg = "Malloc failed for value_entry";
         free(key_value->string);
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      blizzard__value__object__children_entry__init(value_entry);
      value_entry->key = strdup("value");
      if (!value_entry->key) {
         *error_msg = "strdup failed for value";
         free(value_entry);
         free(key_value->string);
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }

      Blizzard__Value__Value *value_value = malloc(sizeof(Blizzard__Value__Value));
      if (!value_value) {
         *error_msg = "Malloc failed for value_value";
         free(value_entry->key);
         free(value_entry);
         free(key_value->string);
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      blizzard__value__value__init(value_value);
      value_value->kind_case = BLIZZARD__VALUE__VALUE__KIND_STRING;
      size_t str_len = VALUE_TYPE_SIZE;
      if (results[i].type == VALUE_TYPE_BYTES) {
         str_len = 2 * results[i].value.bytes.len + 1;
      }
      value_value->string = malloc(str_len);
      if (!value_value->string) {
         *error_msg = "Malloc failed for value string";
         free(value_value);
         free(value_entry->key);
         free(value_entry);
         free(key_value->string);
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }

      switch (results[i].type) {
      case VALUE_TYPE_STRING:
         strncpy(value_value->string, results[i].value.string, str_len - 1);
         value_value->string[str_len - 1] = '\0';
         break;
      case VALUE_TYPE_INTEGER:
         snprintf(value_value->string, str_len, "%" PRIi64, results[i].value.integer);
         break;
      case VALUE_TYPE_DOUBLE:
         snprintf(value_value->string, str_len, "%f", results[i].value.double_val);
         break;
      case VALUE_TYPE_BOOLEAN:
         strcpy(value_value->string, results[i].value.boolean ? "true" : "false");
         break;
      case VALUE_TYPE_BYTES:
         for (size_t k = 0; k < results[i].value.bytes.len; k++) {
            snprintf(value_value->string + 2 * k, 3, "%02x", results[i].value.bytes.data[k]);
         }
         value_value->string[2 * results[i].value.bytes.len] = '\0';
         break;
      default:
         *error_msg = "Unsupported type in results";
         free(value_value->string);
         free(value_value);
         free(value_entry->key);
         free(value_entry);
         free(key_value->string);
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      value_entry->value = value_value;

      Blizzard__Value__Object__ChildrenEntry *children[] = {key_entry, value_entry};
      elem_obj->n_children = sizeof(children) / sizeof(children[0]);
      elem_obj->children = malloc(elem_obj->n_children * sizeof(Blizzard__Value__Object__ChildrenEntry *));
      if (!elem_obj->children) {
         *error_msg = "Malloc failed for children array";
         free(value_value->string);
         free(value_value);
         free(value_entry->key);
         free(value_entry);
         free(key_value->string);
         free(key_value);
         free(key_entry->key);
         free(key_entry);
         free(elem_obj);
         free(elem);
         goto build_fail;
      }
      elem_obj->children[0] = key_entry;
      elem_obj->children[1] = value_entry;

      // All succeeded, assign
      result_elements[valid_elements] = elem;
      valid_elements++;
   }

   result_list->n_elements = valid_elements;
   return true;

build_fail:
   // Cleanup partial
   for (int j = 0; j < valid_elements; j++) {
      Blizzard__Value__Value *elem = result_elements[j];
      if (elem && elem->object) {
         for (size_t k = 0; k < elem->object->n_children; k++) {
            Blizzard__Value__Object__ChildrenEntry *entry = elem->object->children[k];
            free(entry->key);
            if (entry->value) {
               free(entry->value->string);
               free(entry->value);
            }
            free(entry);
         }
         free(elem->object->children);
         free(elem->object);
         free(elem);
      }
   }
   free(result_elements);
   free(result_list);
   return false;
}

void send_invoke_response(int sock, uint64_t id, const char *method, const Google__Protobuf__Any *parameters) {
   // Static allocations for fixed Protobuf structures
   Blizzard__Plugin__Messages__InvokeResponse resp = BLIZZARD__PLUGIN__MESSAGES__INVOKE_RESPONSE__INIT;
   Blizzard__Plugin__Messages__PluginToManagerMessage msg = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__INIT;
   Google__Protobuf__Any success_any = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Value__Value result_value = BLIZZARD__VALUE__VALUE__INIT;

   // Initialize dynamic pointers
   const char **paths = NULL;
   KeyValuePair *pairs = NULL;
   KeyValuePair *in_params = NULL;
   KeyValuePair *results = NULL;
   uint8_t *packed = NULL;
   uint8_t *buf = NULL;
   char *error_msg = NULL;
   int num_params = 0;
   int num_results = 0;

   // Initialize response
   resp.id = id;

   if (strcmp(method, "get") == 0) {
      if (parameters == NULL) {
         error_msg = "No parameters provided";
      } else {
         Blizzard__Value__Value *param_value = blizzard__value__value__unpack(NULL, parameters->value.len, parameters->value.data);
         if (param_value == NULL) {
            error_msg = "Failed to unpack parameters";
         } else if (param_value->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
            error_msg = "Parameters must be an object";
         } else {
            Blizzard__Value__Object *obj = param_value->object;
            Blizzard__Value__List *path_list = NULL;

            // Extract "path" list from the object
            for (size_t i = 0; i < obj->n_children; i++) {
               if (strcmp(obj->children[i]->key, "path") == 0 &&
                  obj->children[i]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_LIST) {
                  path_list = obj->children[i]->value->list;
                  break;
               }
            }

            if (path_list == NULL) {
               error_msg = "Missing or invalid 'path' field; expected a list";
            } else {
               int num_paths = path_list->n_elements;
               if (num_paths > 0) {
                  paths = malloc(num_paths * sizeof(const char *));
                  if (!paths) {
                     error_msg = "Malloc failed for paths";
                  } else {
                     bool valid = true;
                     for (size_t j = 0; j < num_paths; j++) {
                        if (path_list->elements[j]->kind_case != BLIZZARD__VALUE__VALUE__KIND_STRING) {
                           error_msg = "All path elements must be strings";
                           valid = false;
                           break;
                        }
                        paths[j] = path_list->elements[j]->string;
                     }
                     if (!valid) {
                        free(paths);
                        paths = NULL;
                     } else {
                        rbusError_t err = rbus_get_values(paths, num_paths, &num_results, &pairs);
                        if (err != RBUS_ERROR_SUCCESS) {
                           error_msg = "rbus get failed";
                        } else {
                           if (!build_keyvalue_list(pairs, num_results, &result_value, &error_msg)) {
                              // build_keyvalue_list sets error_msg
                           }
                        }
                     }
                  }
               } else {
                  error_msg = "Empty 'path' list";
               }
            }
            blizzard__value__value__free_unpacked(param_value, NULL);
         }
      }
   } else if (strcmp(method, "set") == 0) {
      if (parameters == NULL) {
         error_msg = "No parameters provided";
      } else {
         Blizzard__Value__Value *param_value = blizzard__value__value__unpack(NULL, parameters->value.len, parameters->value.data);
         if (param_value == NULL) {
            error_msg = "Failed to unpack parameters";
         } else if (param_value->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
            error_msg = "Parameters must be an object";
         } else {
            Blizzard__Value__Object *obj = param_value->object;
            const char *key = NULL;
            const char *value = NULL;

            for (size_t i = 0; i < obj->n_children; i++) {
               if (strcmp(obj->children[i]->key, "key") == 0 &&
                  obj->children[i]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
                  key = obj->children[i]->value->string;
               } else if (strcmp(obj->children[i]->key, "value") == 0 &&
                  obj->children[i]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
                  value = obj->children[i]->value->string;
               }
            }

            if (key == NULL || value == NULL) {
               error_msg = "Missing or invalid 'key' or 'value' field";
            } else {
               rbusError_t err = rbus_set_value(key, value);
               result_value.kind_case = BLIZZARD__VALUE__VALUE__KIND_STRING;
               if (err != RBUS_ERROR_SUCCESS) {
                  error_msg = "rbus set failed";
                  result_value.string = strdup("Failed to set property");
               } else {
                  result_value.string = strdup("Success");
               }
               if (!result_value.string) {
                  error_msg = "Malloc failed for result string";
               }
            }
            blizzard__value__value__free_unpacked(param_value, NULL);
         }
      }
   } else if (strcmp(method, "invoke") == 0) {
      if (parameters == NULL) {
         error_msg = "No parameters provided";
      } else {
         Blizzard__Value__Value *param_value = blizzard__value__value__unpack(NULL, parameters->value.len, parameters->value.data);
         if (param_value == NULL) {
            error_msg = "Failed to unpack parameters";
         } else if (param_value->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
            error_msg = "Parameters must be an object";
         } else {
            Blizzard__Value__Object *obj = param_value->object;
            const char *method_name = NULL;
            Blizzard__Value__List *params_list = NULL;

            for (size_t i = 0; i < obj->n_children; i++) {
               if (strcmp(obj->children[i]->key, "method") == 0 &&
                  obj->children[i]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
                  method_name = obj->children[i]->value->string;
               } else if (strcmp(obj->children[i]->key, "params") == 0 &&
                  obj->children[i]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_LIST) {
                  params_list = obj->children[i]->value->list;
               }
            }

            if (method_name == NULL || params_list == NULL) {
               error_msg = "Missing or invalid 'method' or 'params' field";
            } else {
               num_params = params_list->n_elements;
               if (num_params > 0) {
                  in_params = malloc(num_params * sizeof(KeyValuePair));
                  if (!in_params) {
                     error_msg = "Malloc failed for input parameters";
                  } else {
                     int valid_params = 0;
                     for (size_t i = 0; i < num_params; i++) {
                        if (params_list->elements[i]->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
                           error_msg = "All params must be objects";
                           break;
                        }
                        Blizzard__Value__Object *param_obj = params_list->elements[i]->object;
                        const char *key = NULL;
                        bool has_value = false;
                        for (size_t j = 0; j < param_obj->n_children; j++) {
                           if (strcmp(param_obj->children[j]->key, "key") == 0 &&
                              param_obj->children[j]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
                              key = param_obj->children[j]->value->string;
                           } else if (strcmp(param_obj->children[j]->key, "value") == 0) {
                              has_value = true;
                              switch (param_obj->children[j]->value->kind_case) {
                              case BLIZZARD__VALUE__VALUE__KIND_STRING:
                                 in_params[valid_params].type = VALUE_TYPE_STRING;
                                 in_params[valid_params].value.string = strdup(param_obj->children[j]->value->string);
                                 break;
                              case BLIZZARD__VALUE__VALUE__KIND_INTEGER:
                                 in_params[valid_params].type = VALUE_TYPE_INTEGER;
                                 in_params[valid_params].value.integer = param_obj->children[j]->value->integer;
                                 break;
                              case BLIZZARD__VALUE__VALUE__KIND_DOUBLE:
                                 in_params[valid_params].type = VALUE_TYPE_DOUBLE;
                                 in_params[valid_params].value.double_val = param_obj->children[j]->value->double_;
                                 break;
                              case BLIZZARD__VALUE__VALUE__KIND_BOOLEAN:
                                 in_params[valid_params].type = VALUE_TYPE_BOOLEAN;
                                 in_params[valid_params].value.boolean = param_obj->children[j]->value->boolean;
                                 break;
                              case BLIZZARD__VALUE__VALUE__KIND_BYTES:
                                 in_params[valid_params].type = VALUE_TYPE_BYTES;
                                 in_params[valid_params].value.bytes.len = param_obj->children[j]->value->bytes.len;
                                 in_params[valid_params].value.bytes.data = malloc(param_obj->children[j]->value->bytes.len);
                                 if (in_params[valid_params].value.bytes.data) {
                                    memcpy(in_params[valid_params].value.bytes.data,
                                       param_obj->children[j]->value->bytes.data,
                                       param_obj->children[j]->value->bytes.len);
                                 } else {
                                    error_msg = "Malloc failed for bytes value";
                                 }
                                 break;
                              default:
                                 error_msg = "Unsupported value type in params";
                                 break;
                              }
                           }
                        }
                        if (error_msg || key == NULL || !has_value) {
                           error_msg = error_msg ? error_msg : "Invalid param object: missing 'key' or 'value'";
                           break;
                        }
                        in_params[valid_params].key = strdup(key);
                        if (!in_params[valid_params].key) {
                           error_msg = "Malloc failed for key";
                           if (in_params[valid_params].type == VALUE_TYPE_STRING) {
                              free(in_params[valid_params].value.string);
                           } else if (in_params[valid_params].type == VALUE_TYPE_BYTES) {
                              free(in_params[valid_params].value.bytes.data);
                           }
                           break;
                        }
                        valid_params++;
                     }
                     if (error_msg) {
                        num_params = valid_params;
                     } else {
                        num_params = valid_params;
                     }
                  }
               }

               if (error_msg == NULL) {
                  rbusError_t err = rbus_invoke_method(method_name, num_params, in_params, &num_results, &results);
                  if (err != RBUS_ERROR_SUCCESS) {
                     error_msg = "rbus invoke failed";
                  } else {
                     if (!build_keyvalue_list(results, num_results, &result_value, &error_msg)) {
                        // build_keyvalue_list sets error_msg
                     }
                  }
               }
            }
            blizzard__value__value__free_unpacked(param_value, NULL);
         }
      }
   } else {
      error_msg = "Unknown method";
   }

   if (error_msg == NULL) {
      size_t packed_len = blizzard__value__value__get_packed_size(&result_value);
      packed = malloc(packed_len);
      if (!packed) {
         error_msg = "Malloc failed for response packing";
      } else {
         blizzard__value__value__pack(&result_value, packed);
         success_any.type_url = strdup("type.googleapis.com/blizzard.value.Value");
         if (!success_any.type_url) {
            error_msg = "Malloc failed for type_url";
         } else {
            success_any.value.len = packed_len;
            success_any.value.data = packed;
            resp.status_case = BLIZZARD__PLUGIN__MESSAGES__INVOKE_RESPONSE__STATUS_SUCCESS;
            resp.success = &success_any;
         }
      }
   }

   if (error_msg != NULL) {
      resp.status_case = BLIZZARD__PLUGIN__MESSAGES__INVOKE_RESPONSE__STATUS_ERROR;
      resp.error = error_msg;
   }

   msg.message_case = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__MESSAGE_INVOKE_RESPONSE;
   msg.invoke_response = &resp;

   size_t len = blizzard__plugin__messages__plugin_to_manager_message__get_packed_size(&msg);
   buf = malloc(len);
   if (!buf) {
      perror("malloc failed");
      goto cleanup;
   }
   blizzard__plugin__messages__plugin_to_manager_message__pack(&msg, buf);

   printf("Sent invoke response for id=%" PRIu64 "\n", id);
   send_message(sock, buf, len);

cleanup:
   if (results) {
      for (int i = 0; i < num_results; i++) {
         free(results[i].key);
         if (results[i].type == VALUE_TYPE_STRING) {
            free(results[i].value.string);
         } else if (results[i].type == VALUE_TYPE_BYTES) {
            free(results[i].value.bytes.data);
         }
      }
      free(results);
   }
   if (in_params) {
      for (int i = 0; i < num_params; i++) {
         free(in_params[i].key);
         if (in_params[i].type == VALUE_TYPE_STRING) {
            free(in_params[i].value.string);
         } else if (in_params[i].type == VALUE_TYPE_BYTES) {
            free(in_params[i].value.bytes.data);
         }
      }
      free(in_params);
   }
   // Cleanup result_value if built
   if (result_value.kind_case == BLIZZARD__VALUE__VALUE__KIND_LIST && result_value.list) {
      for (size_t i = 0; i < result_value.list->n_elements; i++) {
         Blizzard__Value__Value *elem = result_value.list->elements[i];
         if (elem && elem->object) {
            for (size_t j = 0; j < elem->object->n_children; j++) {
               free(elem->object->children[j]->key);
               free(elem->object->children[j]->value->string);
               free(elem->object->children[j]->value);
               free(elem->object->children[j]);
            }
            free(elem->object->children);
            free(elem->object);
            free(elem);
         }
      }
      free(result_value.list->elements);
      free(result_value.list);
   } else if (result_value.kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
      free(result_value.string);
   }
   free(packed);
   free(success_any.type_url);
   free(paths);
   free(buf);
}

void handle_manager_message(int sock, uint8_t *buf, ssize_t len) {
   Blizzard__Plugin__Messages__ManagerToPluginMessage *msg =
      blizzard__plugin__messages__manager_to_plugin_message__unpack(NULL, len, buf);

   if (!msg) {
      fprintf(stderr, "Failed to unpack ManagerToPluginMessage\n");
      return;
   }

   switch (msg->message_case) {
   case BLIZZARD__PLUGIN__MESSAGES__MANAGER_TO_PLUGIN_MESSAGE__MESSAGE_REGISTRATION_RESPONSE:
      printf("Registration %s\n", msg->registration_response->status ? "successful" : "failed");
      break;

   case BLIZZARD__PLUGIN__MESSAGES__MANAGER_TO_PLUGIN_MESSAGE__MESSAGE_INVOKE_REQUEST:
      printf("Received invoke request: method = %s\n", msg->invoke_request->method);
      send_invoke_response(sock, msg->invoke_request->id, msg->invoke_request->method, msg->invoke_request->parameters);
      break;

   case BLIZZARD__PLUGIN__MESSAGES__MANAGER_TO_PLUGIN_MESSAGE__MESSAGE_PROPERTY_GET_REQUEST:
      send_property_get_response(sock, msg->property_get_request->id);
      break;

   case BLIZZARD__PLUGIN__MESSAGES__MANAGER_TO_PLUGIN_MESSAGE__MESSAGE_PROPERTY_SET_REQUEST:
      send_property_set_response(sock, msg->property_set_request->id);
      break;

   default:
      printf("Unknown manager message\n");
      break;
   }

   blizzard__plugin__messages__manager_to_plugin_message__free_unpacked(msg, NULL);
}

int main() {
   int sock;
   struct sockaddr_un addr;

   sock = socket(AF_UNIX, SOCK_STREAM, 0);
   if (sock == -1) {
      perror("socket error");
      exit(EXIT_FAILURE);
   }

   memset(&addr, 0, sizeof(struct sockaddr_un));
   addr.sun_family = AF_UNIX;
   strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

   if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
      fprintf(stderr, "failed to connect to: %s\n", SOCKET_PATH);
      close(sock);
      exit(EXIT_FAILURE);
   }

   rbus_init();

   send_registration_request(sock);

   while (1) {
      uint8_t buffer[READ_BUFFER_SIZE];
      ssize_t len = read(sock, buffer, sizeof(buffer));
      if (len <= 0) break;
      handle_manager_message(sock, buffer, len);
   }

   close(sock);
   return 0;
}
