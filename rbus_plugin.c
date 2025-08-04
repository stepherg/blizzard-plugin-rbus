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
#define READ_BUFFER_SIZE 8192

static void send_message(int sock, uint8_t* buf, size_t len) {
   uint32_t net_len = htonl(len);
   if (write(sock, &net_len, sizeof(net_len)) != sizeof(net_len)) {
      perror("write length failed");
      return;
   }
   if (write(sock, buf, len) != (ssize_t)len) {
      perror("write data failed");
   }
}

static ssize_t recv_message(int sock, uint8_t* buf, size_t max_len) {
   uint32_t net_len;
   ssize_t n = read(sock, &net_len, sizeof(net_len));
   if (n == 0) {
      fprintf(stderr, "Connection closed by peer\n");
      return -1;
   }
   if (n < 0) {
      perror("read length failed");
      return -1;
   }
   if (n != sizeof(net_len)) {
      fprintf(stderr, "Partial length read (%zd bytes)\n", n);
      return -1;
   }
   size_t len = ntohl(net_len);

   if (len > max_len) {
      fprintf(stderr, "Error: recv_message len: %zu exceeds max_len: %zu\n", len, max_len);
      return -1;
   }

   return read(sock, buf, len);
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
   uint8_t* buf = malloc(len);
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
   uint8_t* buf = malloc(len);
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

   // Static allocations for set method
   Blizzard__Plugin__Description__MethodDescription method_set = BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT;
   Google__Protobuf__Any param_any_set = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor param_schema_set = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Google__Protobuf__Any result_any_set = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor result_schema_set = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;

   // Static allocations for invoke method
   Blizzard__Plugin__Description__MethodDescription method_invoke = BLIZZARD__PLUGIN__DESCRIPTION__METHOD_DESCRIPTION__INIT;
   Google__Protobuf__Any param_any_invoke = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor param_schema_invoke = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;
   Google__Protobuf__Any result_any_invoke = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Descriptor__Descriptor result_schema_invoke = BLIZZARD__DESCRIPTOR__DESCRIPTOR__INIT;

   // Initialize dynamic buffers
   uint8_t* param_buf_get = NULL;
   uint8_t* result_buf_get = NULL;
   uint8_t* param_buf_set = NULL;
   uint8_t* result_buf_set = NULL;
   uint8_t* param_buf_invoke = NULL;
   uint8_t* result_buf_invoke = NULL;
   uint8_t* desc_buf = NULL;
   uint8_t* buffer = NULL;

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
   Blizzard__Descriptor__Object__PropertiesEntry* param_get_entries[] = {&param_get_path_entry};
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

   // Result schema for 'get': any_object
   result_schema_get.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_schema_get.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__ANY_OBJECT;

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

   // Parameters schema for 'set': any_object
   param_schema_set.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_schema_set.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__ANY_OBJECT;

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

   // Parameters schema for 'invoke': any_object
   param_schema_invoke.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   param_schema_invoke.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__ANY_OBJECT;
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

   // Result schema for 'invoke': any_object
   result_schema_invoke.kind_case = BLIZZARD__DESCRIPTOR__DESCRIPTOR__KIND_BASIC;
   result_schema_invoke.basic = BLIZZARD__DESCRIPTOR__BASIC_TYPES__ANY_OBJECT;

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
   Blizzard__Plugin__Description__MethodDescription* methods[] = {
      &method_get,
      &method_set,
      &method_invoke
   };

   // Initialize plugin description
   plugin_desc.name = PLUGIN_NAME;
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

// Helper function to serialize a Blizzard__Value__Object to a simple string
static char* serialize_object_to_string(Blizzard__Value__Object* obj) {
   // Simple stringification: create a string with key-value pairs
   // For production, consider a proper JSON library if needed
   size_t total_len = 2; // For "{}"
   for (size_t i = 0; i < obj->n_children; i++) {
      total_len += strlen(obj->children[i]->key) + 3; // key + ":" + quotes
      switch (obj->children[i]->value->kind_case) {
         case BLIZZARD__VALUE__VALUE__KIND_STRING:
            total_len += strlen(obj->children[i]->value->string) + 2; // quotes
            break;
         case BLIZZARD__VALUE__VALUE__KIND_INTEGER:
            total_len += 20; // Enough for a 64-bit integer
            break;
         case BLIZZARD__VALUE__VALUE__KIND_DOUBLE:
            total_len += 32; // Enough for a double
            break;
         case BLIZZARD__VALUE__VALUE__KIND_BOOLEAN:
            total_len += 6; // "true" or "false"
            break;
         case BLIZZARD__VALUE__VALUE__KIND_BYTES:
            total_len += obj->children[i]->value->bytes.len * 2 + 2; // Hex string + quotes
            break;
         case BLIZZARD__VALUE__VALUE__KIND_OBJECT:
            total_len += 32; // Placeholder for nested object
            break;
         default:
            total_len += 10; // Fallback for unknown types
      }
      total_len += 2; // For ", " or closing brace
   }

   char* result = malloc(total_len);
   if (!result) return NULL;
   result[0] = '{';
   size_t offset = 1;

   for (size_t i = 0; i < obj->n_children; i++) {
      offset += snprintf(result + offset, total_len - offset, "\"%s\":", obj->children[i]->key);
      switch (obj->children[i]->value->kind_case) {
         case BLIZZARD__VALUE__VALUE__KIND_STRING:
            offset += snprintf(result + offset, total_len - offset, "\"%s\"", obj->children[i]->value->string);
            break;
         case BLIZZARD__VALUE__VALUE__KIND_INTEGER:
            offset += snprintf(result + offset, total_len - offset, "%" PRId64, obj->children[i]->value->integer);
            break;
         case BLIZZARD__VALUE__VALUE__KIND_DOUBLE:
            offset += snprintf(result + offset, total_len - offset, "%g", obj->children[i]->value->double_);
            break;
         case BLIZZARD__VALUE__VALUE__KIND_BOOLEAN:
            offset += snprintf(result + offset, total_len - offset, "%s", obj->children[i]->value->boolean ? "true" : "false");
            break;
         case BLIZZARD__VALUE__VALUE__KIND_BYTES: {
            // Convert bytes to hex string
            for (size_t j = 0; j < obj->children[i]->value->bytes.len && offset < total_len - 3; j++) {
               offset += snprintf(result + offset, total_len - offset, "%02x", obj->children[i]->value->bytes.data[j]);
            }
            break;
         }
         case BLIZZARD__VALUE__VALUE__KIND_OBJECT:
            offset += snprintf(result + offset, total_len - offset, "\"[object]\""); // Placeholder
            break;
         default:
            offset += snprintf(result + offset, total_len - offset, "\"unknown\"");
      }
      if (i < obj->n_children - 1) {
         offset += snprintf(result + offset, total_len - offset, ",");
      }
   }
   snprintf(result + offset, total_len - offset, "}");
   return result;
}

// Helper function to build key-value object for protobuf response
static bool build_keyvalue_object(KeyValuePair* results, int num_results, Blizzard__Value__Value* result_value, char** error_msg) {
   Blizzard__Value__Object* result_obj = malloc(sizeof(Blizzard__Value__Object));
   if (!result_obj) {
      *error_msg = "Malloc failed for result_obj";
      return false;
   }
   blizzard__value__object__init(result_obj);
   result_value->kind_case = BLIZZARD__VALUE__VALUE__KIND_OBJECT;
   result_value->object = result_obj;

   Blizzard__Value__Object__ChildrenEntry** children = malloc(num_results * sizeof(Blizzard__Value__Object__ChildrenEntry*));
   if (!children) {
      *error_msg = "Malloc failed for children";
      free(result_obj);
      return false;
   }
   result_obj->children = children;
   int valid_children = 0;

   for (int i = 0; i < num_results; i++) {
      Blizzard__Value__Object__ChildrenEntry* entry = malloc(sizeof(Blizzard__Value__Object__ChildrenEntry));
      if (!entry) {
         *error_msg = "Malloc failed for entry";
         goto build_fail;
      }
      blizzard__value__object__children_entry__init(entry);
      entry->key = strdup(results[i].key);
      if (!entry->key) {
         *error_msg = "strdup failed for key";
         free(entry);
         goto build_fail;
      }

      Blizzard__Value__Value* val = malloc(sizeof(Blizzard__Value__Value));
      if (!val) {
         *error_msg = "Malloc failed for val";
         free(entry->key);
         free(entry);
         goto build_fail;
      }
      blizzard__value__value__init(val);

      switch (results[i].type) {
         case VALUE_TYPE_STRING:
            val->kind_case = BLIZZARD__VALUE__VALUE__KIND_STRING;
            val->string = strdup(results[i].value.string);
            if (!val->string) {
               *error_msg = "strdup failed for string value";
               free(val);
               free(entry->key);
               free(entry);
               goto build_fail;
            }
            break;
         case VALUE_TYPE_INTEGER:
            val->kind_case = BLIZZARD__VALUE__VALUE__KIND_INTEGER;
            val->integer = results[i].value.integer;
            break;
         case VALUE_TYPE_DOUBLE:
            val->kind_case = BLIZZARD__VALUE__VALUE__KIND_DOUBLE;
            val->double_ = results[i].value.double_val;
            break;
         case VALUE_TYPE_BOOLEAN:
            val->kind_case = BLIZZARD__VALUE__VALUE__KIND_BOOLEAN;
            val->boolean = results[i].value.boolean;
            break;
         case VALUE_TYPE_BYTES:
            val->kind_case = BLIZZARD__VALUE__VALUE__KIND_BYTES;
            val->bytes.len = results[i].value.bytes.len;
            val->bytes.data = malloc(val->bytes.len);
            if (!val->bytes.data) {
               *error_msg = "Malloc failed for bytes value";
               free(val);
               free(entry->key);
               free(entry);
               goto build_fail;
            }
            memcpy(val->bytes.data, results[i].value.bytes.data, val->bytes.len);
            break;
         default:
            *error_msg = "Unsupported type in results";
            free(val);
            free(entry->key);
            free(entry);
            goto build_fail;
      }
      entry->value = val;

      // All succeeded, assign
      children[valid_children] = entry;
      valid_children++;
   }

   result_obj->n_children = valid_children;
   return true;

build_fail:
   // Cleanup partial
   for (int j = 0; j < valid_children; j++) {
      Blizzard__Value__Object__ChildrenEntry* entry = children[j];
      free(entry->key);
      if (entry->value) {
         if (entry->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
            free(entry->value->string);
         } else if (entry->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_BYTES) {
            free(entry->value->bytes.data);
         }
         free(entry->value);
      }
      free(entry);
   }
   free(children);
   free(result_obj);
   return false;
}

void send_invoke_response(int sock, uint64_t id, const char* method, const Google__Protobuf__Any* parameters) {
   // Static allocations for fixed Protobuf structures
   Blizzard__Plugin__Messages__InvokeResponse resp = BLIZZARD__PLUGIN__MESSAGES__INVOKE_RESPONSE__INIT;
   Blizzard__Plugin__Messages__PluginToManagerMessage msg = BLIZZARD__PLUGIN__MESSAGES__PLUGIN_TO_MANAGER_MESSAGE__INIT;
   Google__Protobuf__Any success_any = GOOGLE__PROTOBUF__ANY__INIT;
   Blizzard__Value__Value result_value = BLIZZARD__VALUE__VALUE__INIT;
   success_any.type_url = NULL;

   // Initialize dynamic pointers
   const char** paths = NULL;
   KeyValuePair* pairs = NULL;
   KeyValuePair* in_params = NULL;
   KeyValuePair* results = NULL;
   uint8_t* packed = NULL;
   uint8_t* buf = NULL;
   char* error_msg = NULL;
   int num_params = 0;
   int num_results = 0;

   // Initialize response
   resp.id = id;

   if (strcmp(method, "get") == 0) {
      if (parameters == NULL) {
         error_msg = "No parameters provided";
      } else {
         Blizzard__Value__Value* param_value = blizzard__value__value__unpack(NULL, parameters->value.len, parameters->value.data);
         if (param_value == NULL) {
            error_msg = "Failed to unpack parameters";
         } else if (param_value->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
            error_msg = "Parameters must be an object";
         } else {
            Blizzard__Value__Object* obj = param_value->object;
            Blizzard__Value__List* path_list = NULL;

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
                  paths = malloc(num_paths * sizeof(const char*));
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
                           if (!build_keyvalue_object(pairs, num_results, &result_value, &error_msg)) {
                              // build_keyvalue_object sets error_msg
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
         Blizzard__Value__Value* param_value = blizzard__value__value__unpack(NULL, parameters->value.len, parameters->value.data);
         if (param_value == NULL) {
            error_msg = "Failed to unpack parameters";
         } else if (param_value->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
            error_msg = "Parameters must be an object";
         } else {
            Blizzard__Value__Object* obj = param_value->object;
            if (obj->n_children != 1) {
               error_msg = "Expected exactly one key-value pair in parameters";
            } else {
               Blizzard__Value__Object__ChildrenEntry* entry = obj->children[0];
               const char* key = entry->key;
               Blizzard__Value__Value* value = entry->value;

               if (key == NULL || value == NULL) {
                  error_msg = "Invalid key or value in parameters";
               } else if (value->kind_case != BLIZZARD__VALUE__VALUE__KIND_STRING) {
                  error_msg = "Value must be a string for rbus_set_value";
               } else {
                  rbusError_t err = rbus_set_value(key, value->string);
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
            }
            blizzard__value__value__free_unpacked(param_value, NULL);
         }
      }
   } else if (strcmp(method, "invoke") == 0) {
      if (parameters == NULL) {
         error_msg = "No parameters provided";
      } else {
         Blizzard__Value__Value* param_value = blizzard__value__value__unpack(NULL, parameters->value.len, parameters->value.data);
         if (param_value == NULL) {
            error_msg = "Failed to unpack parameters";
         } else if (param_value->kind_case != BLIZZARD__VALUE__VALUE__KIND_OBJECT) {
            error_msg = "Parameters must be an object";
         } else {
            Blizzard__Value__Object* obj = param_value->object;
            const char* method_name = NULL;

            // Extract "method" from the object
            for (size_t i = 0; i < obj->n_children; i++) {
               if (strcmp(obj->children[i]->key, "method") == 0 &&
                  obj->children[i]->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
                  method_name = obj->children[i]->value->string;
                  break;
               }
            }

            if (method_name == NULL) {
               error_msg = "Missing or invalid 'method' field; expected a string";
            } else {
               // Count parameters (all key-value pairs except "method")
               num_params = obj->n_children > 0 ? obj->n_children - 1 : 0;
               if (num_params > 0) {
                  in_params = malloc(num_params * sizeof(KeyValuePair));
                  if (!in_params) {
                     error_msg = "Malloc failed for input parameters";
                  } else {
                     int valid_params = 0;
                     for (size_t i = 0; i < obj->n_children && valid_params < num_params; i++) {
                        if (strcmp(obj->children[i]->key, "method") == 0) {
                           continue;
                        }
                        const char* key = obj->children[i]->key;
                        Blizzard__Value__Value* value = obj->children[i]->value;
                        if (key == NULL || value == NULL) {
                           error_msg = "Invalid key or value in parameters";
                           break;
                        }
                        in_params[valid_params].key = strdup(key);
                        if (!in_params[valid_params].key) {
                           error_msg = "Malloc failed for key";
                           break;
                        }
                        switch (value->kind_case) {
                           case BLIZZARD__VALUE__VALUE__KIND_STRING:
                              in_params[valid_params].type = VALUE_TYPE_STRING;
                              in_params[valid_params].value.string = strdup(value->string);
                              if (!in_params[valid_params].value.string) {
                                 error_msg = "Malloc failed for string value";
                                 free(in_params[valid_params].key);
                                 break;
                              }
                              break;
                           case BLIZZARD__VALUE__VALUE__KIND_INTEGER:
                              in_params[valid_params].type = VALUE_TYPE_INTEGER;
                              in_params[valid_params].value.integer = value->integer;
                              break;
                           case BLIZZARD__VALUE__VALUE__KIND_DOUBLE:
                              in_params[valid_params].type = VALUE_TYPE_DOUBLE;
                              in_params[valid_params].value.double_val = value->double_;
                              break;
                           case BLIZZARD__VALUE__VALUE__KIND_BOOLEAN:
                              in_params[valid_params].type = VALUE_TYPE_BOOLEAN;
                              in_params[valid_params].value.boolean = value->boolean;
                              break;
                           case BLIZZARD__VALUE__VALUE__KIND_BYTES:
                              in_params[valid_params].type = VALUE_TYPE_BYTES;
                              in_params[valid_params].value.bytes.len = value->bytes.len;
                              in_params[valid_params].value.bytes.data = malloc(value->bytes.len);
                              if (!in_params[valid_params].value.bytes.data) {
                                 error_msg = "Malloc failed for bytes value";
                                 free(in_params[valid_params].key);
                                 break;
                              }
                              memcpy(in_params[valid_params].value.bytes.data, value->bytes.data, value->bytes.len);
                              break;
                           case BLIZZARD__VALUE__VALUE__KIND_OBJECT: {
                              in_params[valid_params].type = VALUE_TYPE_STRING;
                              in_params[valid_params].value.string = serialize_object_to_string(value->object);
                              if (!in_params[valid_params].value.string) {
                                 error_msg = "Failed to serialize object to string";
                                 free(in_params[valid_params].key);
                                 break;
                              }
                              break;
                           }
                           default:
                              error_msg = "Unsupported value type in params";
                              free(in_params[valid_params].key);
                              break;
                        }
                        if (error_msg) {
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
                     if (!build_keyvalue_object(results, num_results, &result_value, &error_msg)) {
                        // build_keyvalue_object sets error_msg
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
      fprintf(stderr, "%s() Error: %s\n", __FUNCTION__, error_msg);
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

   send_message(sock, buf, len);

   printf("Sent invoke response length %lu, for id=%" PRIu64 "\n", len, id);

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
   if (result_value.kind_case == BLIZZARD__VALUE__VALUE__KIND_OBJECT && result_value.object) {
      for (size_t i = 0; i < result_value.object->n_children; i++) {
         Blizzard__Value__Object__ChildrenEntry* entry = result_value.object->children[i];
         free(entry->key);
         if (entry->value) {
            if (entry->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
               free(entry->value->string);
            } else if (entry->value->kind_case == BLIZZARD__VALUE__VALUE__KIND_BYTES) {
               free(entry->value->bytes.data);
            }
            free(entry->value);
         }
         free(entry);
      }
      free(result_value.object->children);
      free(result_value.object);
   } else if (result_value.kind_case == BLIZZARD__VALUE__VALUE__KIND_STRING) {
      free(result_value.string);
   }
   free(packed);
   free(success_any.type_url);
   free(paths);
   free(buf);
}

void handle_manager_message(int sock, uint8_t* buf, ssize_t len) {
   Blizzard__Plugin__Messages__ManagerToPluginMessage* msg =
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

   if (connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1) {
      fprintf(stderr, "failed to connect to: %s\n", SOCKET_PATH);
      close(sock);
      exit(EXIT_FAILURE);
   }

   rbus_init();

   send_registration_request(sock);

   while (1) {
      uint8_t buffer[READ_BUFFER_SIZE];
      ssize_t len = recv_message(sock, buffer, sizeof(buffer));
      if (len <= 0) break;
      handle_manager_message(sock, buffer, len);
   }

   close(sock);
   return 0;
}
