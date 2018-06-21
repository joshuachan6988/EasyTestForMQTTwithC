// C_MQTT.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mosquitto.h"

void on_publish(struct mosquitto *mosq, void *userdata, int mid)
{
    mosquitto_disconnect(mosq);
}


int _tmain(int argc, _TCHAR* argv[])
{
	struct mosquitto *mosq;
	mosquitto_lib_init();
    mosq = mosquitto_new(NULL, true, NULL);
    mosquitto_publish_callback_set(mosq, on_publish);

    mosquitto_connect(mosq, "localhost", 1883, 60);
    mosquitto_publish(mosq, NULL, "hello/world", 11, "hello world", 0, false);
    mosquitto_loop_forever(mosq, 2, 1);  // this calls mosquitto_loop() in a loop, it will exit once the client disconnects cleanly

    return 0;
}

