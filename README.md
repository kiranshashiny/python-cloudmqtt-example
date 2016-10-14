This sample app shows how to connect with [mosquitto](https://pypi.python.org/pypi/mosquitto/) to [CloudMQTT](http://www.cloudmqtt.com) and both publish and subscribe messages. 

    $ pip install -r requirements.txt

I got the definitions from this page.
https://pypi.python.org/pypi/paho-mqtt/0.9

This was tested against cloudmqtt.com 

https://api.cloudmqtt.com/sso/cloudmqtt/websocket

1. Create an account on cloudmqtt.com ( in my case it was Kute Cat )

2. Start Arduino IDE and upload the sketch - to Arduino Uno board.
3. Start the app.py so publish data.
4. Wait for it to appear on the Cloudmqtt websockets console.
5. See that it appears on the Arduino IDE Serial monitor as well.

<img width="711"  src="https://cloud.githubusercontent.com/assets/14288989/19376311/64c745ce-91fa-11e6-8450-c0d44bcba9d9.png">

<img width="550"  src="https://cloud.githubusercontent.com/assets/14288989/19376319/7a26fb12-91fa-11e6-909d-06e26f1188b3.png">

<img width="776"  src="https://cloud.githubusercontent.com/assets/14288989/19376317/7a21d574-91fa-11e6-839d-77978c3a38ac.png">

<img width="1440" src="https://cloud.githubusercontent.com/assets/14288989/19376320/7a298a9e-91fa-11e6-9c8c-a46013715d02.png">

<img width="780"  src="https://cloud.githubusercontent.com/assets/14288989/19376318/7a244c28-91fa-11e6-88fc-bc21f04625e0.png">

