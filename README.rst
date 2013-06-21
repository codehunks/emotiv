EPOC EMOTIV Programming
=======================
Intro
-----
A revolutionary personal interface for human computer interacton.The Emotiv EPOC uses sensors to tune
into electrical signals produced by the brain to detect user thoughts, feelings, and expressions.

Requirements
------------

#. Windows ( i know some would unlike it, no options )
#. Visual Basic C++ (tested with express 2010)

Installation
------------
Those who spent bucks for the device, get ready with your Emotiv-SDK.

Getting Started
---------------

First, make sure you set up your applications to be 32 bit x86, otherwise they won't link to edk.dll
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

