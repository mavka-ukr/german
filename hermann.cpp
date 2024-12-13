#include <cstdio>

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