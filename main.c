#include <stdio.h>
#include "cignal_slot.h"

void __caller(aslot_callback_t callback)
{
    static int x = 30;
    callback(&x);
}


void recv(void* payload)
{
    int* _int = (int*)payload;
    printf("recv:%d\r\n", *_int);
}

int main(int argc, char const *argv[])
{
    add_signal("mycaller", __caller);
    add_slot("mycaller", recv);

    send_signal(__caller);
    return 0;
}
