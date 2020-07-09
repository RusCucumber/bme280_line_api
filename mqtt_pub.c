#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <unistd.h> // sleep()
#include <signal.h> // signal()
#include <mosquitto.h>

struct mosquitto *mosq;
void sig_catch(int sig)
{
    printf("\nfin\n");
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    exit(0);
}
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Argument must be one.\n");
        return -1;
    }

    const char *username = "token:token_zh2mqivS6Hjs0h0F";
    const char *pw = NULL;

    const char *cafile = "/Users/ryuki/raspberrypi/bme280_line_api/mqtt.beebotte.com.pem";

    const char *ip = "mqtt.beebotte.com"; // ipアドレス
    const int port = 8883; // port, デフォルトは1883
    const char *id = "mqtt/pub"; // id名
    const char *topic = "test/sub1"; // トピック
    const char *message = argv[1]; // メッセージ

    printf("Preoareing mosquitto...\n");
    // mosquitto_apiの初期化
    mosquitto_lib_init(); 
    // mosquitto構造体の作成
    mosq = mosquitto_new(id, 1, NULL);
    if (!mosq) {
        perror("Failed to create mosquitto\n");
        mosquitto_lib_cleanup();
        return -1;
    }
    
    int res;
    res = mosquitto_tls_set(mosq, cafile, NULL, NULL, NULL, NULL);
    if (res != MOSQ_ERR_SUCCESS) {
        perror("Failed to tls.\n");
        mosquitto_lib_cleanup();
        return -1;
    }
    mosquitto_tls_insecure_set(mosq, 1);

    res = mosquitto_username_pw_set(mosq, username, pw);
    if (res != MOSQ_ERR_SUCCESS) {
        perror("Failed to authantification.\n");
        mosquitto_lib_cleanup();
        return -1;
    }

    res = mosquitto_connect_bind(mosq, ip, port, 60, NULL);
    if (res != MOSQ_ERR_SUCCESS) {
        perror("Failed to connect.\n");
        mosquitto_lib_cleanup();
        return -1;
    }

    printf("Server connected!\n");

    signal(SIGINT, sig_catch);

    while(1) {
        mosquitto_publish(mosq, NULL, topic, strlen(message), message, 0, 0);
        printf("Publish \"%s\" about \"%s\" from %s to %s:%d\n", message, topic, id, ip, port);
        sleep(1);
    }
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

/*
mosquitto_sub -v -h mqtt.beebotteom -p 8883 -t "test/sub1" -u "token:token_zh2mqivS6Hjs0h0F" --cafile mqtt.beebotte.com.pem

*/