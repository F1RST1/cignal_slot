#ifndef _CIGNAL_SLOT_TYPES_H_
#define _CIGNAL_SLOT_TYPES_H_
#include <stddef.h>
#include "cignal_slot_def.h"
#include "user_signal.h"

// closure might be better
typedef void(*aslot_callback_t)(unsigned char ignore, ...);
typedef void(*asignal_caller_t)(aslot_callback_t callback);


typedef struct
{
    const char* signal_name;
    asignal_caller_t caller;
    aslot_callback_t cblist[MAX_CALLBACK_COUNT_FOR_ONE_CALLER];
}sig_slots_t;


typedef struct slot_node slot_node_t;
struct slot_node
{
    aslot_callback_t callback;
    slot_node_t* next;
};

typedef struct
{
    usig_id_t signal_id;
    asignal_caller_t caller;  // 
    slot_node_t* slot_list;   // linked list
}signal_node_t;

// for declarative style
typedef struct
{
    usig_id_t signal_id;
    slot_node_t slot_node;
}signal_slot_connection_t;






#endif // !_CIGNAL_SLOT_TYPES_H_