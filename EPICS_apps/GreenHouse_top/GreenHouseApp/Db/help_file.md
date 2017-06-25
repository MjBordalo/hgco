# Help file for DB EPICS PV's definition
author: *Miguel Bordalo*

This document describes all the PV fields used (short description)

## Scanning specification
more [info](http://www.aps.anl.gov/epics/EpicsDocumentation/AppDevManuals/RecordRef/Recordref-5.html)

Scanning determines when a record is processed. Can be:
1. Periodic scanning occurs on set time intervals.
2. Event scanning occurs on either an I/O interrupt event or a user-defined event.
3. Passive scanning occurs when the records linked to the passive record are scanned, or when a value is "put" into a passive record through the database access routines.

## used fields description:
*	DTYP - Device Type can be :
* INP/OUT - Where to read/write. It can also be a constant in that case specify
						DTYP as Soft Channel(specified by defaut)
 if they specify PP, they will cause the record whose address they contain to process when the records containing them are processed
* DESC - Variable description
* PREC - Display Precision e.g: 1 shows 1 decimal precision
* SCAN - Periodicity to update VAL. Or specify passive if other PV will cause it to process. [Passive,Event,I/O Intr, 10 secound..]
* FLNK - Forward links are always process passive, so they cannot specify NPP.
* LOPR / HOPR - Low/High Operating Range
* ADEL - Archive Deadband
* PINI - Process at Initialization
* EGU - Engineering units name
* LOLO, LOW, HIGH, HIHI - Alarm Limits
* LLSV, LSV, HSV, HHSV - Alarm Associated severities
* OMSL -	Output Mode Select can be closed_loop or supervisory
         If supervisory is specified, the value in the VAL field can be set
					externally via dbPuts at run-time. If closed_loop is specified, the
					VAL field's value is obtained from the address specified in the
					desired output location field (DOL)
* OIF -  Incremental or Full
					decides whether the value obtained from DOL is an increment to be					added to the current VAL or if the value obtained from DOL is the
					actual value.
* ASLO & AOFF - Specify the Slope and offset Changing the pv VAL field according to:
								VAL = VAL*ASLO + AOFF

## Specific records for:

### bi record
* ZSV; OSV; COSV - Zero Severity, One Severity; Change of State Severity.
									The possible values for these fields are NO ALARM, MINOR, and MAJOR.

#### ao record
* DOL - Desired output Link: The value where that the ao value will take if in closed_loop mode

### asub record
more [info](https://wiki-ext.aps.anl.gov/epics/index.php/RRM_3-14_Array_Subroutine)
* SNAM - The name of the routine called
* VAL -  must be zero to activate output links
* EFLG - 	Tells the record when to post change events on the output fields VALA,...,VALU. [NEVER,ALWAYS, ON CHANGE]
* INAM - This is the name of the initialisation routine to be called once, at iocInit.
* INPA,..,INPU - The input links from where the values of A,...,U are fetched during record processing.
* FTA,..,FTU - Field types of the input values. These can be any of the following: "STRING", "CHAR", "UCHAR", "SHORT", "USHORT", "LONG", "ULONG", "FLOAT", "DOUBLE, "ENUM".
* NOA,..,NOU - The number of elements of storage allocated for each input field. Default is 1 (scalar value). An array is specified by setting this field to greater than 1.
* OUTA,..,OUTU - The output links on which the scalars or arrays located at VALA,...,VALU are placed during record processing.
* VALA,.., VALU	 - The output fields which hold the scalar values or arrays pushed out across the output links OUTA,...,OUTU.
* FTVA,..,FTVU - Field types of the output values.
* OVLA,..,OVLU - The previous values of the outputs.
