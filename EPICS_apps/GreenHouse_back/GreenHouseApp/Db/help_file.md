# author: Miguel Bordalo
#
# This document describes all the PV fields used (short description)
#
#
# used fields description:
#	DTYP - Device Type can be :
# INP/OUT - Where to read/write. It can also be a constant in that case specify
#						DTYP as Soft Channel(specified by defaut)
# DESC - Variable description
# PREC - Display Precision e.g: 1 shows 1 decimal precision
# SCAN - Periodicity to update VAL
# LOPR / HOPR - Low/High Operating Range
# ADEL - Archive Deadband
# PINI - Process at Initialization
# EGU - Engineering units name
# LOLO, LOW, HIGH, HIHI - Alarm Limits
# LLSV, LSV, HSV, HHSV - Alarm Associated severities
# OMSL -	Output Mode Select can be closed_loop or supervisory
#         If supervisory is specified, the value in the VAL field can be set
#					externally via dbPuts at run-time. If closed_loop is specified, the
#					VAL field's value is obtained from the address specified in the
#					desired output location field (DOL)
# OIF -  Incremental or Full
#					decides whether the value obtained from DOL is an increment to be
#					added to the current VAL or if the value obtained from DOL is the
#					actual value.
# ASLO & AOFF - Specify the Slope and offset Changing the pv VAL field according to:
#								VAL = VAL*ASLO + AOFF

# Specific records for:

# bi record
# ZSV; OSV; COSV - Zero Severity, One Severity; Change of State Severity.
#									The possible values for these fields are NO ALARM, MINOR, and MAJOR.

#ao record
# DOL - Desired output Link: The value where that the ao value will take if in closed_loop mode
