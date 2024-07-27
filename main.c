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
    // procedural style
    // use_llist_create_signal_noname(&signal_type, &signal_type.key.any, __caller);
    static slot_node_t node;
    node = create_slot_node(callback_on_happened);
    use_llist_safely_connect_slot_to(&signal_type, &signal_type.key.any, &node);

    use_llist_create_signal_noname(&signal_type, &signal_type.key.any, __caller);

    static slot_node_t node2;
    node2 = create_slot_node(callback_on_happened);
    use_llist_safely_connect_slot_to(&signal_type, &signal_type.key.any, &node2);

    use_llist_emit_signal_by_caller(__caller);
    use_llist_emit_signal_by_id(&signal_type, &signal_type.key.any);



    // declarative style
    signal_slot_connection_t conns[] = 
    {
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.any}, .slot_node = {.callback = callback_on_happened}},
        {.signal_id = {.base = &signal_type, .offset = &signal_type.key.any}, .slot_node = {.callback = NULL}},
    };

    use_llist_safely_connect_slot_array(conns, sizeof(conns)/ sizeof(*conns));
    use_llist_emit_signal_by_id(&signal_type, &signal_type.key.any);

    return 0;
}
