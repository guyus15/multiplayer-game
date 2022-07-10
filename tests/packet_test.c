/*
 *  @file packet_test.c
 *  @brief A test file for testing packet-related functions.
 */

#include "packet.h"

#include <unitc.h>
#include <stdlib.h>
#include <string.h>

static packet_t *packet;

static void before_each()
{
    packet = create_packet(NONE);
}

static void after_each()
{
    free(packet);
}

// Test 1
static void test_create_packet()
{
    test_name("test_create_packet");

    // This test ensures that the create_packet() function works at intended.
    
    ASSERT_EQUAL(packet->type, NONE);
    ASSERT_EQUAL(packet->size, 0);
    ASSERT_EQUAL(packet->read_head, 0);
}

// Test 2
static void test_write_byte()
{
    test_name("test_write_byte");

    // This test ensures that when the packet buffer is empty, the write_byte
    // function fills up the first byte of the buffer with the given value.

    write_byte(packet, 'a');

    ASSERT_EQUAL(packet->buffer[0], 'a');
    ASSERT_EQUAL(packet->size, 1);
}


// Test 3
static void test_write_byte_after()
{
    test_name("test_write_byte_after");

    // This test ensures that when the packet buffer is not empty, the write_byte
    // function fills up the buffer after what it already contains with the 
    // given value.
   
    // Test data
    for (int i = 0; i < 10; i++)
    {
        write_byte(packet, '1' + i);
    }

    write_byte(packet, 'a');

    ASSERT_EQUAL(packet->buffer[10], 'a');
    ASSERT_EQUAL(packet->size, 11);
}

// Test 10
static void test_write_int16()
{
    test_name("test_write_int16");

    // This test ensures that when the packet buffer is empty, the write_int16
    // function fills up the buffer from the first position.

    write_int16(packet, 1000);

    // 1000 in binary: 0b0000001111101000

    ASSERT_EQUAL(packet->buffer[0], 0b11101000);
    ASSERT_EQUAL(packet->buffer[1], 0b00000011);
}

// Test 11
static void test_write_int16_after()
{
    test_name("test_write_int16_after");

    // This test ensures that when the packet buffer is not empty, the write_int16
    // function fills up the buffer after what it already contains with the
    // given value.
    
    // Fill up the buffer
    for (int i = 0; i < 5; i++)
    {
        write_byte(packet, '1' + i);
    }

    int size_save = packet->size;

    write_int16(packet, 8);

    ASSERT_EQUAL(packet->buffer[size_save], 0b00001000);
    ASSERT_EQUAL(packet->buffer[size_save + 1], 0);
}

// Test 4
static void test_write_int32()
{
    test_name("test_write_int32");

    // This test ensures that when the packet buffer is empty, the write_int32
    // function fills up the buffer from the first position.

    write_int32(packet, 10000);

    // 10000 in binary: 0b0010011100010000

    ASSERT_EQUAL(packet->buffer[0], 0b00010000);
    ASSERT_EQUAL(packet->buffer[1], 0b00100111);
    ASSERT_EQUAL(packet->buffer[2], 0);
    ASSERT_EQUAL(packet->buffer[3], 0);
}

// Test 5
static void test_write_int32_after()
{
    test_name("test_write_int32_after");

    // This test ensures that when the packet buffer is not empty, the write_int32
    // function fills up the buffer after what it already contains with the 
    // given value.
    
    // Fill up the buffer
    for (int i = 0; i < 5; i++)
    {
        write_byte(packet, '1' + i);
    }

    int size_save = packet->size;

    write_int32(packet, 8);

    ASSERT_EQUAL(packet->buffer[size_save], 0b00001000);
    ASSERT_EQUAL(packet->buffer[size_save + 1], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 2], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 3], 0);
}

// Test 12
static void test_write_int64()
{
    test_name("test_write_int64");

    // This test ensures that when the packet buffer is empty, the write_int64
    // function fills up the buffer from the first position.

    write_int64(packet, 100000);

    // 100000 in binary: 0b000000011000011010100000

    ASSERT_EQUAL(packet->buffer[0], 0b10100000);
    ASSERT_EQUAL(packet->buffer[1], 0b10000110);
    ASSERT_EQUAL(packet->buffer[2], 0b00000001);
    ASSERT_EQUAL(packet->buffer[3], 0);
    ASSERT_EQUAL(packet->buffer[4], 0);
    ASSERT_EQUAL(packet->buffer[5], 0);
    ASSERT_EQUAL(packet->buffer[6], 0);
    ASSERT_EQUAL(packet->buffer[7], 0);
}

// Test 13
static void test_write_int64_after()
{
    test_name("test_write_int64_after");

    // This test ensures that when the packet buffer is not empty, the write_int64
    // function fills up the buffer after what it already contains with the 
    // given value.
    
    // Fill up the buffer
    for (int i = 0; i < 5; i++)
    {
        write_byte(packet, '1' + i);
    }

    int size_save = packet->size;

    write_int64(packet, 8);

    ASSERT_EQUAL(packet->buffer[size_save], 0b00001000);
    ASSERT_EQUAL(packet->buffer[size_save + 1], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 2], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 3], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 4], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 5], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 6], 0);
    ASSERT_EQUAL(packet->buffer[size_save + 7], 0);
}

// Test 6
static void test_write_float()
{
    test_name("test_write_float");

    // This test ensures that when the packet buffer is empty, the write_float
    // function fills up the buffer from the first position, with the correct
    // bytes.
    
    write_float(packet, 10.0f);
    
    float test_float;
    memcpy(&test_float, packet->buffer, FLOATSIZE);

    ASSERT_EQUAL(test_float, 10.0f);
}

// Test 7
static void test_write_float_after()
{
    test_name("test_write_float_after");

    // This test ensures that when the packet buffer is not empty, the write_int32
    // function fills up the buffer after what it already contains with the 
    // given value.
    
    for (int i = 0; i < 5; i++)
    {
        write_byte(packet, '1' + i);
    }

    int size_save = packet->size;

    write_float(packet, 5.0f);

    float test_float;
    memcpy(&test_float, &(packet->buffer[size_save]), FLOATSIZE);

    ASSERT_EQUAL(test_float, 5.0f);
}

// Test 8
static void test_write_double()
{
    test_name("test_write_double");

    // This test ensures that when the packet buffer is empty, the write_double
    // function fills up the buffer from the first position, with the correct
    // bytes.

    write_double(packet, 15.0);
    
    double test_double;
    memcpy(&test_double, packet->buffer, DOUBLESIZE);

    ASSERT_EQUAL(test_double, 15.0);
}

// Test 9
static void test_write_double_after()
{
    test_name("test_write_double_after");

    // This test ensures that when the packet buffer is not empty, the write_int32
    // function fills up the buffer after what it already contains with the 
    // given value.

    for (int i = 0; i < 5; i++)
    {
        write_byte(packet, '1' + i);
    }

    int size_save = packet->size;

    write_double(packet, 10.5);

    double test_double;
    memcpy(&test_double, &(packet->buffer[size_save]), DOUBLESIZE);

    ASSERT_EQUAL(test_double, 10.5);
}

// Test 14
static void test_read_byte()
{   
    test_name("test_read_byte");

    // This test ensures that when the function read_byte is called, it will
    // return the correct value from a packet's buffer.
    
    write_byte(packet, 'a');

    char read_value;
    read_byte(packet, &read_value);

    ASSERT_EQUAL(read_value, 'a');
}

// Test 15
static void test_read_int16()
{
    test_name("test_read_int16");

    // This test ensures that when the function read_int16 is called, it will
    // return correct value from a packet's buffer.

    write_int16(packet, 32767);

    int16_t read_value;
    read_int16(packet, &read_value);

    ASSERT_EQUAL(read_value, 32767);
}

// Test 16
static void test_read_int32()
{
    test_name("test_read_int32");

    // This test ensures that when the function read_int32 is called, it will
    // return correct value from a packet's buffer.

    write_int32(packet, 2147483647);

    int32_t read_value;
    read_int32(packet, &read_value);

    ASSERT_EQUAL(read_value, 2147483647);
}

// Test 17
static void test_read_int64()
{
    test_name("test_read_int64");

    // This test ensures that when the function read_int64 is called, it will
    // return correct value from a packet's buffer.

    write_int64(packet, 9223372036854775807);

    int64_t read_value;
    read_int64(packet, &read_value);

    ASSERT_LEQUAL(read_value, 9223372036854775807);
}

// Test 18
static void test_read_float()
{
    test_name("test_read_float");

    // This test ensures that when the function read_float is called, it will
    // return correct value from a packet's buffer.

    write_float(packet, 50.0f);

    float read_value;
    read_float(packet, &read_value);

    ASSERT_FEQUAL(read_value, 50.0f);
}

// Test 19
static void test_read_double()
{
    test_name("test_read_double");

    // This test ensures that when the function read_double is called, it will
    // return correct values from a packet's buffer.

    write_double(packet, 25.0);

    double read_value;
    read_double(packet, &read_value);

    ASSERT_FEQUAL(read_value, 25.0);
}

#include <stdio.h>

// Test 20
static void test_read_and_write_all_types()
{
    test_name("test_read_and_write_all_types");

    // This test ensures that the reading and writing of a packet behaves
    // as expected when we read and write with every type.
    
    // Write
    write_byte(packet, 'a');
    write_int16(packet, 8);
    write_int32(packet, 10000);
    write_int64(packet, 1000000);
    write_float(packet, 100.0f);
    write_double(packet, 10.0000);

    char read_byte_value;
    read_byte(packet, &read_byte_value);

    int16_t read_int16_value;
    read_int16(packet, &read_int16_value);

    int32_t read_int32_value;
    read_int32(packet, &read_int32_value);

    int64_t read_int64_value;
    read_int64(packet, &read_int64_value);

    float read_float_value;
    read_float(packet, &read_float_value);

    double read_double_value;
    read_double(packet, &read_double_value);

    ASSERT_EQUAL(read_byte_value, 'a');
    ASSERT_EQUAL(read_int16_value, 8);
    ASSERT_EQUAL(read_int32_value, 10000);
    ASSERT_LEQUAL(read_int64_value, 1000000);
    ASSERT_FEQUAL(read_float_value, 100.0f);
    ASSERT_FEQUAL(read_double_value, 10.0000);
}

// Test 21
static void test_writing_to_full_packet()
{
    test_name("test_writing_to_full_packet");

    // This test ensures that when writing to a full packet, the called write
    // function returns -1 status code.

    // Fill packet
    for (int i = 0; i < PACKET_SIZE; i++)
    {
        write_byte(packet, '1' + i);
    }

    int status = write_byte(packet, 'a');

    ASSERT_EQUAL(status, -1);
}

// Test 22
static void test_reading_from_empty_packet()
{
    test_name("test_reading_from_empty_packet");

    // This test ensures that when reading from an empty packet, the called read
    // function returns a -1 status code.

    char read_value;
    int status = read_byte(packet, &read_value);

    ASSERT_EQUAL(status, -1);
}

// Test 23
static void test_get_packet_type()
{
    test_name("test_get_packet_type");

    // This test ensures that when calling the get_packet_type() function,
    // the expected packet type is returned.

    ASSERT_EQUAL(get_packet_type(packet), NONE);
}

int main()
{
    set_before_each(before_each);
    set_after_each(after_each);   

    void (*tests[])() =
    {
        test_create_packet,
        test_write_byte,
        test_write_byte_after,
        test_write_int16,
        test_write_int16_after,
        test_write_int32,
        test_write_int32_after,
        test_write_int64,
        test_write_int64_after,
        test_write_float,
        test_write_float_after,
        test_write_double,
        test_write_double_after,
        test_read_byte,
        test_read_int16,
        test_read_int32,
        test_read_int64,
        test_read_float,
        test_read_double,
        test_read_and_write_all_types,
        test_writing_to_full_packet,
        test_reading_from_empty_packet,
        test_get_packet_type
    };

    run_tests(tests, 23);
}
