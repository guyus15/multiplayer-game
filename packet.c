/**
 * @file packet.c
 * @brief Specifies functions to write and read from specific packets.
 */

#include "packet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Forward declarations
static int packet_full(packet_t *packet, int new_size);

/**
 * Allocates and zeroes memory required for a packet struct.
 *
 * @return A pointer to the allocated packet.
 */
packet_t* create_packet()
{
    packet_t *packet = (packet_t *) malloc(sizeof(packet_t));

    // Zero values

    memset(packet->buffer, 0, PACKET_SIZE);

    packet->size = 0;
    packet->read_head = 0;

    return packet;
}

//
// Write functions
//

/**
 * Writes a single byte to a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param value The byte value to write to the packet.
 *
 * @return A status code (-1 for failure).
 */
int write_byte(packet_t *packet, char value)
{
    if (packet_full(packet, CHARSIZE))
    {
        fprintf(stderr, "Failure when writing to packet: exceeding packet size limit.\n");
        return -1;
    }

    packet->size += CHARSIZE;
    packet->buffer[packet->size - 1] = value;

    return 0;
}

/**
 * Writes an int16_t value to a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param value The int16_t value to write to the packet.
 *
 * @return A status code (-1 for failure).
 */
int write_int16(packet_t *packet, int16_t value)
{
    if (packet_full(packet, INT16SIZE))
    {
        fprintf(stderr, "Failure when writing to packet: exceeding packet size limit.\n");
        return -1;
    }

    packet->size += INT16SIZE;
    
    memcpy(packet->buffer + packet->size - INT16SIZE, &value, INT16SIZE);

    return 0;
}

/**
 * Writes an int32_t value to a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param value The int32_t value to write to the packet.
 *
 * @return A status code (-1 for failure).
 */
int write_int32(packet_t *packet, int32_t value)
{
    if (packet_full(packet, INT32SIZE))
    {
        fprintf(stderr, "Failure when writing to packet: exceeding packet size limit.\n");
        return -1;
    }

    packet->size += INT32SIZE;
    
    memcpy(packet->buffer + packet->size - INT32SIZE, &value, INT32SIZE);

    return 0; 
}

/**
 * Writes an int64_t value to a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param value The int64_t value to write to the packet.
 *
 * @return A status code (-1 for failure).
 */
int write_int64(packet_t *packet, int64_t value)
{
    if (packet_full(packet, INT64SIZE))
    {
        fprintf(stderr, "Failure when writing to packet: exceeding packet size limit.\n");
        return -1;
    }

    packet->size += INT64SIZE;

    memcpy(packet->buffer + packet->size - INT64SIZE, &value, INT64SIZE);

    return 0;
}

/**
 * Writes a float value to a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param value The float value to write to the packet.
 *
 * @return A status code (-1 for failure).
 */
int write_float(packet_t *packet, float value)
{
    if (packet_full(packet, FLOATSIZE))
    {
        fprintf(stderr, "Failure when writing to packet: exceeding packet size limit.\n");
        return -1;
    }

    packet->size += FLOATSIZE;
    
    char buffer[FLOATSIZE];

    memcpy(packet->buffer + packet->size - FLOATSIZE, &value, FLOATSIZE);

    return 0;
}

/** 
 * Writes a double value to a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param value The float value to write to the packet.
 *
 * @return A status code (-1 for failure).
 */
int write_double(packet_t *packet, double value)
{
    if (packet_full(packet, DOUBLESIZE))
    {
        fprintf(stderr, "Failure when writing to packet: exceeding packet size limit.\n");
        return -1;
    }

    packet->size += DOUBLESIZE;

    memcpy(packet->buffer + packet->size - DOUBLESIZE, &value, DOUBLESIZE);

    return 0;
}

//
// Read functions
//

/**
 * Reads a byte value from a packet.
 *
 * @param *packet A pointer to a packet struct.
 * @param *dest The destination char to read the value into.
 *
 * @return A status code (-1 for failure).
 */
int read_byte(packet_t *packet, char *dest)
{
    if (packet->size == 0)
    {
        fprintf(stderr, "Failure when reading from packet: packet size is zero.\n");
        return -1;
    }

    *dest = packet->buffer[packet->read_head];

    packet->read_head += CHARSIZE;
    
    return 0;
}

/**
 * Reads an int16_t value from a packet.
 * 
 * @param *packet A pointer to a packet struct.
 * @param *dest The destination int16_t to read the value into.
 *
 * @return A status (-1 for failure).
 */
int read_int16(packet_t *packet, int16_t *dest)
{
    if (packet->size == 0)
    {
        fprintf(stderr, "Failure when reading from packet: packet size is zero.\n");
        return -1;
    }

    memcpy(dest, &(packet->buffer[packet->read_head]), INT16SIZE);

    packet->read_head += INT16SIZE;

    return 0;
}

/**
 * Reads an int32_t value from a packet.
 * 
 * @param *packet A pointer to a packet struct.
 * @param *dest The destination int32_t to read the value into.
 *
 * @return A status code (-1 for failure).
 */
int read_int32(packet_t *packet, int32_t *dest)
{
    if (packet->size == 0)
    {
        fprintf(stderr, "Failure when reading from packet: packet size is zero.\n");
        return -1;
    }

    memcpy(dest, &(packet->buffer[packet->read_head]), INT32SIZE);

    packet->read_head += INT32SIZE;

    return 0;
}

/**
 * Reads an int64_t value from a packet.
 * 
 * @param *packet A pointer to a packet struct.
 * @param *dest The destination int64_t to read the value into.
 *
 * @return A status code (-1 for failure).
 */
int read_int64(packet_t *packet, int64_t *dest)
{
    if (packet->size == 0)
    {
        fprintf(stderr, "Failure when reading from packet: packet size is zero.\n");
        return -1;
    }

    memcpy(dest, &(packet->buffer[packet->read_head]), INT64SIZE);

    packet->read_head += INT64SIZE;

    return 0;
}

/** 
 * Reads a float value from a packet.
 *
 * @param *packet A pointer to a packet.
 * @param *dest The destination float to read the value into.
 *
 * @return A status code (-1 for failure).
 */
int read_float(packet_t *packet, float *dest)
{
    if (packet->size == 0)
    {
        fprintf(stderr, "Failure when reading from packet: packet size is zero.\n");
        return -1;
    }

    memcpy(dest, &(packet->buffer[packet->read_head]), FLOATSIZE);

    packet->read_head += FLOATSIZE;

    return 0;
}

/**
 * Reads a double value from a packet.
 *
 * @param *packet A pointer to a packet.
 * @param *dest The destination double to read the value into.
 *
 * @return A status code (-1 for failure);
 */
int read_double(packet_t *packet, double *dest)
{
    if (packet->size == 0)
    {
        fprintf(stderr, "Failure when reading from packet: packet size is zero.\n");
        return -1; 
    }

    memcpy(dest, &(packet->buffer[packet->read_head]), DOUBLESIZE);

    packet->read_head += DOUBLESIZE;

    return 0;
}

/**
 * Checks if a packet will be full when a new size is added to it.
 *
 * @param *packet A pointer to a packet struct.
 * @param new_size The size to add on to the packet size.
 *
 * @return A boolean determining if the packet is full or not.
 * 1 for yes, 0 for no.
 */
static int packet_full(packet_t *packet, int new_size)
{
    if (packet->size + new_size >= PACKET_SIZE)
    {
        return 1;
    }

    return 0;
}
