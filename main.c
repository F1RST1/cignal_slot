#include <stdio.h>
#include "cignal_slot.h"

void __caller(aslot_callback_t slot)
{
    static int x = 70;
    static int x2= 50;
    slot(0, &x, &x2);
}

void callback_on_happened(int ignore, const int *x, const int *x2)
{
    printf("recv:%d\r\n", *x);
    printf("recv:%d\r\n", *x2);
}

int main(int argc, char const *argv[])
{
    create_signal("mycaller", __caller);
    connect_slot_to("mycaller", callback_on_happened);

    emit_signal(__caller);
    return 0;
}
