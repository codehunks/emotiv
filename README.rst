EPOC EMOTIV Programming
=======================
Intro
-----
 A revolutionary personal interface for brain computer interacton.The Emotiv EPOC headset uses a total of 16 sensors, 
 14 for EEG data, 2 for gyro motions to tune into electrical signals produced by the brain to detect user thoughts,
 feelings, expressions and their mental state.

Requirements
------------

#. OS: Windows 7/8
#. Programming Tool: Visual Basic C++ (tested with express 2010)
#. EMOTIV SDK: Tested with education version.

Installation
------------
Those who spent bucks for the device, get ready with your Emotiv-SDK. SDK installation is fairly easier,
you just have to follow the steps as mentioned in the installation guide.


Getting Started
---------------

First, wear the headset on your head, try to connect all the 16 sensors with the sdk control panel so that you get a 
good connection.

Second, make sure you set up your applications to be 32 bit x86 in VB, otherwise they won't link to edk.dll
which is 32 bit (unless you have SDK v2.0.0.20 or later which also has 64 bit versions). 
Make sure edk.dll and edk_utils.dll are in your project directory or search path. Then you should be 
able to build any of the examples in the SDK installation folder. 
The SDK manual has fairly comprehensive instructions on how to program for EPOC.

Programming with glut(a library of utilities for OpenGL programs)
-----------------------------------------------------------------
`Configuring Visual C++ and GLUT <https://sites.google.com/site/marcoschaerfcomputergraphics/lab/installing-and-configuring-visual-c-and-glut/>`_

Building & Running
------------------

#. F7 for building (succeed without errors)
#. F5 for running your app.

Patches are welcomed
--------------------

.. code-block:: bash

    $ git clone https://github.com/codehunks/emotiv.git "emotiv"
    $ cd emotiv
