/**
 * @file packet.h
 * @brief Specifies functions to write and read from specific packets.
 */

#ifndef PACKET_H
#define PACKET_H

#include <stddef.h>
#include <stdint.h>

#define PACKET_SIZE 256
#define CHARSIZE 1
#define INT16SIZE 2
#define INT32SIZE 4
#define INT64SIZE 8
#define FLOATSIZE 4
#define DOUBLESIZE 8

typedef enum packet_type_enum
{
    NONE = 0,
    WELCOME,
    WELCOME_RECEIVED,
    SPAWN_PLAYER,
    PLAYER_MOVEMENT
} packet_type;

typedef struct packet_struct
{   
    packet_type type;
    size_t size;
    int read_head;
    unsigned char buffer[PACKET_SIZE];
} packet_t;

packet_t* create_packet();

packet_type get_packet_type(packet_t *packet);
void set_packet_type(packet_t *packet, packet_type type);

//
// Write functions
//

int write_byte(packet_t *packet, char value);
int write_int16(packet_t *packet, int16_t value);
int write_int32(packet_t *packet, int32_t value);
int write_int64(packet_t *packet, int64_t value);
int write_float(packet_t *packet, float value);
int write_double(packet_t *packet, double value);

//
// Read functions
//

int read_byte(packet_t *packet, char *dest);
int read_int16(packet_t *packet, int16_t *dest);
int read_int32(packet_t *packet, int32_t *dest);
int read_int64(packet_t *packet, int64_t *dest);
int read_float(packet_t *packet, float *dest);
int read_double(packet_t *packet, double *dest);

#endif

