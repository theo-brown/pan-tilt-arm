pan-tilt-arm
============

Controlling a pan and tilt servo-powered arm from the raspberry pi.


So you have been given a Raspberry Pi by your Dad, and you don't have the foggiest idea of what to do with it.
This was the situation I found myself in, and so I decided to write up one of my first projects, so that everyone can get
going doing something with this wonderful bit of kit. 

The idea of this project was to make a simple thing that was cool, and a starter on the road to robotics.
It was also to get people into learning C, which is quite a daunting task to start off with. I also wanted to learn 
to use ncurses, a C module I haven't really used before.
However, as this is for beginners, I may end up uploading a different version of the code in python, which is
a lot easier to use. I will also at some point make a wiki (hopefully) detailing how to do it, as currently this is 
just download, compile and play.

This program uses pigpio- download it here
abyz.co.uk/rpi/pigpio/pigpio.zip

You'll need to compile arm-control.c with the following flags
-lpigpio -lpthread -lrt -lncurses
to link it with pigpio and curses.


