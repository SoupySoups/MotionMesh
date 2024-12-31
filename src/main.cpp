#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include "joystick.h"
#include "aboutPage.h"
// #include "MAX17048.h"
#include "Adafruit_MAX1704X.h"

TwoWire Wire2 = TwoWire(1);

// MAX17048 pwr_mgmt;
Adafruit_MAX17048 maxlipo;

auto lv_last_tick = millis();

static lv_indev_drv_t indev_drv;
lv_indev_t * indev;

// Joystick joystick = Joystick(17, 18, 13, 400, false, 100);

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
    // if (analogRead(13) >= 212 || analogRead(13) <= 812) {
    //     data->state = LV_INDEV_STATE_PRESSED;
    // } else {
    //     data->state = LV_INDEV_STATE_RELEASED;
    // }

    // JoystickData d = joystick.read();

    // data->point.x = d.x;
    // data->point.y = d.y;

    // Serial.print("x: ");
    // Serial.print(data->point.x);
    // Serial.print(", y: ");
    // Serial.println(data->point.y);
}

void OnInvertJoystickCheckboxChecked(lv_event_t *e) {
    // if (lv_obj_has_state(ui_InvertJoystickCheckbox, LV_STATE_CHECKED)) {
    //     joystick.setInvert(true);
    // } else {
    //     joystick.setInvert(false);
    // }
}

void OnJoystickSensitivitySliderChange(lv_event_t *e) {
    int value = lv_slider_get_value(ui_JoystickSensitivitySlider);
    // joystick.setSensitivity(value);

    // if (value != 400) {
    //     lv_obj_clear_flag(ui_JoystickSensitivitySliderResetButton, LV_OBJ_FLAG_HIDDEN);
    // } else {
    //     lv_obj_add_flag(ui_JoystickSensitivitySliderResetButton, LV_OBJ_FLAG_HIDDEN);
    // }
}

void JoystickSensitivitySliderResetButtonClicked(lv_event_t *e) {
    // lv_slider_set_value(ui_JoystickSensitivitySlider, 400, LV_ANIM_ON);
    // lv_obj_add_flag(ui_JoystickSensitivitySliderResetButton, LV_OBJ_FLAG_HIDDEN);
}

static void event_cb(lv_event_t * e) {
    lv_obj_t * obj = lv_event_get_current_target(e);
    Serial.printf("Button %s clicked\n", lv_msgbox_get_active_btn_text(obj));
}

void OnCalibrateButtonClicked(lv_event_t *e) {
    static const char * btns[] = {"Calibrate", "Cancel"};

    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Note", "Do not touch the joystick while calibrating!", btns, true);
    lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);
}

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Serial.println("MeshPilot ");

    smartdisplay_init();

    __attribute__((unused)) auto disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISP_ROT_180); // Rotate the display 180 degrees

    ui_init();
    // Disable tabview scroll
    lv_obj_clear_flag(lv_tabview_get_content(uic_PageSelector), LV_OBJ_FLAG_SCROLLABLE);

    Wire2.begin(18, 17);
    // pwr_mgmt.attatch(Wire2);
    maxlipo.begin(&Wire2);

    // // Initialize the input device driver
    // joystick.Calibrate();

    // joystick.setXRange(0, 800);
    // joystick.setYRange(0, 480);

    // lv_indev_drv_init(&indev_drv);
    // indev = lv_indev_drv_register(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = my_input_read;

    // lv_obj_t * cursor_obj = lv_img_create(lv_scr_act());       /*Create an image object for the cursor */
    // lv_img_set_src(cursor_obj, &ui_img_pointer_png);             /*Set the image source*/
    // lv_indev_set_cursor(indev, cursor_obj);  

    AboutPage();
}

void loop() {
    auto const now = millis();

    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;

    // Update the UI
    lv_timer_handler();

    // lv_label_set_text_fmt(uic_battInfo, "Hello World! %d", pwr_mgmt.percent());
    // Serial.print(F("Found MAX17048"));
    // Serial.print(F(" with Chip ID: 0x")); 
    // Serial.println(maxlipo.getChipID(), HEX);
    Serial.print("Firmware Version: ");
    Serial.println(AUTO_VERSION);
}

