#ifndef _CIGNAL_SLOT_H_
#define _CIGNAL_SLOT_H_
#include "cignal_slot_types.h"

void send_signal(asignal_caller_t caller);
void add_signal(const char* name, asignal_caller_t caller);
void add_slot(const char* name, aslot_callback_t callback);

#endif // !_CIGNAL_SLOT_H_