#ifndef MACHINETHREAD_H
#define MACHINETHREAD_H

#include "JsonController.h"
#include "FPDController.h"
#include "RawController.h"

extern void test_Home();

namespace firestep {

typedef class MachineThread : Thread {
    friend void test_Home();

protected:
    void displayStatus();
    char * buildStartupJson();
    Status executeEEPROM();
    size_t readEEPROM(uint8_t *eeprom_addr, char *dst, size_t maxLen);

public:
    Status status;
    Machine machine;
    JsonCommand command;
    RawController rawController;
    FPDController fpdController;
    JsonController *pController;
    bool printBannerOnIdle;

public:
    MachineThread();
    void setController(JsonController &controller);
    void setup(PinConfig pc);
    void loop();
    Status syncConfig();
    Status process(JsonCommand& jcmd);
    const char * updateController();
} MachineThread;

} // namespace firestep

#endif
