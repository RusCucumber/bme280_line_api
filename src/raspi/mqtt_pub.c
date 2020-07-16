#include "mods_p.h"
#include <mosquitto.h>

int connect_desire = 1;

void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    mosquitto_publish(mosq, NULL, topic, strlen(message), message, 0, 0);
    printf("Publish \"%s\" about \"%s\" from %s to %s:%d\n", message, topic, id, host, port);
}

void on_disconnect(struct mosquitto *mosq, void *obj, int result)
{
    printf("Publisher was disconnected from broker.\n");
}

static void on_publish(struct mosquitto *mosq, void *userdata, int mid)
{
    connect_desire = 1;
    mosquitto_disconnect(mosq);
}

void mqtt_pub(void)
{
    int result;

    struct mosquitto *mosq = NULL;

    mosquitto_lib_init();

    mosq = mosquitto_new(id, 1, NULL);
    if (!mosq) {
        perror("Failed to create mosquitto\n");
        mosquitto_lib_cleanup();
        exit(1);
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    mosquitto_publish_callback_set(mosq, on_publish);
    
    result = mosquitto_tls_set(mosq, cafile, NULL, NULL, NULL, NULL);
    if (result != MOSQ_ERR_SUCCESS) {
        perror("Failed to tls.\n");
        mosquitto_lib_cleanup();
        exit(1);
    }

    result = mosquitto_username_pw_set(mosq, username, pw);
    if (result != MOSQ_ERR_SUCCESS) {
        perror("Failed to authantification.\n");
        mosquitto_lib_cleanup();
        exit(1);
    }

    result = mosquitto_connect_bind(mosq, host, port, 60, NULL);
    if (result != MOSQ_ERR_SUCCESS) {
        perror("Failed to connect.\n");
        mosquitto_lib_cleanup();
        exit(1);
    }

    printf("Server connected!\n");

    do {
        result = mosquitto_loop_forever(mosq, -1, 1); // -1 で timeoutを1000msにセット
    } while ((result == MOSQ_ERR_SUCCESS) && (connect_desire != 1));

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

/*
void mqtt_pub(void)
{
    printf("Publish \"%s\" about \"%s\" from %s to %s:%d\n", message, topic, id, host, port);
}
*/
