#!/bin/sh

DATE=$(date +"%Y_%m_%d-%H_%M")

sudo sed -i "1i$DATE" /home/pi/hgco/data/reboot_log.txt
