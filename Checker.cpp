#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

enum Language { ENGLISH, GERMAN };
Language currentLanguage = ENGLISH;

const float TEMPERATURE_UPPER_LIMIT = 45;
const float SOC_UPPER_LIMIT = 80;
const float CHARGE_RATE_UPPER_LIMIT = 0.8;

const float TEMPERATURE_WARNING_TOLERANCE = 0.05 * TEMPERATURE_UPPER_LIMIT; // 5% of 45
const float SOC_WARNING_TOLERANCE = 0.05 * SOC_UPPER_LIMIT; // 5% of 80
const float CHARGE_RATE_WARNING_TOLERANCE = 0.05 * CHARGE_RATE_UPPER_LIMIT; // 5% of 0.8

string translate(const string& message) {
  if(currentLanguage == GERMAN) {
    if(message == "Temperature out of range!") return "Temperatur außerhalb des Bereichs!";
    if(message == "Approaching low temperature") return "Annäherung an niedrige Temperatur";
    if(message == "Approaching high temperature") return "Annäherung an hohe Temperatur";
    if(message == "State of Charge out of range!") return "Ladezustand außerhalb des Bereichs!";
    if(message == "Approaching discharge") return "Annäherung an Entladung";
    if(message == "Approaching charge-peak") return "Annäherung an Ladespitze";
    if(message == "Charge Rate out of range!") return "Laderate außerhalb des Bereichs!";
    if(message == "Approaching high charge rate") return "Annäherung an hohe Laderate";
  }
  return message;
}

void printMessage(const string& message) {
  cout << translate(message) << endl;
}

bool isTemperatureOk(float temperature) {
  if(temperature < 0 || temperature > TEMPERATURE_UPPER_LIMIT) {
    printMessage("Temperature out of range!");
    return false;
  }
  if(temperature >= 0 && temperature <= 0 + TEMPERATURE_WARNING_TOLERANCE) {
    printMessage("Approaching low temperature");
  }
  if(temperature >= TEMPERATURE_UPPER_LIMIT - TEMPERATURE_WARNING_TOLERANCE && temperature <= TEMPERATURE_UPPER_LIMIT) {
    printMessage("Approaching high temperature");
  }
  return true;
}

bool isSocOk(float soc) {
  if(soc < 20 || soc > SOC_UPPER_LIMIT) {
    printMessage("State of Charge out of range!");
    return false;
  }
  if(soc >= 20 && soc <= 20 + SOC_WARNING_TOLERANCE) {
    printMessage("Approaching discharge");
  }
  if(soc >= SOC_UPPER_LIMIT - SOC_WARNING_TOLERANCE && soc <= SOC_UPPER_LIMIT) {
    printMessage("Approaching charge-peak");
  }
  return true;
}

bool isChargeRateOk(float chargeRate) {
  if(chargeRate > CHARGE_RATE_UPPER_LIMIT) {
    printMessage("Charge Rate out of range!");
    return false;
  }
  if(chargeRate >= CHARGE_RATE_UPPER_LIMIT - CHARGE_RATE_WARNING_TOLERANCE && chargeRate <= CHARGE_RATE_UPPER_LIMIT) {
    printMessage("Approaching high charge rate");
  }
  return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return isTemperatureOk(temperature) && isSocOk(soc) && isChargeRateOk(chargeRate);
}

int main() {
  currentLanguage = ENGLISH; // Set language to English
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
  assert(batteryIsOk(-10, 50, 0.7) == false);
  assert(batteryIsOk(25, 85, 0.7) == false);
  assert(batteryIsOk(35, 25, 0.5) == true);
  assert(batteryIsOk(25, 70, 0.9) == false);

  currentLanguage = GERMAN; // Set language to German
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
  assert(batteryIsOk(-10, 50, 0.7) == false);
  assert(batteryIsOk(25, 85, 0.7) == false);
  assert(batteryIsOk(35, 25, 0.5) == true);
  assert(batteryIsOk(25, 70, 0.9) == false);
}
