#include "key_press_gen.h"
#include "cignal_slot.h"

void power_key_clicked(aslot_callback_t callback, void* context)
{
    callback(0);
}

void power_key_long(aslot_callback_t callback, void* context)
{
    callback(0);
}

void light_key_clicked(aslot_callback_t callback, void* context)
{
    callback(0);
}

void ac_key_clicked(aslot_callback_t callback, void* context)
{
    callback(0);
}

void ac_key_long(aslot_callback_t callback, void* context)
{
    callback(0);
}

void dc_key_clicked(aslot_callback_t callback, void* context)
{
    callback(0);
}

void usb_key_clicked(aslot_callback_t callback, void* context)
{
    callback(0);
}

void eco_key_clicked(aslot_callback_t callback, void* context)
{
    callback(0);
}

void ac_eco_long(aslot_callback_t callback, void* context)
{
    callback(0);
}

static void key_press_gen_initialize(void)
{
    // declarative style
    signal_node_t signal_list[] =
    {
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.power_clicked}, .caller = power_key_clicked},
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.light_clicked}, .caller = light_key_clicked},
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.ac_clicked}, .caller = ac_key_clicked},
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.dc_clicked}, .caller = dc_key_clicked},
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.eco_clicked}, .caller = eco_key_clicked},
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.ac_eco_long}, .caller = ac_eco_long},
    };

    use_llist_create_signal_from_array(signal_list, sizeof(signal_list)/sizeof(*signal_list));
}

void key_press_gen_task(void)
{
    unsigned char if_initialized = 0;
    if (!if_initialized)
    {
        key_press_gen_initialize();
        if_initialized = 1;
    }

    // check keys and send signal if any checked
}