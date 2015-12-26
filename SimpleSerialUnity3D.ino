/**********************************************************************
   [  SimpleSerialUnity3D  ]
 *                                                                    *
    - A simple Arduino interface for Unity3D, using string commands.
    - It supports read and write for analog and digital pins for now.
    -
    - TODO: implement more functions and write documentation!
 *                                                                    *
   Author: Sjoer van der Ploeg
 *********************************************************************/

#include <Thread.h>
#include <ThreadController.h>
#include <TimeAlarms.h>

ThreadController threadController = ThreadController();
ThreadController timeController = ThreadController();
ThreadController serialController = ThreadController();

Thread timeAlarmThread = Thread();
Thread serialThread = Thread();

void setup()
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  timeAlarmThread.onRun(timeAlarmThreadCallback);
  timeAlarmThread.setInterval(1);
  timeAlarmThread.enabled = true;
  timeController.add(&timeAlarmThread);

  serialThread.onRun(serialThreadCallback);
  serialThread.setInterval(1);
  serialThread.enabled = true;
  serialController.add(&serialThread);

  threadController.add(&timeController);
  threadController.add(&serialController);

  Serial.flush();
  Serial.println("yoloswag");
}

void timeAlarmThreadCallback()
{
  Alarm.delay(0);
}

void serialThreadCallback()
{
  if (Serial.available() > 0)
  {
    String _data = Serial.readString();
    _data.trim();

    switch (_data.charAt(0))
    {
      case 48: setPinMode(_data); break;            // 0 x yy
      case 49: readDigitalPin(_data); break;        // 1 yy
      case 50: writeDigitalPin(_data); break;       // 2 x yy
      case 51: readAnalogPin(_data); break;         // 3 xx
      case 52: writeAnalogPin(_data); break;        // 4 xx yyy
      case 53: setAnalogReference(_data); break;    // 5 x
      case 54: Serial.println("6"); break;
      case 55: Serial.println("7"); break;
      case 56: setLED(_data); break;                // 8 x
      case 57: reportTimeConnected(); break;        // 9 x
    }
  }
}

void setPinMode(String _data)
{
  _data.remove(0, 1);

  switch (_data.charAt(0))
  {
      _data.remove(0, 1);

    case 48:  // 0 0 xx
      {
        pinMode(_data.toInt(), OUTPUT);
        break;
      }
    case 49:  // 0 1 xx
      {
        pinMode(_data.toInt(), INPUT);
        break;
      }
    case 50:  // 0 2 xx
      {
        pinMode(_data.toInt(), INPUT_PULLUP);
        break;
      }
  }
}

void readDigitalPin(String _data)
{
  _data.remove(0, 1);

  Serial.println(digitalRead(_data.toInt()));
}

void writeDigitalPin(String _data)
{
  _data.remove(0, 1);

  switch (_data.charAt(0))
  {
      _data.remove(0, 1);

    case 48:  // 1 0 xx
      {
        digitalWrite(_data.toInt(), LOW);
        break;
      }
    case 49:  // 1 1 xx
      {
        digitalWrite(_data.toInt(), HIGH);
        break;
      }
  }
}

void readAnalogPin(String _data)
{
  _data.remove(0, 1);

  Serial.println(analogRead(_data.toInt()));
}

void writeAnalogPin(String _data)
{
  _data.remove(0, 1);

  String _pin = _data;
  String _value = _data;

  _pin.remove(2, 3);
  _value.remove(0, 2);

  analogWrite(_pin.toInt(), _value.toInt());
}

void setAnalogReference(String _data)
{
  _data.remove(0, 1);

  switch (_data.charAt(0))
  {
      _data.remove(0, 1);

    case 48:  // 5 0
      {
        analogReference(DEFAULT);
        break;
      }
    case 49:  // 5 1
      {
        analogReference(EXTERNAL);
        break;
      }
  }
}

void setLED(String _data)
{
  _data.remove(0, 1);
  
  switch (_data.charAt(0))
  {
    case 48: digitalWrite(LED_BUILTIN, LOW); break;
    case 49: digitalWrite(LED_BUILTIN, HIGH); break;
  }
}

void reportTimeConnected()
{
  Serial.println(now());
}

void loop()
{
  threadController.run();
}
