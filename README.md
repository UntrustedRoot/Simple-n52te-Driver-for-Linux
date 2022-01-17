# NO LONGER MAINTAINED!
I got my hands on a Tartarus Chroma and decided it was finally time to eWaste the old n52te.

RIP

# Simple n52te Driver for Linux

Continuing in my Driver-for-Linux(tm) series of.... drivers for Linux.....

THE SIMPLE n53te DRIVER FOR LINUX

Different device, same problem. No driver for Windows or Linux

So I made one.

A real readme and commented code to follow.....

# Warning
This driver is not intended to replace the whole software suite required to program this device. For my needs, I need this device to return gamepad button hits instead of keyboard keys. If you need macros, profile programing, or anything else needed to use this device as advertised, this is not the driver for you.

If you just want to be able to use this pad as an alternative to WASD, while not actually using WASD, you've got the right driver! Great for replacing a Stream Deck.

As it is right now, every button is a 1-to-1 mapping of BTN_TRIGGERHAPPY_n, with the dpad and the high thumb button at the end (16-20.) Scroll wheel will be isolated in a future version, right now it will still register as a mouse scroll and middle click.

**Future versions MAY included these features**, but they are not required for this driver to be feature complete for my needs.
