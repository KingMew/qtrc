qtrc
====

qtrc is a reality check reminder program designed using the Qt framework. The purpose of this application is to constantly remind the user to reality check in order to hopefully increase the frequency of lucid dreams. By the way, you should try reality checking!

Compiling
---------

In order to compile qtrc, you need Qt 5.2. You'll need to install the latest versions of the Qt and Qt development packages. On Linux, you can simply run 
    
    $ qmake
    $ make

And all will be done. On Windows, you'll have to compile in Qt Creator, which should be even easier.

Using
-----

To use qtrc, launch it, fill in the info, and click "Start". It's pretty self explanatory. One thing that might not be so easy to figure out is how to reconfigure or exit an already running instance of qtrc. Simply launch the application again to reconfigure or exit the application. If you're a savvy console user, then you can run `qtrc --exit` to exit out of the application without wasting the second it takes to click the "Exit" button.

Pics or it didn't happen?
-------------------------

![Reality Check](http://www.mew151.net/creative/qtrc.png "Reality check!")

Here is a picture of qtrc in action! The appearance of the notifications depends on whether you have a compositing window manager or not. If your window manager does compositing, it should show up transparent. Otherwise, you'll get a black background like this or something.

