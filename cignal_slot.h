#ifndef _CIGNAL_SLOT_H_
#define _CIGNAL_SLOT_H_
#include "cignal_slot_types.h"

void emit_signal(asignal_caller_t caller);
sig_slots_t* create_signal(const char* signal_name, asignal_caller_t caller);
void connect_slot_to(const char* name, aslot_callback_t callback);

#endif // !_CIGNAL_SLOT_H_