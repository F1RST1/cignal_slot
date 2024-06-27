#include "cignal_slot.h"
#include <string.h>

#define MAX_CALLBACK_COUNT_FOR_ONE_CALLER 8
#define MAX_SIGNAL_COUNT 64

typedef struct
{
    const char* signal_name;
    asignal_caller_t caller;
    aslot_callback_t cblist[MAX_CALLBACK_COUNT_FOR_ONE_CALLER];
}sig_slots_t;

sig_slots_t sig_slot_list[MAX_SIGNAL_COUNT] = {0};



static int find_signal_by_fn(asignal_caller_t caller, int* if_found);
void emit_signal(asignal_caller_t caller)
{
    // iterate over the list, and find the caller
    int if_found_caller;
    int idx = 0;
    
    idx = find_signal_by_fn(caller, &if_found_caller);

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
        sigslot->caller(sigslot->cblist[i]);
    }
}


void create_signal(const char* signal_name, asignal_caller_t caller)
{
    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        if (sig_slot_list[i].signal_name)
        {
            continue;
        }
        sig_slot_list[i].signal_name = signal_name;
        sig_slot_list[i].caller = caller;
    }
}

static int find_signal_by_name(const char* signal_name, int* if_found);
void attach_slot_to(const char* signal_name, aslot_callback_t callback)
{
    int if_found = 0;
    int idx = find_signal_by_name(signal_name, &if_found);

    if (!if_found)
    {
        return;
    }

    // iterate over the callback list
    sig_slots_t *sigslot = &(sig_slot_list[idx]);
    for (size_t i = 0; i < MAX_CALLBACK_COUNT_FOR_ONE_CALLER; i++)
    {
        if (sigslot->cblist[i])
        {
            continue;
        }
        sigslot->cblist[i] = callback;
        break;
    }

}


static int find_signal_by_name(const char* signal_name, int* if_found)
{
    *if_found = 0;
    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        if (strcmp(signal_name, sig_slot_list[i].signal_name) == 0)
        {
            *if_found = 1;
            return i;
        }
    }
    return 0;
}


static int find_signal_by_fn(asignal_caller_t caller, int* if_found)
{
    *if_found = 0;
    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        if (sig_slot_list[i].caller == caller)
        {
            *if_found = 1;
            return i;
        }
    }
    return 0;
}