#ifndef _CIGNAL_SLOT_TYPES_H_
#define _CIGNAL_SLOT_TYPES_H_
#include <stddef.h>

// closure might be better
typedef void(*aslot_callback_t)(void* context);
typedef void(*asignal_caller_t)(aslot_callback_t callback);




#endif // !_CIGNAL_SLOT_TYPES_H_