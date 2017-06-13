# The-Martian-Decoder

In the 2015 film The Martian, the main character uses a circle with a card displaying hex characters to communicate with Earth. The rover camera points at each hex character (0-9, A-F) to display a message.

This program reads a list of camera angles (0-360 degrees) from the Ascii-Degrees.csv file and decodes them into their corresponding hex value based on the below list. It then converts paired hex values into ASCII characters, and displays the decoded message.

Hex | Degrees

0 = 0°-22°

1 = 23°-45°

2 = 46°-67°

3 = 68°-90°

4 = 91°-112°

5 = 113°-135°

6 = 136°-157°

7 = 158°-180°

8 = 181°-202°

9 = 203°-225°

A = 226°-247°

B = 248°-270°

C = 271°-292°

D = 293°-315°

E = 316°-337°

F = 338°-360°
