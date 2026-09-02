# M1W

* Keyboard Maintainer: [sdk66](https://github.com/sdk66)
* Hardware Supported: M1W
* Hardware Availability: [XXX](http://www.XXX.com)

Make example for this keyboard (after setting up your build environment):

    make akko/m1w:default
        
Flashing example for this keyboard:

    make akko/m1w:default:flash

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the bottom side of the PCB while connecting the USB cable
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+R_Shift+Esc will reset the board to bootloader mode if you have flashed the default QMK keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

