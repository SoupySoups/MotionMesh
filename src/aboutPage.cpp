#include "aboutPage.h"

String AboutPage::getMacAddress() {
   uint8_t baseMac[6];

   // Get MAC address for WiFi station
   esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

   char baseMacChr[18] = {0};
   sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);

   String macAddress = String(baseMacChr);

   return String(baseMacChr);
}

AboutPage::AboutPage() {
    // Fill device information
    char heapStr[32] = {0};
    char psramStr[32] = {0};

    sprintf(heapStr, "%d bytes (%.2f%% left)", ESP.getFreeHeap(), (ESP.getFreeHeap() * 100.0) / ESP.getHeapSize());
    sprintf(psramStr, "%d bytes (%.2f%% left)", ESP.getFreePsram(), (ESP.getFreePsram() * 100.0) / ESP.getPsramSize());

    lv_label_set_text_fmt(uic_DeviceInformation, "Board ID: %s\nCPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)\nSDK version: %s\nLVGL Version: %d.%d.%d\nMAC Address: %s\n\nFree heap: %s\nFree PSRAM: %s",
        BOARD_NAME,
        ESP.getChipModel(), ESP.getChipRevision(),
        getCpuFrequencyMhz(), ESP.getChipCores(),
        ESP.getSdkVersion(),
        LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH,
        getMacAddress().c_str(),
        heapStr,
        psramStr
    );

    lv_obj_set_style_text_font(uic_DeviceInformation, &lv_font_montserrat_12, 0);

    // // To use third party libraries, enable the define in lv_conf.h: #define LV_USE_QRCODE 1
    lv_obj_t * qr = lv_qrcode_create(uic_qrPlaceholder, 200, lv_color_hex3(0xeef), lv_color_hex3(0x00));
    lv_qrcode_update(qr, QR_LINK, strlen(QR_LINK));
    lv_label_set_text(uic_qrLabel, QR_LINK_SHORT);
    lv_obj_set_style_text_font(uic_qrLabel, &lv_font_montserrat_12, 0);
}