#!/bin/sh
#This script takes a picture with raspstill and call the
#Image Processing PlantCV python program to compute plants weight

echo "running CVscript"


DATE=$(date +"%Y_%m_%d-%H_%M")
EXPNAME='Exp02' #Please do not use whitespaces

#Change to to camera folder
cd /home/pi/camera


#Take Snapshot
#raspistill -q 20 -w 1920 -h 1080 -a "$EXPNAME\n$DATE" -o teste.jpg -l latest.jpg
raspistill -q 20 -vf -hf -w 1920 -h 1080 -o $EXPNAME-$DATE.jpg -l latest.jpg
echo "Photo Taken"
#Used raspistill flags
# -q quality [100-0]
#-o Specifies the output filename. If not specified, no file is saved
# -l Makes a file system link under  this name to the latest frame.
#-a ds some text and/or metadata to the picture.
# -w  width
# -h height
# -vf -hf : vertical flip horizontal flip


##Call PlantCV pipeline
#TODO quando tiver a camera mudar para:
/home/pi/hgco/scripts/compute_LAI.py -i /home/pi/camera/$EXPNAME-$DATE.jpg -o output -D 'print' -r $EXPNAME-$DATE-results.txt
#/home/pi/hgco/scripts/compute_LAI.py -i /home/pi/camera/ExperienceName-2017_04_18-18_25.jpg -o output -D 'print' -r $EXPNAME-$DATE-results.txt
echo "PlantCV pipeline runned"
