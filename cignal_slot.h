#ifndef _CIGNAL_SLOT_H_
#define _CIGNAL_SLOT_H_
#include "cignal_slot_types.h"

void use_array_emit_signal(asignal_caller_t caller);
sig_slots_t *use_array_create_signal(const char *signal_name, asignal_caller_t caller);
void use_array_connect_slot_to(const char *name, aslot_callback_t callback);

signal_node_t *use_llist_create_signal_noname(usig_addr_t base, usig_addr_t offset, asignal_caller_t caller);
void use_llist_safely_connect_slot_to(usig_addr_t base, usig_addr_t offset, slot_node_t *slot_to_connect);
void use_llist_emit_signal(asignal_caller_t caller);



slot_node_t create_slot_node(aslot_callback_t callback);

#endif // !_CIGNAL_SLOT_H_