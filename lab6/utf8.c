#include <stdint.h>
#include <stdio.h>
#include "utf8.h"


void decode_utf8(const char* s) {

    size_t i = 0;


    while (s[i] != '\0') {

        uint8_t b = (uint8_t)s[i];
        uint32_t codepoint;
        uint8_t n_bytes;


        if ((b & 0x80) == 0x00) {

            
            codepoint = b;
            n_bytes = 1;


        } else if ((b & 0xE0) == 0xC0) {

           
            codepoint = (b & 0x1F) << 6;
            codepoint |= ((uint8_t)s[i+1] & 0x3F);
            n_bytes = 2;


        } else if ((b & 0xF0) == 0xE0) {
            

            codepoint = (b & 0x0F) << 12;
            codepoint |= ((uint8_t)s[i+1] & 0x3F) << 6;
            codepoint |= ((uint8_t)s[i+2] & 0x3F);
            n_bytes = 3;


        } else if ((b & 0xF8) == 0xF0) {
            

            codepoint = (b & 0x07) << 18;
            codepoint |= ((uint8_t)s[i+1] & 0x3F) << 12;
            codepoint |= ((uint8_t)s[i+2] & 0x3F) << 6;
            codepoint |= ((uint8_t)s[i+3] & 0x3F);
            n_bytes = 4;


        } else {
            
            printf("<li>Unknown byte, 0x%02hhx</li>\n", s[i]);
            i++;
            continue;

        }


        report_character(codepoint, n_bytes);
        i += n_bytes;


    }

    
}