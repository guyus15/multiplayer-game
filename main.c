#include "packet.h"

#include <stdio.h>

int main()
{
    printf("Packet Tester\n");

    packet_t *packet = create_packet();

    write_byte(packet, 'a');

    return 0;
}
