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
        usig power_updated;
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
        usig power_updated;
        usig over_current;
    } usb_uni;

    struct
    {
        usig power_updated;
        usig over_current;
    } dc;

    struct
    {
        usig power_updated;
        usig jsut_out;
        usig just_in;
        usig volt_ok;
        struct
        {
            usig temp_updated;
        } temp;
        usig request_fan;
    } dc_charger;

    struct
    {
        usig power_updated;
        usig just_out;
        usig just_in;
        struct
        {
            usig temp_updated;
        } temp;
        usig request_fan;
    } usb_bi;

    struct
    {
        usig power_updated;
        usig went_on;
        usig went_off;
        usig just_in;
        usig just_out;
        struct
        {
            usig temp_updated;
        } temp;
        usig request_fan;
    } inverter;

    struct
    {
        usig power_updated;
        usig went_on;
        usig went_off;
        usig went_sos;
    } flash_light;

    struct
    {
        usig power_updated;
        usig went_on;
        usig went_off;
    } bar_light;

    struct
    {
        usig power_clicked;
        usig ac_clicked;
        usig dc_clicked;
        usig eco_clicked;
        usig light_clicked;
        usig power_long;
        usig ac_long;
        usig dc_long;
        usig eco_long;
        usig light_long;
        usig ac_eco_long;
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
        usig about_to_go_off;
        usig is_on;
    } system_power_supply;

    struct
    {
        usig power_all_updated;
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