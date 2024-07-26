#ifndef _USER_SIGNAL_H_
#define _USER_SIGNAL_H_

// TODO use base&offset instead of string to identify signal 

typedef unsigned char usig;

typedef struct
{
    struct
    {
        usig battery_over_temp;
        usig battery_under_temp;
        usig battery_over_volt;
        usig battery_under_volt;
    }battery_signal;
    
    struct
    {
        usig usb_is_off;
        usig usb_is_on;
        usig usb_over_temp;
    }usb_signal;

    struct
    {
        usig dc_charger_is_out;
        usig dc_charger_is_in;
        usig dc_charger_over_temp;
    }dc_charger_signal;

    struct
    {
        usig usb_charger_is_out;
        usig usb_charger_is_in;
        usig usb_charger_over_temp;
    }usb_charger_signal;
    


    
    
}user_signal_t;


extern user_signal_t signal_type;

typedef user_signal_t* usig_addr_t;
#define SIGNAL_OFFSET(pparent, pmember) ((pmember) - (pparent))
typedef struct
{
    usig_addr_t base;
    usig_addr_t offset;
}usig_id_t;


#endif // !_USER_SIGNAL_H_