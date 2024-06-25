#include "cignal_slot.h"

#define MAX_CALLBACK_COUNT_FOR_ONE_CALLER 8
#define MAX_SLOT_COUNT 64

typedef struct
{
    const char* name;
    asignal_caller_t caller;
    aslot_callback_t cblist[MAX_CALLBACK_COUNT_FOR_ONE_CALLER];
}sig_slots_t;

sig_slots_t sig_slot_list[MAX_SLOT_COUNT] = {0};



void send_signal(asignal_caller_t caller)
{
    // iterate over the list, and find the caller
    unsigned char if_found_caller;
    size_t idx = 0;

    for (size_t i = 0; i < MAX_SLOT_COUNT; i++)
    {
        if_found_caller = sig_slot_list[i].caller == caller;
        if (!if_found_caller)
        {
            continue;
        }
        idx = i;
        break;
    }

    if (!if_found_caller)
    {
        return;
    }

    // iterate over the callback list
    sig_slots_t *sigslot = &(sig_slot_list[idx]);
    for (size_t i = 0; i < MAX_CALLBACK_COUNT_FOR_ONE_CALLER; i++)
    {
        if (!sigslot->cblist[i])
        {
            continue;
        }
        sigslot->caller(sig_slot_list->cblist[i]);
    }
}


void add_signal(const char* name, asignal_caller_t caller)
{
    sig_slot_list[0].name = name;
    sig_slot_list[0].caller = caller;
}

void add_slot(const char* name, aslot_callback_t callback)
{
    sig_slot_list[0].cblist[0] = callback;
}