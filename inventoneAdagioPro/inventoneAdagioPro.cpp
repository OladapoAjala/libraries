#include "inventoneAdagioPro.h"
#include "AdagioPro.h"

void inventoneAdagioPro::setupAdagioPro() {
    AdagioPro::Initialize();
}

void inventoneAdagioPro::turnLampOn() {
    AdagioPro::AllLampsOn();
}

void inventoneAdagioPro::turnLampOff() {
    AdagioPro::AllLampsOff();
}

void inventoneAdagioPro::AutoSyncronize() {
    AdagioPro::AutoSyncronize();
}

void inventoneAdagioPro::RGB(int red, int green, int blue) {
    AdagioPro::SetRGB(red, green, blue);
}