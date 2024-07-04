#include "key_press_gen.h"
#include "cignal_slot.h"

void power_key_clicked(aslot_callback_t callback)
{
    callback(0);
}

void power_key_long(aslot_callback_t callback)
{
    callback(0);
}

void light_key_clicked(aslot_callback_t callback)
{
    callback(0);
}

void ac_key_clicked(aslot_callback_t callback)
{
    callback(0);
}

void ac_key_long(aslot_callback_t callback)
{
    callback(0);
}

void dc_key_clicked(aslot_callback_t callback)
{
    callback(0);
}

void usb_key_clicked(aslot_callback_t callback)
{
    callback(0);
}

void eco_key_clicked(aslot_callback_t callback)
{
    callback(0);
}

void ac_eco_long(aslot_callback_t callback)
{
    callback(0);
}

static void key_press_gen_initialize(void)
{
    create_signal("power_key_clicked", power_key_clicked);
    create_signal("power_key_long", power_key_long);
    create_signal("light_key_clicked", light_key_clicked);
    create_signal("ac_key_clicked", ac_key_clicked);
    create_signal("ac_key_long", ac_key_long);
    create_signal("dc_key_clicked", dc_key_clicked);
    create_signal("usb_key_clicked", usb_key_clicked);
    create_signal("eco_key_clicked", eco_key_clicked);
    create_signal("ac_eco_long", ac_eco_long);
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