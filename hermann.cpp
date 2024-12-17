#include <cstdio>
#include <cstdlib>

extern "C" void print_long(long value) {
    printf("%ld", value);
}

extern "C" void println_long(long value) {
    printf("%ld\n", value);
}

extern "C" size_t read_file(const char *filename, char **out_address) {
    FILE *file = fopen(filename, "r");
    if (file == nullptr) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *out_address = new char[size];
    fread(*out_address, 1, size, file);

    fclose(file);
    return size;
}

extern "C" unsigned char *mama_convert_utf32_to_utf8(unsigned int *utf32) {
    unsigned long len = 0;
    while (utf32[len] != 0) {
        len++;
    }
    unsigned char *utf8 = (unsigned char *) malloc(len * 4 + 1);
    unsigned char *utf8_start = utf8;
    for (int i = 0; i < len; i++) {
        unsigned int c = utf32[i];
        if (c < 0x80) {
            *utf8++ = c;
        } else if (c < 0x800) {
            *utf8++ = 0xC0 | c >> 6;
            *utf8++ = 0x80 | (c & 0x3F);
        } else if (c < 0x10000) {
            *utf8++ = 0xE0 | c >> 12;
            *utf8++ = 0x80 | (c >> 6 & 0x3F);
            *utf8++ = 0x80 | (c & 0x3F);
        } else {
            *utf8++ = 0xF0 | c >> 18;
            *utf8++ = 0x80 | (c >> 12 & 0x3F);
            *utf8++ = 0x80 | (c >> 6 & 0x3F);
            *utf8++ = 0x80 | (c & 0x3F);
        }
    }
    *utf8 = 0;
    return utf8_start;
}
