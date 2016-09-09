#!/usr/bin/python
  
# Copyright (c) 2014 Roger Light <roger@atchoo.org>
#
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Distribution License v1.0
# which accompanies this distribution. 
#
# The Eclipse Distribution License is available at 
#   http://www.eclipse.org/org/documents/edl-v10.php.
#
# Contributors:
#    Roger Light - initial implementation
  
# This shows an example of using the publish.single helper function.
  
import sys
import paho.mqtt.publish as publish
### Single payload.
#without payload.  
publish.single("/fromlaptop", payload=None, qos=0, retain=False, hostname="m12.cloudmqtt.com",
    port=19757, client_id="", keepalive=60, will=None, auth={'username':"oxefqvkn", 'password':"aKpQPSFiTpXp"}, tls=None)
#with payload
publish.single("/fromlaptop", payload="shashilaptop", qos=0, retain=False, hostname="m12.cloudmqtt.com",
    port=19757, client_id="", keepalive=60, will=None, auth={'username':"oxefqvkn", 'password':"aKpQPSFiTpXp"}, tls=None)


# With multiple topics in a publish

# first set the list with the different topics and 

msgs = [{'topic':"/fromLTMultiple", 'payload':"multiple 1"},
    ("/fromLTDifferenttopic", "multiple 2", 0, False)]

publish.multiple(msgs, hostname="m12.cloudmqtt.com", port=19757, client_id="", keepalive=60,
    will=None, auth={'username':"oxefqvkn", 'password':"aKpQPSFiTpXp"}, tls=None)
