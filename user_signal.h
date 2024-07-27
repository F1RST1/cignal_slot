#ifndef _USER_SIGNAL_H_
#define _USER_SIGNAL_H_
#include <stdint.h>

typedef uint8_t usig;

// udpate_power: periodical. negative for power out, positive for power in
// request_fan: 0-100 for speed rate

typedef struct
{
    struct
    {
        usig update_power;
        usig over_volt;
        usig under_volt;
        usig request_fan;
        struct
        {
            usig update_min_temp;
            usig update_max_temp;
        } temp;
    } battery;

    struct
    {
        usig update_power;
        usig over_current;
    } usb_uni;

    struct
    {
        usig update_power;
        usig over_current;
    } dc;

    struct
    {
        usig update_power;
        usig jsut_out;
        usig just_in;
        usig volt_ok;
        struct
        {
            usig update_temp;
        } temp;
        usig request_fan;
    } dc_charger;

    struct
    {
        usig update_power;
        usig just_out;
        usig just_in;
        struct
        {
            usig update_temp;
        } temp;
        usig request_fan;
    } usb_bi;

    struct
    {
        usig update_power;
        usig went_on;
        usig went_off;
        usig just_in;
        usig just_out;
        struct
        {
            usig update_temp;
        } temp;
        usig request_fan;
    } inverter;

    struct
    {
        usig update_power;
        usig went_on;
        usig went_off;
        usig went_sos;
    } flash_light;

    struct
    {
        usig update_power;
        usig went_on;
        usig went_off;
    } bar_light;

    struct
    {
        usig any;
        usig power_clicked;
        usig usb_clicked;
        usig ac_clicked;
        usig dc_clicked;
        usig eco_clicked;
        usig power_long;
        usig usb_long;
        usig ac_long;
        usig dc_long;
        usig eco_long;
    } key;

    struct
    {
        usig went_on;
        usig went_off;
    } display;

    // application
    struct
    {
        usig developer_mode_on;
        usig developer_mode_off;
    } developer;

    struct
    {
        usig about_to_off;
        usig is_on;
    } system_power_supply;

    struct
    {
        usig update_power_all;
    } discharge;

    struct
    {
        usig eco_timedout;
    } eco;

} user_signal_t;

extern user_signal_t signal_type;

typedef void *usig_addr_t;
typedef struct
{
    usig_addr_t base;
    usig_addr_t offset;
} usig_id_t;

#endif // !_USER_SIGNAL_H_