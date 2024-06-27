#ifndef _CIGNAL_SLOT_TYPES_H_
#define _CIGNAL_SLOT_TYPES_H_
#include <stddef.h>
#include "cignal_slot_def.h"

// closure might be better
typedef void(*aslot_callback_t)(void* context);
typedef void(*asignal_caller_t)(aslot_callback_t callback);


typedef struct
{
    const char* signal_name;
    asignal_caller_t caller;
    aslot_callback_t cblist[MAX_CALLBACK_COUNT_FOR_ONE_CALLER];
}sig_slots_t;


#endif // !_CIGNAL_SLOT_TYPES_H_