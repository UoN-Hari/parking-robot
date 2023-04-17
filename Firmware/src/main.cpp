#include <Arduino.h>
#include <launch_test_pkg/motor_msgs.h>

#define LED_PIN GPIO_NUM_13
#define DIR1_PIN GPIO_NUM_12
#define DIR2_PIN GPIO_NUM_14
#define PUL1_PIN GPIO_NUM_32
#define PUL2_PIN GPIO_NUM_33
#define PUL1_CHN 2
#define PUL2_CHN 4

#define STEP_SIZE 3200.0f
#define pulseTime(spd) (STEP_SIZE / (spd)) 

#define frequency2micros(f) (1e6/(f))
#define gpio_toggle_pin(pin) gpio_set_level((pin), !gpio_get_level(pin))

static launch_test_pkg::motor_msgs motorMsg;

static uint64_t current_micros;
static uint64_t prev_micros_led = 0;
static uint64_t prev_micros_serial = 0;


static void pinInit (void);
static void serial_callback (void);
void msg_clear (void);

void setup () {
    while (!Serial) {
        Serial.begin (921600);
    }
    Serial.onReceive (serial_callback, false);
    pinInit ();
}

void pinInit (void) {
    pinMode (LED_PIN, OUTPUT);

    pinMode (DIR1_PIN, OUTPUT);
    pinMode (DIR2_PIN, OUTPUT);
    pinMode (PUL1_PIN, OUTPUT);
    pinMode (PUL2_PIN, OUTPUT);

    ledcSetup (PUL1_CHN, 1000, 8);
    ledcSetup (PUL2_CHN, 1000, 8);
    ledcAttachPin (PUL1_PIN, PUL1_CHN);
    ledcAttachPin (PUL2_PIN, PUL2_CHN);
}

void loop () {
    current_micros = micros ();

    if (motorMsg.dir1 != 0) {
        gpio_set_level (DIR1_PIN, HIGH);
    } else {
        gpio_set_level (DIR1_PIN, LOW);
    }

    if (motorMsg.dir2 != 0) {
        gpio_set_level (DIR2_PIN, HIGH);
    } else {
        gpio_set_level (DIR2_PIN, LOW);
    }

    if (current_micros - prev_micros_led >= frequency2micros (1)) {
        gpio_toggle_pin (LED_PIN);
        prev_micros_led = current_micros;
    }

    ledcWriteTone (PUL1_CHN, (uint32_t)((float)motorMsg.angular1 * STEP_SIZE * 3.0f / 60.0f));
    ledcWriteTone (PUL2_CHN, (uint32_t)((float)motorMsg.angular2 * STEP_SIZE * 3.0f / 60.0f));

    vTaskDelay (pdMS_TO_TICKS (5));
}

void serial_callback () {
    uint8_t s_buffer[12]{};

#ifdef problem_may_be_here
    if (Serial) {
        Serial.read (s_buffer, 6);
        motorMsg.deserialize (s_buffer);
    } else {
        msg_clear ();
    }
#else
    Serial.read (s_buffer, 6);
    motorMsg.deserialize (s_buffer);
#endif
}


void msg_clear () {
    motorMsg.angular1 = 0;
    motorMsg.angular2 = 0;
    motorMsg.dir1 = 0;
    motorMsg.dir2 = 0;
}