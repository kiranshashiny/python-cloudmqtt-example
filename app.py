import paho.mqtt.client as mqtt , os, urlparse
import time

# Define event callbacks
    
def on_connect(mosq, obj, rc):
    print "In the on_connect";
    print("rc: " + str(rc))

def on_message(mosq, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

def on_publish(mosq, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(mosq, obj, level, string):
    print(string)


client = mqtt.Client()
# Assign event callbacks
client.on_message = on_message
client.on_connect = on_connect
client.on_publish = on_publish
client.on_subscribe = on_subscribe

# Uncomment to enable debug messages
client.on_log = on_log

print "hello world"

# Connect
client.username_pw_set("ghcqvpeu", "geZgGJ8tsPVk")
print "before connecting"

client.connect('m12.cloudmqtt.com', 12071, 60)
print "after connecting"
#while True :
#        # Publish a message
#        client.publish("/toclientloud", "from python code")
#        time.sleep(5);


# Continue the network loop, exit when an error occurs
#rc = 0
#while rc == 0:
#    rc = client.loop()
#print("rc: " + str(rc))

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
