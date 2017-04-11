#!/bin/sh

#This script is called at pi user stratup configured with crontab -e  command 1

echo "running mystartup"

#Star epics in a detached screen
cd /home/pi/hgco/EPICS_apps/GreenHouse_top/iocBoot/iocGreenHouse
screen -dmS EPICS ./st.cmd

#start tightvncserver
tightvncserver
