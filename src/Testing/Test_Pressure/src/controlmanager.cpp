#include "controlmanager.h"

ControlManager::ControlManager(void){}

int ControlManager::getBaudRate(void)
{
    return this->BAUD_RATE;
}

void ControlManager::loadInitDataFunction(FunctionPtr func) {
    this->init_data_func = func;
}

void ControlManager::loadCollectDataFunction(FunctionPtr func) {
    this->update_data_func = func;
}

void ControlManager::loadSendDataFunction(FunctionPtr func) {
    this->send_data_func = func;
}

void ControlManager::runInitDataFunction() {
    if (this->init_data_func != nullptr) {
        this->init_data_func();
    } else {
        Serial.println("Init Data Function Not Loaded");
    }
}
void ControlManager::runCollectDataFunction() {
    if (this->update_data_func != nullptr) {
        this->update_data_func();
    } else {
        Serial.println("Update Data Function Not Loaded");
    }
}
void ControlManager::runSendDataFunction() {
    if (this->send_data_func != nullptr) {
        this->send_data_func();
    } else {
        Serial.println("Send Data Function Not Loaded");
    }
}

void ControlManager::setSendData(bool send)
{
    this->send_data = send;
}

void ControlManager::checkStartTransmission(int CODE){
    if(CODE==this->START_TRANSMISSION_CODE){
        Serial.print("Start");
        setSendData(true);
        runInitDataFunction();
    }
}
void ControlManager::checkEndTransmission(int CODE){
    if(CODE==this->END_TRANSMISSION_CODE){
        Serial.print("End");
        setSendData(false);
    }
}

void ControlManager::sendDataTransmission(void){
    if (this->send_data){
        runCollectDataFunction();
        runSendDataFunction();
    }
}

void ControlManager::checkSerialMessagesIn(void) {
    static char message[this->MAX_MESSAGE_LENGTH];
    static unsigned int message_pos=0;
    
    char inByte = Serial.read();
    
    if (inByte != '\n'){
      message[message_pos] = inByte;
      message_pos++;
    } else {
        Serial.print("message: ");
        message[message_pos] = '\0';
        Serial.println(message);

        int CODE = atoi(message);

        checkStartTransmission(CODE);
        checkEndTransmission(CODE);

        message_pos = 0;
    }
}