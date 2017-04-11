TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord

# Install xxxSupport.dbd into <top>/dbd
DBD += xxxSupport.dbd

# Build an IOC support library
LIBRARY_IOC += topExemploSupport

# Compile and add the code to the support library
topExemploSupport_SRCS += xxxRecord.c
topExemploSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
# This is required for Windows DLL builds.
topExemploSupport_SRCS += dbSubExample.c
topExemploSupport_SRCS += topExemploHello.c
topExemploSupport_SRCS += initTrace.c

topExemploSupport_LIBS += $(EPICS_BASE_IOC_LIBS)


# Build the IOC application
PROD_IOC = topExemplo

# topExemplo.dbd will be created and installed
DBD += topExemplo.dbd

# topExemplo.dbd will include these files:
topExemplo_DBD += base.dbd
topExemplo_DBD += xxxSupport.dbd
topExemplo_DBD += dbSubExample.dbd
topExemplo_DBD += topExemploHello.dbd
topExemplo_DBD += initTrace.dbd

# topExemplo_registerRecordDeviceDriver.cpp derives from topExemplo.dbd
topExemplo_SRCS += topExemplo_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
topExemplo_SRCS_DEFAULT += topExemploMain.cpp
topExemplo_SRCS_vxWorks += -nil-

# Link in the code from our support library
topExemplo_LIBS += topExemploSupport

# To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file
ifneq ($(SNCSEQ),)
    # Build sncExample into topExemploSupport
    sncExample_SNCFLAGS += +r
    topExemplo_DBD += sncExample.dbd
    # A .stt sequence program is *not* pre-processed:
    topExemploSupport_SRCS += sncExample.stt
    topExemploSupport_LIBS += seq pv
    topExemplo_LIBS += seq pv

    # Build sncProgram as a standalone program
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    # A .st sequence program *is* pre-processed:
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

# Finally link IOC to the EPICS Base libraries
topExemplo_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE

