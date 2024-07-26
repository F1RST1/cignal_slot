#include <stdio.h>
#include "cignal_slot.h"

void __caller(aslot_callback_t slot)
{
    static int x = 99;
    static int x2= 50;
    slot(0, &x, &x2);
}

void callback_on_happened(int ignore, const int *x, const int *x2)
{
    printf("recv:%d\r\n", *x);
    printf("recv:%d\r\n", *x2);
}

int main_2(int argc, char const *argv[])
{
    use_array_create_signal("mycaller", __caller);
    use_array_connect_slot_to("mycaller", callback_on_happened);

    use_array_emit_signal(__caller);
    return 0;
}

int main(int argc, char const *argv[])
{
    use_llist_create_signal("mycaller", 0, 0, __caller);
    slot_node_t node = create_slot_node(callback_on_happened);
    use_llist_connect_slot_to("mycaller", 0, 0, &node);

    slot_node_t node2 = create_slot_node(callback_on_happened);
    use_llist_connect_slot_to("mycaller", 0, 0, &node2);
    use_llist_emit_signal(__caller);

    slot_node_t node3 = create_slot_node(callback_on_happened);
    use_llist_connect_slot_to("mycaller", 0, 0, &node3);
    use_llist_emit_signal(__caller);
    return 0;
}

