#pragma once
#include <ui/ui.h>
#include <Arduino.h>

#define QR_LINK "https://github.com/SoupySoups/OCDR"
#define QR_LINK_SHORT "github.com/SoupySoups/OCDR"

class AboutPage {
    private:
        static String getMacAddress();
    public:
        AboutPage();
};