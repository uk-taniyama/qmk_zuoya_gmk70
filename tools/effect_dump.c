#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define EEPROM_CUSTOM
#define EEPROM_SIZE 1024
#define RGB_MATRIX_ENABLE
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define LED_COUNT (MATRIX_ROWS * MATRIX_COLS)
#define RGB_MATRIX_LED_COUNT LED_COUNT
#define RGB_MATRIX_LED_PROCESS_LIMIT LED_COUNT

#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_RAIN

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#include "rgb_matrix.h"
#include "color.c"
#include "rgb_matrix.c"

typedef struct {
    uint8_t x;
    uint8_t y;
} led_t;

led_t g_leds[LED_COUNT];

typedef struct {
    uint8_t r, g, b;
} rgb_t;

led_config_t g_led_config;

void init_leds(void) {
    int i = 0;
    for (int y = 0; y < MATRIX_ROWS; y++) {
        for (int x = 0; x < MATRIX_COLS; x++) {
            g_led_config.matrix_co[y][x] = i;
            g_led_config.point[i].x      = x * 16;
            g_led_config.point[i].y      = y * 16;
            g_led_config.flags[i]        = LED_FLAG_ALL;
            g_leds[i]                    = (led_t){x, y};
            i++;
        }
    }
    rgb_matrix_config.enable = RGB_MATRIX_DEFAULT_ON;
    rgb_matrix_config.mode   = RGB_MATRIX_DEFAULT_MODE;
    rgb_matrix_config.hsv    = (HSV){RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL};
    rgb_matrix_config.speed  = RGB_MATRIX_DEFAULT_SPD;
    rgb_matrix_config.flags  = RGB_MATRIX_DEFAULT_FLAGS;
}

typedef struct effect_def_t {
    const char *name;
    bool (*effect_func)(effect_params_t *params);
} effect_def_t;

#define EFFECT_DEF(name) \
    { #name, name }

effect_def_t rgb_matrix_effects[] = {
    EFFECT_DEF(ALPHAS_MODS),
    EFFECT_DEF(GRADIENT_UP_DOWN),
    EFFECT_DEF(GRADIENT_LEFT_RIGHT),
    EFFECT_DEF(BREATHING),
    EFFECT_DEF(BAND_SAT),
    EFFECT_DEF(BAND_VAL),
    EFFECT_DEF(BAND_PINWHEEL_SAT),
    EFFECT_DEF(BAND_PINWHEEL_VAL),
    EFFECT_DEF(BAND_SPIRAL_SAT),
    EFFECT_DEF(BAND_SPIRAL_VAL),
    EFFECT_DEF(CYCLE_ALL),
    EFFECT_DEF(CYCLE_LEFT_RIGHT),
    EFFECT_DEF(CYCLE_UP_DOWN),
    EFFECT_DEF(RAINBOW_MOVING_CHEVRON),
    EFFECT_DEF(CYCLE_OUT_IN),
    EFFECT_DEF(CYCLE_OUT_IN_DUAL),
    EFFECT_DEF(CYCLE_PINWHEEL),
    EFFECT_DEF(CYCLE_SPIRAL),
    EFFECT_DEF(DUAL_BEACON),
    EFFECT_DEF(RAINBOW_BEACON),
    EFFECT_DEF(RAINBOW_PINWHEELS),
    EFFECT_DEF(FLOWER_BLOOMING),
    EFFECT_DEF(RAINDROPS),
    EFFECT_DEF(JELLYBEAN_RAINDROPS),
    EFFECT_DEF(HUE_BREATHING),
    EFFECT_DEF(HUE_PENDULUM),
    EFFECT_DEF(HUE_WAVE),
    EFFECT_DEF(PIXEL_FRACTAL),
    EFFECT_DEF(PIXEL_FLOW),
    EFFECT_DEF(PIXEL_RAIN),

    // EFFECT_DEF(TYPING_HEATMAP),
    // EFFECT_DEF(DIGITAL_RAIN),

    // EFFECT_DEF(SOLID_REACTIVE_SIMPLE),
    // EFFECT_DEF(SOLID_REACTIVE),
    // EFFECT_DEF(SOLID_REACTIVE_WIDE),
    // EFFECT_DEF(SOLID_REACTIVE_MULTIWIDE),
    // EFFECT_DEF(SOLID_REACTIVE_CROSS),
    // EFFECT_DEF(SOLID_REACTIVE_MULTICROSS),
    // EFFECT_DEF(SOLID_REACTIVE_NEXUS),
    // EFFECT_DEF(SOLID_REACTIVE_MULTINEXUS),
    // EFFECT_DEF(SPLASH),
    // EFFECT_DEF(MULTISPLASH),
    // EFFECT_DEF(SOLID_SPLASH),
    // EFFECT_DEF(SOLID_MULTISPLASH),
    {NULL, NULL} // End marker
};
#undef EFFECT_DEF

debug_config_t debug_config;

rgb_t led[LED_COUNT];

/* Perform any initialisation required for the other driver functions to work. */
void dummy_init(void) {
    fprintf(stderr, "Dummy RGB init\n");
}
/* Set the colour of a single LED in the buffer. */
void dummy_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index >= 0 && index < LED_COUNT) {
        led[index] = (rgb_t){r, g, b};
    }
}
/* Set the colour of all LEDS on the keyboard in the buffer. */
void dummy_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < LED_COUNT; i++) {
        led[i] = (rgb_t){r, g, b};
    }
}
/* Flush any buffered changes to the hardware. */
void dummy_flush(void) {
    fprintf(stderr, "Flush LED changes\n");
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {}
void eeprom_update_block(const void *buf, void *addr, size_t len) {}
bool is_keyboard_master(void) {
    return true;
}
uint32_t timer_read32(void) {
    return 0;
}
uint32_t timer_elapsed32(uint32_t timer) {
    return 0;
}
uint16_t rand16seed = 1337;

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = dummy_init,
    .flush         = dummy_flush,
    .set_color     = dummy_set_color,
    .set_color_all = dummy_set_color_all,
};

void print_frame(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        rgb_t c = led[i];
        printf("[0, %d, %d, %d]\n", c.r, c.g, c.b);
    }
    printf("[]\n");
}

void play_effect(effect_def_t *effect) {
    const int frames               = 1000;
    const int step                 = 127; // ms
    rgb_t     led_first[LED_COUNT] = {0};
    rgb_t     led_prev[LED_COUNT]  = {0};
    int       frame_count          = 0;

    effect_params_t effect_parms = {
        .init  = true,
        .iter  = 0,
        .flags = LED_FLAG_KEYLIGHT,
    };

    // effect name and matrix size
    printf("[\"%s\", %d, %d]\n", effect->name, MATRIX_ROWS, MATRIX_COLS);

    // initial led state
    memset(led, 0, sizeof(led));
    g_rgb_timer = 0;
    effect->effect_func(&effect_parms);
    print_frame();

    // store first and previous frame
    memcpy(led_first, led, sizeof(led));
    memcpy(led_prev, led, sizeof(led));

    for (int f = 0; f < frames && frame_count < 60; f++) {
        // effect led update
        memset(led, 0, sizeof(led));
        g_rgb_timer = f * step;
        effect->effect_func(&effect_parms);

        // skip if no updated
        if (memcmp(led, led_prev, sizeof(led)) == 0) {
            continue;
        }

        // check for looped effect
        if (memcmp(led, led_first, sizeof(led)) == 0) {
            // NOTE PIXEL_系以外のエフェクトの場合、最初のフレームと同じになったら終了
            if (memcmp(effect->name, "PIXEL_", 6) != 0) {
                break;
            }
        }

        // print frame and store previous
        print_frame();
        memcpy((void *)led_prev, (void *)led, sizeof(led));
        frame_count += 1;
    }
}

int main(void) {
    init_leds();

    for (effect_def_t *effect = rgb_matrix_effects; effect->name != NULL && effect->effect_func != NULL; effect++) {
        play_effect(effect);
    }

    return 0;
}
