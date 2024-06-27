#include <stdio.h>
#include "cignal_slot.h"

void __caller(aslot_callback_t slot)
{
    static int x = 30;
    slot(&x);
}


void callback_on_happened(void* payload)
{
    int* _int = (int*)payload;
    printf("recv:%d\r\n", *_int);
}

int main(int argc, char const *argv[])
{
    create_signal("mycaller", __caller);
    attach_slot_to("mycaller", callback_on_happened);

    emit_signal(__caller);
    return 0;
}
