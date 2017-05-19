# Issues

## Hydroponic Issues
+ (solved) The water solution was getting a "snot". This was found to come from the original water tubes  from the water pumps (chinese ones) that would problably reacted with the nutrient solution. They were substituted and the problem was solved

## Raspberry pi
+ (solved) The pi was shutding down randomly, entering a state that would only recover if the plug in was removed and reconnected. No acess via ssh(red light turn on, no activity on the green ligh, ethernet lights blinking). The first tought was that the problem was due to the powersupply. Indded in the GUI of the Pi a lightingbolt symbol was appering meaning a low voltage of the powersupply. Another one with 2A was tested, but it did not solved the problem. Another Pi was changed, again with no solution. To Solved this a watchdog was installed. (So far it did not seemed that the pi would restart because of the watchdog, but after this install it stopped shuting down, so problem solved) see [/hgco/docs/watchdog.md]. The problem origin was not found but changing the powersupply to a 3A and after installing the watchdog no more issues occured.

## GreenHouse
+ The NFT tubes were hard to handle inside the greenhouse and outside (not flexible). Also the connection from the NFT system to the exit water tube was not well isolated, and leaks thend to oocuur.

### camera
+ The camera did not cover the entire green are.
+ After 15 days the lettuce plants would easily overlap with the NFT system

### Humidity
+ The greenhouse showed a very low level of humidity ~40% where it should be around 60-70%
