#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Light {
private:
    bool isOn;
public:
    Light() : isOn(false) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    string getStatus() const { return isOn ? "On" : "Off"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};


class Thermostat {
private:
    int temperature;
public:
    Thermostat() : temperature(20) {}

    void setTemperature(int temp) { temperature = temp; }
    int getTemperature() const { return temperature; }
};


class SecuritySystem {
private:
    bool isArmed;
public:
    SecuritySystem() : isArmed(false) {}

    void arm() { isArmed = true; }
    void disarm() { isArmed = false; }
    string getStatus() const { return isArmed ? "Armed" : "Disarmed"; }
    bool getState() const { return isArmed; }
    void setState(bool state) { isArmed = state; }
};


class Curtains {
private:
    bool isUp;
public:
    Curtains() : isUp(false) {}

    void raise() { isUp = true; }
    void lower() { isUp = false; }
    string getStatus() const { return isUp ? "Raised" : "Lowered"; }
    bool getState() const { return isUp; }
    void setState(bool state) { isUp = state; }
};


class AirConditioner {
private:
    bool isOn;
public:
    AirConditioner() : isOn(false) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    string getStatus() const { return isOn ? "On" : "Off"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};

class SmartHome {
private:
    Light light;
    Thermostat thermostat;
    SecuritySystem securitySystem;
    Curtains curtains;
    AirConditioner airConditioner;
    const string stateFile = "home_state.txt";

public:
    SmartHome() { loadState(); }

    ~SmartHome() { saveState(); }

    void controlLight(bool state) { state ? light.turnOn() : light.turnOff(); }
    void setTemperature(int temp) { thermostat.setTemperature(temp); }
    void controlSecurity(bool state) { state ? securitySystem.arm() : securitySystem.disarm(); }
    void controlCurtains(bool state) { state ? curtains.raise() : curtains.lower(); }
    void controlAirConditioner(bool state) { state ? airConditioner.turnOn() : airConditioner.turnOff(); }

    void displayStatus() const {
        cout << "Current State:\n";
        cout << "Light: " << light.getStatus() << "\n";
        cout << "Temperature: " << thermostat.getTemperature() << "°C\n";
        cout << "Security System: " << securitySystem.getStatus() << "\n";
        cout << "Curtains: " << curtains.getStatus() << "\n";
        cout << "Air Conditioner: " << airConditioner.getStatus() << "\n";
    }

    void saveState() const {
        ofstream file(stateFile);
        if (file.is_open()) {
            file << light.getState() << "\n";
            file << thermostat.getTemperature() << "\n";
            file << securitySystem.getState() << "\n";
            file << curtains.getState() << "\n";
            file << airConditioner.getState() << "\n";
            file.close();
            cout << "State saved to " << stateFile << ".\n";
        }
    }

    void loadState() {
        ifstream file(stateFile);
        if (file.is_open()) {
            bool lightState, securityState, curtainsState, acState;
            int temp;

            file >> lightState >> temp >> securityState >> curtainsState >> acState;

            light.setState(lightState);
            thermostat.setTemperature(temp);
            securitySystem.setState(securityState);
            curtains.setState(curtainsState);
            airConditioner.setState(acState);

            file.close();
            cout << "State loaded from " << stateFile << ".\n";
        } else {
            cout << "No previous state file found. Using default settings.\n";
        }
    }
};

void userInterface(SmartHome& home) {
    int choice;
    do {
        home.displayStatus();
        cout << "Choose an action:\n";
        cout << "1. Turn on light\n";
        cout << "2. Turn off light\n";
        cout << "3. Set temperature\n";
        cout << "4. Arm security system\n";
        cout << "5. Disarm security system\n";
        cout << "6. Raise curtains\n";
        cout << "7. Lower curtains\n";
        cout << "8. Turn on air conditioner\n";
        cout << "9. Turn off air conditioner\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: home.controlLight(true); break;
            case 2: home.controlLight(false); break;
            case 3: {
                int temp;
                cout << "Enter temperature: ";
                cin >> temp;
                home.setTemperature(temp);
                break;
            }
            case 4: home.controlSecurity(true); break;
            case 5: home.controlSecurity(false); break;
            case 6: home.controlCurtains(true); break;
            case 7: home.controlCurtains(false); break;
            case 8: home.controlAirConditioner(true); break;
            case 9: home.controlAirConditioner(false); break;
            case 10: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);
}

int main() {
    SmartHome home;
    userInterface(home);
    return 0;
}
