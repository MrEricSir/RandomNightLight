# RandomNightLight

> There are four lights!

 -- Captain Jean-Luc Picard

Have some digitally controllable lights (for example LEDs) that you want to fade in or out in a random sequence depending on the light level? Do you also have an extra Arduino lying around and a photoresistor? This is the program for you!

The Arduino Uno can light from zero to six lights using this program, though in practice it's overkill if you have fewer than two light.

In general, you should just be able to modify the user settings at the top of RandomNightLight.ino.  I'll leave wiring the lights up to you.  In my case I'm using decorative LEDs that already have resistors wired in.  Your situation may be different.

If you've never wired a photoresistor before, here's how:

![Photoresistor circuit diagram](https://raw.githubusercontent.com/MrEricSir/RandomNightLight/master/circuit.png)

Having trouble?  Try setting the debugMode constant to true and listening on the serial port.
