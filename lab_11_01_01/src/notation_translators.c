#include <stdio.h>
#include <string.h>

char num_to_hex_value(int num)
{
    char translated_char;
    if (num >= 0 && num <= 9)
        translated_char = '0' + (char)num;
    else if (num >= 10 && num <= 15)
        translated_char = 'a' + (num - 10);
    else
        translated_char = '?';

    return translated_char;
}

void reverse_string(char *str, int length)
{
    for (int start = 0, end = length - 1; start < end; start++, end--)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }
}

void int_to_string(int num, char *buffer, int buffer_size)
{
    int index = 0;
    int is_negative = 0;
    unsigned int unum;
    
    if (num < 0) 
    {
        is_negative = 1;
        unum = (unsigned int)(-num);
    }
    else if (num != 0)
        unum = (unsigned int)num;

    if (num == 0) 
    {
        buffer[0] = buffer_size > 0 ? '0' : '\0';
        if (buffer_size > 1)
            buffer[1] = '\0';
    }
    else
    {
        for (; unum > 0 && index < buffer_size - 1; unum /= 10)
            buffer[index++] = '0' + (unum % 10);
    
        if (is_negative && index < buffer_size - 1)
            buffer[index++] = '-';
    
        buffer[index] = '\0';
        reverse_string(buffer, index);
    }
}

void int_to_hex_string(int num, char *buffer, int buffer_size)
{
    unsigned int unum = (unsigned int)num;
    int index = 0;
    
    if (unum == 0) 
    {
        buffer[0] = (buffer_size > 0) ? '0' : '\0';
        if (buffer_size > 1) 
            buffer[1] = '\0';
    }
    else
    {
        for (; unum > 0 && index < buffer_size - 1; unum /= 16)
            buffer[index++] = num_to_hex_value(unum % 16);
    
        buffer[index] = '\0';
        reverse_string(buffer, index);
    }
}

void int_to_oct_string(int num, char *buffer, int buffer_size)
{
    unsigned int unum = (unsigned int)num;
    int index = 0;
    
    if (unum == 0) 
    {
        buffer[0] = (buffer_size > 0) ? '0' : '\0';
        if (buffer_size > 1) 
            buffer[1] = '\0';
    }
    else
    {
        for (; unum > 0 && index < buffer_size - 1; unum /= 8)
            buffer[index++] = '0' + (unum % 8);
    
        buffer[index] = '\0';
        reverse_string(buffer, index);
    }
}