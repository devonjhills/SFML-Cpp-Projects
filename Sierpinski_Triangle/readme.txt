/**********************************************************************
 *  ps1
 *  Recursive Graphics
 **********************************************************************/

Your name:
Devon Hills

Operating system you're using (Linux, OS X, or Windows):
Linux

Text editor or IDE you're using:
Atom


/**********************************************************************
 *  A discussion of what I did.
 **********************************************************************/

For this assignment I first implemented the Sierpinski triangle pattern recursively using the SFML graphics. I found a formula for the pattern which revolved around continuously cutting the length of each sub-triangle in half, and then calculating the height of each sub triangle by multiplying the length by sqrt(3)/2. After that it was just a matter of positioning the three sub triangles drawn during each iteration correctly in the window.

For my original pattern I created a large circle with a radius equal to half the inputted screen width. There are four recursive statements which draw 2 sub circles along the x axis and 2 along the y axis, each with half the radius of the preceding circle.


/**********************************************************************
 *  Why inheriting sf::Drawable allows window.draw() to work?
    What was interesting/hard/or easy?
 **********************************************************************/

Inheriting from sf::Drawable gives access to the virtual draw function, which we can implement ourselves in order to draw custom shapes and objects. Then in main we can use window.draw(object) rather than object.draw(window).

Getting the geometry to function properly in the SFML window was the most difficult part of the assignment. I got the recursion to work, but the pattern was all messy until I managed to figure out the proper coordinates.


/**********************************************************************
 *  Memory usage.
 **********************************************************************/

Sierpinski:
depth 3:
in use at exit: 52,099 bytes in 477 blocks
total heap usage: 83,311 allocs, 82,834 frees, 18,144,809 bytes allocated

depth 6:
in use at exit: 52,099 bytes in 477 blocks
total heap usage: 176,151 allocs, 175,674 frees, 31,463,257 bytes allocated

Original:
depth 3:
in use at exit: 52,099 bytes in 477 blocks
total heap usage: 65,894 allocs, 65,417 frees, 388,827,609 bytes allocated

depth 6:
in use at exit: 52,099 bytes in 477 blocks
total heap usage: 116,701 allocs, 116,224 frees, 1,005,906,933 bytes allocated



Time invested: A weekend
