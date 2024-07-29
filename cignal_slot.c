#include "cignal_slot.h"
#include <string.h>


#ifdef USE_ARRAY
sig_slots_t sig_slot_list[MAX_SIGNAL_COUNT] = {0};

static int use_array_find_signal_by_fn(asignal_caller_t caller, int* if_found);
void use_array_emit_signal(asignal_caller_t caller)
{
    // iterate over the list, and find the caller
    int if_found_caller;
    int idx = 0;
    
    idx = use_array_find_signal_by_fn(caller, &if_found_caller);

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


static int use_array_find_signal_by_name(const char* signal_name, int* if_found);
sig_slots_t* use_array_create_signal(const char* signal_name, asignal_caller_t caller)
{
    int if_found = 0;
    int idx = use_array_find_signal_by_name(signal_name, &if_found);
    if (if_found)
    {
        sig_slots_t* sigslot = &(sig_slot_list[idx]);
        sigslot->caller = caller;
        return sigslot;
    }

    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        if (sig_slot_list[i].signal_name)
        {
            continue;
        }
        sig_slot_list[i].signal_name = signal_name;
        sig_slot_list[i].caller = caller;
        return &sig_slot_list[i];
    }
    return NULL;
}

void use_array_connect_slot_to(const char* signal_name, aslot_callback_t callback)
{
    int if_found = 0;
    int idx = use_array_find_signal_by_name(signal_name, &if_found);

    sig_slots_t *sigslot = NULL;
    if (!if_found)
    {
        sigslot = use_array_create_signal(signal_name, NULL);
        if (!sigslot)
        {
            return;
        }
    }
    else
    {
        sigslot = &(sig_slot_list[idx]);
    }

    // iterate over the callback list
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


static int use_array_find_signal_by_name(const char* signal_name, int* if_found)
{
    *if_found = 0;
    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        if (!sig_slot_list[i].signal_name)
        {
            continue;
        }
        if (strcmp(signal_name, sig_slot_list[i].signal_name) == 0)
        {
            *if_found = 1;
            return i;
        }
    }
    return 0;
}


static int use_array_find_signal_by_fn(asignal_caller_t caller, int* if_found)
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
#endif // USE_ARRAY

#ifdef USE_LINKED_LIST

static signal_node_t signal_llist[MAX_SIGNAL_COUNT] = {0};

static int use_llist_find_signal_by_fn(asignal_caller_t caller, int* if_found);
static void use_llist_emit_psignal(signal_node_t* psignal);
void use_llist_emit_signal_by_caller(asignal_caller_t caller)
{
    int if_found_caller = 0;
    int idx = 0;

    idx = use_llist_find_signal_by_fn(caller, &if_found_caller);

    if (!if_found_caller)
    {
        return;
    }

    use_llist_emit_psignal(signal_llist + idx);    
}

static int use_llist_find_signal_by_addr(usig_addr_t base, usig_addr_t offset, int* if_found);
void use_llist_emit_signal_by_id(usig_addr_t base, usig_addr_t offset)
{
    int if_found = 0;
    int idx = use_llist_find_signal_by_addr(base, offset, &if_found);
    if (!if_found)
    {
        return;
    }

    use_llist_emit_psignal(signal_llist + idx);    
}

signal_node_t *use_llist_create_signal(usig_addr_t base, usig_addr_t offset, asignal_caller_t caller)
{
    int if_found = 0;
    int idx = use_llist_find_signal_by_addr(base, offset, &if_found);
    if (if_found)
    {
        signal_node_t* psignal = signal_llist + idx;
        psignal->caller = caller;
        return psignal;
    }

    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        if (signal_llist[i].signal_id.base != 0)
        {
            continue;
        }

        signal_llist[i].signal_id.base = base;
        signal_llist[i].signal_id.offset = offset;
        signal_llist[i].caller = caller;
        signal_llist[i].slot_list = NULL;
        return (signal_llist + i);
    }
    return NULL;
    
}

// pre-connect if signal was not created
void use_llist_connect_slot_to(usig_addr_t base, usig_addr_t offset, slot_node_t *slot_to_connect)
{
    if (!slot_to_connect->callback)
    {
        return;
    }

    int if_found = 0;
    int idx = use_llist_find_signal_by_addr(base, offset, &if_found);

    signal_node_t* psignal = NULL;
    if (!if_found)
    {
        psignal = use_llist_create_signal(base, offset, NULL);
        if (!psignal)
        {
            // array insufficient
            return;
        }
    }
    else
    {
        psignal = signal_llist + idx;
    }

    slot_to_connect->next = NULL;
    if (psignal->slot_list == NULL)
    {
        // connect as first node
        psignal->slot_list = slot_to_connect;
        return;
    }

    slot_node_t* pslot = psignal->slot_list;
    while (1)
    {
        if (pslot->next != NULL)
        {
            pslot = pslot->next;
            continue;
        }

        pslot->next = slot_to_connect;
        return;
    }
}


void use_llist_connect_slot_array(signal_slot_connection_t* arr, size_t arrsize)
{
    for (size_t i = 0; i < arrsize; i++)
    {
        signal_slot_connection_t* pconn = arr + i;
        use_llist_connect_slot_to(pconn->signal_id.base, pconn->signal_id.offset, &pconn->slot_node);
    }
}

void use_llist_create_signal_array(signal_node_t* arr, size_t arrsize)
{
    for (size_t i = 0; i < arrsize; i++)
    {
        signal_node_t* psignal = arr + i;
        use_llist_create_signal(psignal->signal_id.base, psignal->signal_id.offset, psignal->caller);
    }
}

static int use_llist_find_signal_by_fn(asignal_caller_t caller, int* if_found)
{
    *if_found = 0;
    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        signal_node_t* psignal = signal_llist + i;
        if (psignal->caller == caller)
        {
            *if_found = 1;
            return i;
        }
    }
    return 0;
}

static int use_llist_find_signal_by_addr(usig_addr_t base, usig_addr_t offset, int* if_found)
{
    *if_found = 0;
    for (size_t i = 0; i < MAX_SIGNAL_COUNT; i++)
    {
        signal_node_t* psignal = signal_llist + i;
        if (psignal->signal_id.base == base && psignal->signal_id.offset == offset)
        {
            *if_found = 1;
            return i;
        }
    }
    return 0;
}

static void use_llist_emit_psignal(signal_node_t* psignal)
{
    if (!psignal->caller)
    {
        return;
    }
    slot_node_t* pslot = psignal->slot_list;
    if (!pslot)
    {
        return;
    }

    while (1)
    {
        if (!pslot->callback)
        {
            continue;
        }
        psignal->caller(pslot->callback);
        pslot = pslot->next;
        if (!pslot)
        {
            return;
        }
    }
}

slot_node_t create_slot_node(aslot_callback_t callback)
{
    slot_node_t node = {.callback = callback, .next = NULL};
    return node;
}
#endif // USE_LINKED_LIST