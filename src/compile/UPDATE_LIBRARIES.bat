@echo off
echo Preparing to transfer libs ...

rem Parent dir
set "parentDir=C:\Users\mikej\OneDrive\Documents\PlatformIO\Projects\JS_UDS_Hardware\src"

rem Manger cpp file name
set "manageFileCppName=controlmanager.cpp"

rem Manger h file name
set "manageFileHName=controlmanager.h"

rem Manger cpp file
set "manageFileCpp=%parentDir%\compile\%manageFileCppName%"

rem Manger h file
set "manageFileH=%parentDir%\compile\%manageFileHName%"

echo Copying to Simulation scripts
copy "%manageFileCpp%" "%parentDir%\Simulation\Sim_Full_System\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Simulation\Sim_Full_System\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Simulation\Sim_Pressure\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Simulation\Sim_Pressure\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Simulation\Sim_Pump_Flowrate\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Simulation\Sim_Pump_Flowrate\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Simulation\Sim_Volume_Infused\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Simulation\Sim_Volume_Infused\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Simulation\Sim_Volume_Void\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Simulation\Sim_Volume_Void\src\%manageFileHName%"


echo Copying to Test scripts
copy "%manageFileCpp%" "%parentDir%\Testing\Test_Pressure\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Testing\Test_Pressure\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Testing\Test_Pump_Flowrate\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Testing\Test_Pump_Flowrate\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Testing\Test_Volume_Infused\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Testing\Test_Volume_Infused\src\%manageFileHName%"

copy "%manageFileCpp%" "%parentDir%\Testing\Test_Volume_Void\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\Testing\Test_Volume_Void\src\%manageFileHName%"

echo Copying to clinical investigation script
copy "%manageFileCpp%" "%parentDir%\UDS_Clinical_Investigation\src\%manageFileCppName%"
copy "%manageFileH%" "%parentDir%\UDS_Clinical_Investigation\src\%manageFileHName%"

echo ...
pause