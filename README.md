# WikiBeep

WikiBeep was PhD research side-project that eventually led on to much more advanced analysis of WiFi privacy leaks. It is a demonstration of how some information can be leaked from WiFi networks, despite their encryption is working exactly as intended.

Specifically, it makes an annoying beep when it detects someone nearby using WiFi to access Wikipedia. This serves absolutely no practical purpose, but is a proof-of-concept tool demonstrating that private activities can be inferred despite encryption. WiFi users would normally assume that their actvities were confidential if encryption is working 100% as intended.


## How it works

Although data cannot be read directly from encrypted WiFi traffic, certain information can still be measured. WikiBeep looks for certain size frames/packets corresponding to Wikipedia's many language subdomains.

For best results:
- Aim for the wikipedia homepage proper (www.wikipedia.org, including the www.)
- Use a browser with DNS prefetch turned on (modern Chrome, Firefox, IE all do this by default including mobile versions)
- Ensure the DNS entries aren't already cached (you can clear manually, or some OS's have a very short timeout. Android is only 10s)


You will get partial detection for other wikipedia pages (i.e. actual articles rather than the homepage). You will also get partial detection for quick refreshes (i.e. DNS cache has not yet timed out so few addition DNS requests are sent).


## Dependencies:

- Ubuntu Linux OS, or your ability to adapt it to another (details below).
- The airmon-ng program must be installed. Part of the aircrack-ng tools package.
- The tshark program must be installed. Part of the Wireshark suite.
- Demo scripts assume an Ubuntu or Ubuntu-derivative OS. See below. 

## Compilation:

```
g++ ./*.cc -lpthread -o ./wikibeep
```

## Demonstration:

The project comes with two scripts that simplify starting the monitoring process via the Linux shell. Unless you are running default Ubuntu and your WiFi network uses Channel 1, these will require modification.

In other cases you will need to modify both these scripts and work out how to disable/re-enable your equivalent of network-manager so that it does not try to connect to your wireless network as normal and interfere with packet collection. If you're stuck Googling for posts by airmon-ng users will probably provide a solution for your chosen platform. 

### Start the monitoring process.

Modify this file to alter the name of the interface to monitor on (default: wlan0) and the WiFi channel to monitor (default: 1). If you don't know what channel you want to monitor on there various WiFi scanner apps available for Android and iOS or you can check your Access Point's setup if that's something accessible to you. Alternatively, you can guess. Most APs run on channel 1, 6 or 11.

```
./testRun
```

### Monitoring

Once you are monitoring a channel, use a device connected to that channel to access Wikipedia. The program records frames from the last 5 seconds that indicate Wikipedia activity.

In left-right column order the monitor program shows: the total number of frames monitored, time of latest update, horizontal graph in green showing incoming frames that indicate Wikipedia activity, horizontal graph in blue showing outgoing frames that indicate Wikipedia activity in the last 5 seconds. If both of these graphs exceed 10 indicating frames then a beep alert is emitted.

![Screenshot](https://github.com/fauxnetic/WikiBeep/blob/master/screenshot.png "WikiBeep Screenshot")

If your platform does not have a system speaker included (like Raspberry Pi's) or enabled, then you will need to adapt the UIUpdater::alert() method to your needs.


### Cleanup

After you've finished monitoring, hit CTRL+C. This will quit the monitoring process. To cleanup and restore WiFi connectivity:

```
./testCleanup
```

  
## Notes

This is only a proof-of-concept. Although it has been demonstrated on a variety of networks, your mileage may vary. Furthermore, the metrics used to detect Wikipedia may change if Wikipedia makes changes to its infrastructure.


## Licensing

Copyright (C) 2013 John Atkinson <john@fauxnetic.co.uk>

WikiBeep is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

WikiBeep is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>.


