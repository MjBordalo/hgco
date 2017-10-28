# Virtual network computing (VNC)
is a graphical desktop sharing system that allows you to control one computer remotely from another. A VNC server transfers keyboard and mouse events, and displays the remote host’s screen via a network connection, which allows you to operate a full desktop environment on your Linode.

## Realvnc
### Enabling on Pi - Server
https://www.raspberrypi.org/documentation/remote-access/vnc/
### Install client:
on linux download the file from the site: https://www.realvnc.com/en/connect/download/viewer/linux/

in case of resolutions problems edit ```/boot/config.txt```
and enabled\uncomment these configs:
```
framebuffer_width=1280
framebuffer_height=720
```

## TightVNC
TightVNC is a free remote control software package. With TightVNC, you can see the desktop of a remote machine and control it with your local mouse and keyboard, just like you would do it sitting in the front of that computer.
I used this because in windows realvnc was not working.

### Linux Commands
* start: `tightvncserver`
* change password: `vncpasswd`

### Acess it

When on a remote computer connect to the desired computer default port 5901. E.g `hgco.ddns.net:5901`
