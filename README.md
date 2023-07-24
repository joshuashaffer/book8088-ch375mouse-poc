Book8088 USB Mouse Proof of Concept
===================================

This is a proof of concept for putting the CH375 USB Host Controller into HOST mode and using it to read a USB mouse on
the Book 8088 computer (available on aliexpress.com).

This reads the mouse data and updates a cursor drawn in 80x25 text mode.

This is not a complete driver, it is just a proof of concept. It makes a lot of assumptions about the mouse and the
environment. It is not robust and it is not complete. If you have a fancy mouse with more than 3 buttons, it will not
work correctly. 

This is based on code for doing similar things on the Arduino. https://github.com/Makeblock-official/Makeblock-Libraries/

Public Domain.

## Building

Setup openwatcom and run the following:

```shell
$ wmake
```

## Running


Copy the resulting `mouse.com` file to the compact flash card, plug a basic usb mouse in, and run it on the Book 8088.

<video src="demo.webm" width="640" height="480" controls preload></video>