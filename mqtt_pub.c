#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <unistd.h> // sleep()
#include <signal.h> // signal()
#include <mosquitto.h>

// beebotte 用の認証情報
const char *username = "token:token_zh2mqivS6Hjs0h0F";
const char *pw = NULL;

// tls 接続用の証明書
const char *cafile = "/Users/ryuki/raspberrypi/bme280_line_api/mqtt.beebotte.com.pem";

// 接続用情報
const char *host = "mqtt.beebotte.com"; // host
const int port = 8883; // port番号 tlsを利用するので 8883
const char *id = "mqtt/pub"; // id名（任意）
const char *topic = "test/sub1"; // トピック
char *message = "default msg: test"; // メッセージ

// brokerとの接続情報を保持 0: True, 1: False
int connect_desire = 1;

// Brokerとの接続成功時に実行されるcallback関数
void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    mosquitto_publish(mosq, NULL, topic, strlen(message), message, 0, 0);
    printf("Publish \"%s\" about \"%s\" from %s to %s:%d\n", message, topic, id, host, port);
}

// Brokerとの接続を切断したときに実行されるcallback関数
void on_disconnect(struct mosquitto *mosq, void *obj, int result)
{
    printf("Publisher was disconnected from broker.\n");
}

// BrokerにMQTTメッセージを送信後に実行されるcallback関数
static void on_publish(struct mosquitto *mosq, void *userdata, int mid)
{
    connect_desire = 1;
    mosquitto_disconnect(mosq);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Message is needed.\n");
        return EXIT_FAILURE;
    }

    printf("Prepareing mosquitto...\n");

    // コマンドライン引数からメッセージをセット
    message = &(argv[1][0]);

    // mosquitto APIの関数の結果を保持
    int result;

    // mosquitto を利用するためのインスタンス（構造体）
    struct mosquitto *mosq = NULL; 

    // mosquitto_apiの初期化
    mosquitto_lib_init(); 

    // mosquitto構造体の作成
    mosq = mosquitto_new(id, 1, NULL);
    if (!mosq) {
        perror("Failed to create mosquitto\n");
        mosquitto_lib_cleanup();
        return EXIT_FAILURE;
    }

    // callback関数のセット
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    mosquitto_publish_callback_set(mosq, on_publish);
    
    // tls証明書の読み込み
    result = mosquitto_tls_set(mosq, cafile, NULL, NULL, NULL, NULL);
    if (result != MOSQ_ERR_SUCCESS) {
        perror("Failed to tls.\n");
        mosquitto_lib_cleanup();
        return EXIT_FAILURE;
    }
    mosquitto_tls_insecure_set(mosq, 1);

    // 認証情報の読み込み
    result = mosquitto_username_pw_set(mosq, username, pw);
    if (result != MOSQ_ERR_SUCCESS) {
        perror("Failed to authantification.\n");
        mosquitto_lib_cleanup();
        return EXIT_FAILURE;
    }

    // Brokerとの接続
    result = mosquitto_connect_bind(mosq, host, port, 60, NULL);
    if (result != MOSQ_ERR_SUCCESS) {
        perror("Failed to connect.\n");
        mosquitto_lib_cleanup();
        return -1;
    }

    printf("Server connected!\n");

    // メッセージを送るまでループをする
    do {
        result = mosquitto_loop_forever(mosq, -1, 1); // -1 で timeoutを1000msにセット
    } while ((result == MOSQ_ERR_SUCCESS) && (connect_desire != 1));

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return EXIT_SUCCESS;
}

/*
mosquitto_sub -v -h mqtt.beebotteom -p 8883 -t "test/sub1" -u "token:token_zh2mqivS6Hjs0h0F" --cafile mqtt.beebotte.com.pem
*/