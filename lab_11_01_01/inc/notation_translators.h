#ifndef NUM_SYS_TRANSLATORS_H__
#define NUM_SYS_TRANSLATORS_H__

char num_to_hex_value(int num);
void reversed_dec_to_oct(int num_dec, char *buffer, int buffer_size);
void reverse_string(char *str, int length);
void int_to_string(int num, char *buffer, int buffer_size);
void int_to_hex_string(int num, char *buffer, int buffer_size);
void int_to_oct_string(int num, char *buffer, int buffer_size);

#endif