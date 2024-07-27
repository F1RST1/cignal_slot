#ifndef _USER_SIGNAL_H_
#define _USER_SIGNAL_H_

typedef unsigned char usig;

typedef struct
{
    struct
    {
        usig over_volt;
        usig under_volt;
        usig request_fan;
        struct
        {
            usig update_min_temp;
            usig update_max_temp;
        }temp;
    }battery;

    
    struct
    {
        usig update_power;
        usig over_current;
    }usb_uni;

    struct
    {
        usig update_power;
        usig over_current;
    }dc;

    struct
    {
        usig update_power;
        usig jsut_out;
        usig just_in;
        usig volt_ok;
        struct
        {
            usig update_temp;
        }temp;
        usig request_fan;
    }dc_charger;

    struct
    {
        usig update_power;
        usig just_out;
        usig just_in;
        struct
        {
            usig update_temp;
        }temp;
        usig request_fan;
    }usb_bi;

    struct
    {
        usig update_power;
        usig went_off;
        usig just_in;
        usig just_out;
        struct
        {
            usig update_temp;
        }temp;
        usig request_fan;
    }inverter;

    struct
    {
        usig update_power;
        usig went_on;
        usig went_off;
        usig went_sos;
    }flash_light;

    struct
    {
        usig update_power;
        usig went_on;
        usig went_off;
    }bar_light;
    
    struct
    {
        usig any;
        usig usb_clicked;
        usig ac_clicked;
        usig dc_clicked;
        usig usb_long;
        usig ac_long;
        usig dc_long;
    }key;
    
    struct
    {
        usig went_off;
    }display;

    // application
    struct
    {
        usig developer_mode_on;
        usig developer_mode_off;
    }developer;
    
    
    
    

    
    
}user_signal_t;


extern user_signal_t signal_type;

typedef void* usig_addr_t;
typedef struct
{
    usig_addr_t base;
    usig_addr_t offset;
}usig_id_t;


#endif // !_USER_SIGNAL_H_