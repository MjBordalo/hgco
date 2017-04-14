#!../../bin/linux-arm/GreenHouse

## You may have to change GreenHouse to something else
## everywhere it appears in this file

< envPaths

#Stream
epicsEnvSet(STREAM_PROTOCOL_PATH,".:../protocols")

#Autosave
epicsEnvSet(IOCNAME,"GreenHouse")
epicsEnvSet(SAVE_DIR,"/home/pi/hgco/EPICS_apps/GreenHouse_top/var/$(IOCNAME)")

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/GreenHouse.dbd"
GreenHouse_registerRecordDeviceDriver pdbbase

#Autosave
save_restoreSet_status_prefix("$(IOCNAME):")

set_requestfile_path("$(SAVE_DIR)")
set_savefile_path("$(SAVE_DIR)")

#set_savefile_path(startup)
#set_requestfile_path(startup, $(SAVE_DIR)”)
#set_requestfile_path(startup)

save_restoreSet_NumSeqFiles(3)
save_restoreSet_SeqPeriodInSeconds(600)
set_pass1_restoreFile("$(IOCNAME).sav")

#Asyn
drvAsynSerialPortConfigure("USB0","/dev/ttyUSB0",0,0,0)
asynSetOption("USB0",-1,"baud","115200")
asynSetOption("USB0",-1,"bits","8")
asynSetOption("USB0",-1,"parity","none")
asynSetOption("USB0",-1,"stop","1")
asynSetOption("USB0",-1,"clocal","Y")
asynSetOption("USB0",-1,"crtscts","N")

## Load record instances
dbLoadRecords("db/arduino.db","user=miHost,PORT=USB0")

cd ${AUTOSAVE}/asApp/Db
dbLoadRecords("save_restoreStatus.db","P=miHostAS:")

cd "${TOP}/iocBoot/${IOC}"
iocInit

#Autosave 
# Create request file and start periodic 'save’
makeAutosaveFileFromDbInfo("$(SAVE_DIR)/$(IOCNAME).req", "autosaveFields")
create_monitor_set("$(IOCNAME).req", 30)

## Start any sequence programs
#seq sncxxx,"user=piHost"
