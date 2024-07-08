This project has taught me many things and I wanted to write about the experience of completing it here. The real and helpful ReadMe is in the files :)

I started this project not knowing anything about Python, C++ or SBC, heck, I didn't even know how to use the terminal properly beyond using it for things like node.js.
After completing this project I've experienced both the pains and joys of programming all over again.
I began with the simple steps, connecting pins, with the RFID tag reader I actually wanted sold out, I got the RDM6300 instead and connected it to my Arduino Uno
I then followed some tutorials on how to read the RFID tags I had from it and pasting that information in the Serial Monitor
I then thought, "why not display it on a screen?" oh how naive I was... this sent me down a 2 day streak of troubleshooting why my display just would not work with Adafruit libraries
Finally, with some help, I came accross the U8g2.h library made to run monochrome OLED's, this finally worked and so I went about learning how to work with such a simple display 
This is where I finally ran into my biggest "woah" moment. All my life I've been writing code on computers that couldn't care less if you used the most efficeint methods or not, or if you 
used 3Mb of memory or 4Mb... but the Arduino? I had 2048 bytes to play with, and the moment you went over 93% usage, the display would glitch out or stop working at all (ask me how I know)
I had to actively optimize my code to do less work, with less variables, with less lines and ultimately run faster for the first time in my life.
Reducing redundency, using local variables instead of allocating space for global ones, forcing constant outputs to be stored as program data instead of being allocated to memory, using 
smaller data types where I could, not because it was "the nice thing to do" but because I *HAD* to.
Your everyday 500 line DB manager for about 200 records wouldnt blink if you used Int instead of Bytes, but here it mattered.

I then learned about sending serial data over ports, addresses, waiting, listening, parsing and whatnot. I would send this tag's info I read to my computer and have a Python script listen for it, handle 
it, and then make an API call with that information.
I've only ever worked with API's with node.js and was overjoyed to have a library which handled these calls effortlessly.
I would correlate the Tag's ID with a song's name and artist I assigned it to, I would send that as a search request to Spotify's API, get that data, format what I wanted from it, display it neatly and then
send the user to the song's link which would then start playing the song.

Putting it in words makes it sound simple now but I know I struggled at almost every step at least a little and I'm happy I learned something from this.
