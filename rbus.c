#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rbus_plugin.h"

#define VALUE_MAX_LEN 512

rbusHandle_t g_rbusHandle = NULL;

void rbus_init(void) {
   rbusError_t err = rbus_open(&g_rbusHandle, "rbus-plugin");
}

static bool convert_rbus_value_to_keyvaluepair(rbusValue_t value, KeyValuePair *pair) {
   if (!value) {
      return false;
   }

   switch (rbusValue_GetType(value)) {
   case RBUS_BOOLEAN: {
      pair->type = VALUE_TYPE_BOOLEAN;
      pair->value.boolean = rbusValue_GetBoolean(value);
      break;
   }
   case RBUS_CHAR: {
      pair->type = VALUE_TYPE_STRING;
      char char_val = rbusValue_GetChar(value);
      pair->value.string = malloc(2);
      if (!pair->value.string) {
         return false;
      }
      pair->value.string[0] = char_val;
      pair->value.string[1] = '\0';
      break;
   }
   case RBUS_BYTE: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetByte(value);
      break;
   }
   case RBUS_INT8: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetInt8(value);
      break;
   }
   case RBUS_UINT8: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetUInt8(value);
      break;
   }
   case RBUS_INT16: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetInt16(value);
      break;
   }
   case RBUS_UINT16: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetUInt16(value);
      break;
   }
   case RBUS_INT32: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetInt32(value);
      break;
   }
   case RBUS_UINT32: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetUInt32(value);
      break;
   }
   case RBUS_INT64: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetInt64(value);
      break;
   }
   case RBUS_UINT64: {
      pair->type = VALUE_TYPE_INTEGER;
      pair->value.integer = rbusValue_GetUInt64(value);
      break;
   }
   case RBUS_SINGLE: {
      pair->type = VALUE_TYPE_DOUBLE;
      pair->value.double_val = rbusValue_GetSingle(value);
      break;
   }
   case RBUS_DOUBLE: {
      pair->type = VALUE_TYPE_DOUBLE;
      pair->value.double_val = rbusValue_GetDouble(value);
      break;
   }
   case RBUS_DATETIME: {
      pair->type = VALUE_TYPE_STRING;
      const rbusDateTime_t *time_val = rbusValue_GetTime(value);
      if (time_val) {
         pair->value.string = malloc(128);
         if (!pair->value.string) {
            return false;
         }
         snprintf(pair->value.string, 128,
            "%04d-%02d-%02dT%02d:%02d:%02d%s%02d:%02d",
            time_val->m_time.tm_year + 1900,
            time_val->m_time.tm_mon + 1,
            time_val->m_time.tm_mday,
            time_val->m_time.tm_hour,
            time_val->m_time.tm_min,
            time_val->m_time.tm_sec,
            time_val->m_tz.m_isWest ? "-" : "+",
            time_val->m_tz.m_tzhour,
            time_val->m_tz.m_tzmin);
      } else {
         return false;
      }
      break;
   }
   case RBUS_STRING: {
      pair->type = VALUE_TYPE_STRING;
      const char *str_val = rbusValue_GetString(value, NULL);
      pair->value.string = strdup(str_val);
      if (!pair->value.string) {
         return false;
      }
      break;
   }
   case RBUS_BYTES: {
      pair->type = VALUE_TYPE_BYTES;
      int len = 0;
      const uint8_t *bytes_val = rbusValue_GetBytes(value, &len);
      pair->value.bytes.data = malloc(len);
      if (!pair->value.bytes.data) {
         return false;
      }
      memcpy(pair->value.bytes.data, bytes_val, len);
      pair->value.bytes.len = len;
      break;
   }
   case RBUS_NONE:
   default:
      return false;
   }
   return true;
}

rbusError_t rbus_get_values(const char **propertyNames, int numProperties, int *numPairs, KeyValuePair **pairs) {
   int numProps = 0;
   rbusProperty_t properties = NULL;
   rbusError_t err = rbus_getExt(g_rbusHandle, numProperties, propertyNames, &numProps, &properties);
   if (err != RBUS_ERROR_SUCCESS) {
      return err;
   }

   *numPairs = 0;
   *pairs = NULL;

   if (numProps > 0) {
      *pairs = malloc(numProps * sizeof(KeyValuePair));
      if (*pairs == NULL) {
         rbusProperty_Release(properties);
         return RBUS_ERROR_OUT_OF_RESOURCES;
      }

      int index = 0;
      rbusProperty_t prop = properties;
      while (prop) {
         const char *key = rbusProperty_GetName(prop);
         rbusValue_t val = rbusProperty_GetValue(prop);
         if (key && convert_rbus_value_to_keyvaluepair(val, &(*pairs)[index])) {
            (*pairs)[index].key = strdup(key);
            if ((*pairs)[index].key) {
               index++;
            } else {
               if ((*pairs)[index].type == VALUE_TYPE_STRING) {
                  free((*pairs)[index].value.string);
               } else if ((*pairs)[index].type == VALUE_TYPE_BYTES) {
                  free((*pairs)[index].value.bytes.data);
               }

               for (int j = 0; j < index; j++) {
                  free((*pairs)[j].key);
                  if ((*pairs)[j].type == VALUE_TYPE_STRING) {
                     free((*pairs)[j].value.string);
                  } else if ((*pairs)[j].type == VALUE_TYPE_BYTES) {
                     free((*pairs)[j].value.bytes.data);
                  }
               }
               free(*pairs);
               *pairs = NULL;
               rbusProperty_Release(properties);
               return RBUS_ERROR_OUT_OF_RESOURCES;
            }
         }
         prop = rbusProperty_GetNext(prop);
      }
      *numPairs = index;

      if (index == 0) {
         free(*pairs);
         *pairs = NULL;
      }
   }

   rbusProperty_Release(properties);
   return RBUS_ERROR_SUCCESS;
}

rbusError_t rbus_set_value(const char *propertyName, const char *val_str) {

   rbusValue_t value;
   rbusValue_Init(&value);

   rbusValue_t current_value;
   rbusValueType_t target_type = RBUS_STRING;
   rbusError_t err = rbus_get(g_rbusHandle, propertyName, &current_value);
   if (err == RBUS_ERROR_SUCCESS) {
      target_type = rbusValue_GetType(current_value);
      rbusValue_Release(current_value);
   } else {
      fprintf(stderr, "Error: rbus_get failed for '%s' during type inference (%d). Cannot set without known type.\n", propertyName, err);
      rbusValue_Release(value);
      return RBUS_ERROR_INVALID_INPUT;
   }

   bool conversion_success = false;
   switch (target_type) {
   case RBUS_BOOLEAN:
   case RBUS_CHAR:
   case RBUS_BYTE:
   case RBUS_INT8:
   case RBUS_UINT8:
   case RBUS_INT16:
   case RBUS_UINT16:
   case RBUS_INT32:
   case RBUS_UINT32:
   case RBUS_INT64:
   case RBUS_UINT64:
   case RBUS_SINGLE:
   case RBUS_DOUBLE:
   case RBUS_STRING: {
      conversion_success = rbusValue_SetFromString(value, target_type, val_str);
      break;
   }
   case RBUS_DATETIME: {
      struct tm tm = {0};
      int year, month, day, hour, min, sec;
      int tz_hour_val = 0, tz_min_val = 0;
      char tz_sign = '+';
      int scanned = sscanf(val_str, "%d-%d-%dT%d:%d:%d%c%d:%d",
         &year, &month, &day, &hour, &min, &sec,
         &tz_sign, &tz_hour_val, &tz_min_val);
      if (scanned >= 6) {
         tm.tm_year = year - 1900;
         tm.tm_mon = month - 1;
         tm.tm_mday = day;
         tm.tm_hour = hour;
         tm.tm_min = min;
         tm.tm_sec = sec;
         rbusDateTime_t dt;
         rbusValue_MarshallTMtoRBUS(&dt, &tm);
         if (scanned == 9) {
            dt.m_tz.m_tzhour = tz_hour_val;
            dt.m_tz.m_tzmin = tz_min_val;
            dt.m_tz.m_isWest = (tz_sign == '-');
         } else {
            dt.m_tz.m_isWest = 0;
            dt.m_tz.m_tzhour = 0;
            dt.m_tz.m_tzmin = 0;
         }
         rbusValue_SetTime(value, &dt);
         conversion_success = true;
      }
      break;
   }
   case RBUS_BYTES: {
      size_t str_len = strlen(val_str);
      if (str_len % 2 == 0) {
         size_t byte_len = str_len / 2;
         uint8_t bytes[VALUE_MAX_LEN / 2];
         if (byte_len <= sizeof(bytes)) {
            conversion_success = true;
            for (size_t i = 0; i < byte_len; i++) {
               unsigned int byte = 0;
               if (sscanf(&val_str[i * 2], "%2x", &byte) == 1) {
                  bytes[i] = (uint8_t)byte;
               } else {
                  conversion_success = false;
                  break;
               }
            }
            if (conversion_success) {
               rbusValue_SetBytes(value, bytes, byte_len);
            }
         } else {
         }
      }
      break;
   }
   case RBUS_PROPERTY:
   case RBUS_OBJECT: {
      rbusValue_Release(value);
      return RBUS_ERROR_INVALID_INPUT;
   }
   case RBUS_NONE:
      rbusValue_SetString(value, val_str);
      conversion_success = true;
      break;
   default:
      rbusValue_Release(value);
      return RBUS_ERROR_INVALID_INPUT;
   }

   if (!conversion_success) {
      rbusValue_Release(value);
      return RBUS_ERROR_INVALID_INPUT;
   }

   err = rbus_set(g_rbusHandle, propertyName, value, NULL);
   rbusValue_Release(value);
   if (err != RBUS_ERROR_SUCCESS) {
      return err;
   }

   return RBUS_ERROR_SUCCESS;
}

rbusError_t rbus_invoke_method(const char *methodName, int numParams, KeyValuePair *inParams, int *numResults, KeyValuePair **results) {
   rbusObject_t inObj;
   rbusObject_t outObj;
   rbusError_t err;

   *numResults = 0;
   *results = NULL;

   // Initialize input object
   rbusObject_Init(&inObj, NULL);

   // Convert KeyValuePair array to rbusObject_t
   for (int i = 0; i < numParams; i++) {
      rbusValue_t paramVal;
      rbusValue_Init(&paramVal);
      switch (inParams[i].type) {
      case VALUE_TYPE_STRING:
         rbusValue_SetString(paramVal, inParams[i].value.string);
         break;
      case VALUE_TYPE_INTEGER:
         rbusValue_SetInt64(paramVal, inParams[i].value.integer);
         break;
      case VALUE_TYPE_DOUBLE:
         rbusValue_SetDouble(paramVal, inParams[i].value.double_val);
         break;
      case VALUE_TYPE_BOOLEAN:
         rbusValue_SetBoolean(paramVal, inParams[i].value.boolean);
         break;
      case VALUE_TYPE_BYTES:
         rbusValue_SetBytes(paramVal, inParams[i].value.bytes.data, inParams[i].value.bytes.len);
         break;
      default:
         rbusValue_Release(paramVal);
         rbusObject_Release(inObj);
         return RBUS_ERROR_INVALID_PARAMETER_TYPE;
      }
      rbusObject_SetValue(inObj, inParams[i].key, paramVal);
      rbusValue_Release(paramVal);
   }

   // Call rbusMethod_Invoke
   err = rbusMethod_Invoke(g_rbusHandle, methodName, inObj, &outObj);
   rbusObject_Release(inObj);

   if (err != RBUS_ERROR_SUCCESS) {
      return err;
   }

   // Count properties manually
   rbusProperty_t prop = rbusObject_GetProperties(outObj);
   int count = 0;
   rbusProperty_t temp = prop;
   while (temp) {
      count++;
      temp = rbusProperty_GetNext(temp);
   }

   // Process output parameters
   if (count > 0) {
      *results = malloc(count * sizeof(KeyValuePair));
      if (*results == NULL) {
         rbusObject_Release(outObj);
         return RBUS_ERROR_OUT_OF_RESOURCES;
      }

      int index = 0;
      while (prop) {
         const char *key = rbusProperty_GetName(prop);
         rbusValue_t val = rbusProperty_GetValue(prop);
         if (key && convert_rbus_value_to_keyvaluepair(val, &(*results)[index])) {
            (*results)[index].key = strdup(key);
            if ((*results)[index].key) {
               index++;
            } else {
               if ((*results)[index].type == VALUE_TYPE_STRING) {
                  free((*results)[index].value.string);
               } else if ((*results)[index].type == VALUE_TYPE_BYTES) {
                  free((*results)[index].value.bytes.data);
               }
               for (int j = 0; j < index; j++) {
                  free((*results)[j].key);
                  if ((*results)[j].type == VALUE_TYPE_STRING) {
                     free((*results)[j].value.string);
                  } else if ((*results)[j].type == VALUE_TYPE_BYTES) {
                     free((*results)[j].value.bytes.data);
                  }
               }
               free(*results);
               *results = NULL;
               rbusObject_Release(outObj);
               return RBUS_ERROR_OUT_OF_RESOURCES;
            }
         }
         prop = rbusProperty_GetNext(prop);
      }
      *numResults = index;

      if (index == 0) {
         free(*results);
         *results = NULL;
      }
   }

   rbusObject_Release(outObj);
   return RBUS_ERROR_SUCCESS;
}
