/**********************************************************************
   [  SimpleSerialUnity3D  ]
 *                                                                    *
    - A simple Arduino interface for Unity3D, using string commands.
    - It supports read and write for analog and digital pins for now.
 *                                                                    *
   Author: Sjoer van der Ploeg
 *********************************************************************/
 
 A command is sent as a string over serial, and the handling is based
 on a simple state machine.
 
 For example:
 
 Sending 0013, enables pin 13 as output.
 Sending 2113, will make pin 13 digital high.
 
 The Arduino sketch is somewhat commented, for you to figure out!
 
 This does not only work with Unity3D, but with everything that
 supports serial commumnication.
 
 The code runs "threaded" on  the Arduino, you can make it do whatever
 you want it to do! The main serial thread is called every millisecond.
