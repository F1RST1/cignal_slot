#ifndef _CIGNAL_SLOT_H_
#define _CIGNAL_SLOT_H_
#include "cignal_slot_types.h"

void emit_signal(asignal_caller_t caller);
void create_signal(const char* name, asignal_caller_t caller);
void attach_slot_to(const char* name, aslot_callback_t callback);

#endif // !_CIGNAL_SLOT_H_