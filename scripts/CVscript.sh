#!/bin/sh
#This script takes a picture with raspstill and call the
#Image Processing PlantCV python program to compute plants weight

echo "running CVscript"


DATE=$(date +"%Y_%m_%d-%H_%M")
EXPNAME='ExperienceName' #Please do not use whitespaces

#Change to to camera folder
cd /home/pi/camera


#Take Snapshot
raspistill -q 20 -w 1920 -h 1080 -a "$EXPNAME\n$DATE" -o teste.jpg -l latest.jpg
#raspistill -q 20 -w 1920 -h 1080 -a "$EXPNAME\n$DATE" -o /home/pi/camera/$EXPNAME-$DATE.jpg -l latest.jpg
echo "Photo Taken"
#Used raspistill flags
# -q quality [100-0]
#-o Specifies the output filename. If not specified, no file is saved
# -l Makes a file system link under  this name to the latest frame.
#-a ds some text and/or metadata to the picture.
# -w  width
# -h height



#Call PlantCV pipeline

/home/pi/plantcv/mypipeline/mypipeline.py -i /home/pi/camera/teste.jpg -o output -D 'print'
echo "PlantCV pipeline runned"
