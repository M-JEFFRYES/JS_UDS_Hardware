#ifndef ControlManager_h
#define ControlManager_h

#include <Arduino.h>

class ControlManager
{
	public:
    	typedef void (*FunctionPtr)();

		ControlManager(void);
		int getBaudRate(void);
		void setSendData(bool);
		void checkSerialMessagesIn(void);
		void loadInitDataFunction(FunctionPtr);
		void loadCollectDataFunction(FunctionPtr);
		void loadSendDataFunction(FunctionPtr);
		void runInitDataFunction(void);
		void runCollectDataFunction(void);
		void runSendDataFunction(void);
		void sendDataTransmission(void);

	private:
		void checkStartTransmission(int);
		void checkEndTransmission(int);

		FunctionPtr init_data_func;
		FunctionPtr update_data_func;
		FunctionPtr send_data_func;
		 
		static const int BAUD_RATE = 9600;
		static const int START_TRANSMISSION_CODE = 333;
		static const int END_TRANSMISSION_CODE = 444;
		static const int MAX_MESSAGE_LENGTH = 5;
		
		bool send_data;


		// Function pointer type for the loaded function


};

#endif
