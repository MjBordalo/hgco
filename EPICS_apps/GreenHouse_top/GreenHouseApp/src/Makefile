TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = GreenHouse
# GreenHouse.dbd will be created and installed
DBD += GreenHouse.dbd

# GreenHouse.dbd will be made up from these files:
GreenHouse_DBD += base.dbd

# Include dbd files from all support applications:
GreenHouse_DBD += asyn.dbd
GreenHouse_DBD += stream.dbd
GreenHouse_DBD += drvAsynSerialPort.dbd
GreenHouse_DBD += asSupport.dbd
#GreenHouse_DBD += xxx.dbd

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
# This is required for Windows DLL builds.
GreenHouse_SRCS += dbSubExample.c

GreenHouse_DBD += dbSubExample.dbd

# Add all the support libraries needed by this IOC
GreenHouse_LIBS += autosave

# GreenHouse_registerRecordDeviceDriver.cpp derives from GreenHouse.dbd
GreenHouse_SRCS += GreenHouse_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
GreenHouse_SRCS_DEFAULT += GreenHouseMain.cpp
GreenHouse_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#GreenHouse_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
GreenHouse_LIBS += $(EPICS_BASE_IOC_LIBS)
GreenHouse_LIBS += asyn
GreenHouse_LIBS += stream

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
