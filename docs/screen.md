# Screen
Screen is a linux service that allows a user to have multiple shells simultaniously and be able to detach them and they will still run in daemon mode.
This is used at start up to call EPICS inside a screen so that it is running in the backgorund.

## Linux Commands
* start `screen `
* Recover session `screen -r`
* List all sessions `screen -li`

## Screen ShortKeys
* Detach current session: `ctrl+A` then `d` then `y`
* Kill current session `ctrl+A`then `k`then `y`


## Other commands
* ? screen /dev/ttyUSB0 115200  
