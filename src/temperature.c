#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PATH_LED_0 "/sys/class/leds/d0/brightness"
#define PATH_LED_1 "/sys/class/leds/d1/brightness"
#define PATH_LED_2 "/sys/class/leds/d2/brightness"
#define PATH_LED_3 "/sys/class/leds/d3/brightness"
#define PATH_LED_4 "/sys/class/leds/d4/brightness"
#define PATH_LED_5 "/sys/class/leds/d5/brightness"
#define PATH_LED_6 "/sys/class/leds/d6/brightness"
#define PATH_LED_7 "/sys/class/leds/d7/brightness"

#define ON "255"
#define OFF "0"

#define PATH_TEMP_RAW "/sys/bus/iio/devices/iio:device0/in_temp_raw"
#define PATH_TEMP_SCALE "/sys/bus/iio/devices/iio:device0/in_temp_scale"

char* paths[8] = {PATH_LED_0, PATH_LED_1, PATH_LED_2, PATH_LED_3, PATH_LED_4, PATH_LED_5, PATH_LED_6, PATH_LED_7};

void set_led(char* path, char* value) {
    FILE* file = NULL;

    file = fopen(path, "w+");
    
    if(file != NULL) {
        fputs(value, file);
        fclose(file);
    }
    else {
        printf("[set_leds] Cannot open file %s\n", path);
    }
}

uint32_t get_temperature_raw() {
    FILE* file = NULL;

    int buffer_length = 255;
    char buffer[buffer_length];
    
    file = fopen(PATH_TEMP_RAW, "r+");
    
    if(file != NULL) {
        fgets(buffer, buffer_length, file);
        fclose(file);
        uint32_t raw = (uint32_t)atoi(buffer);
        return raw;
    }
    else {
        printf("[get_temperature_raw] Cannot open file %s\n", PATH_TEMP_RAW);
    }

    return 0;
}

float get_temperature_scale() {
    FILE* file = NULL;

    int buffer_length = 255;
    char buffer[buffer_length];
    
    file = fopen(PATH_TEMP_SCALE, "r+");
    
    if(file != NULL) {
        fgets(buffer, buffer_length, file);
        fclose(file);
        float raw = (float)atof(buffer);
        return raw;
    }
    else {
        printf("[get_temperature_scale] Cannot open file %s\n", PATH_TEMP_SCALE);
    }

    return 0.0f;
}

void set_leds_from_temperature(float temperature) {
    uint8_t integer_temperature = (int) temperature;

    uint8_t nb_leds = integer_temperature - 28;

    for(int i=0; i<nb_leds; i++) {
        set_led(paths[i], ON);
    }

    for(int i=nb_leds; i<(int) (sizeof(paths)/sizeof(paths[0])); i++) {
        set_led(paths[i], OFF);
    }
}

void do_temperature_scan() {

    while(1) {
        uint32_t temperature_raw = get_temperature_raw();
        float temperature_scale = get_temperature_scale();

        float temperature = temperature_raw * temperature_scale;
        set_leds_from_temperature(temperature);
        
        usleep(200000);
    }
}

int main(int argc, char *argv[]) {

    do_temperature_scan();

    return 0;
}