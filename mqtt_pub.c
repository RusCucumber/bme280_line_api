#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <unistd.h> // sleep()
#include <signal.h> // signal()
#include <mosquitto.h>

void endCatch(int);
struct mosquitto *mosq;
int main(void)
{
    const char *ip = "192.168.0.13"; // ipアドレス
    const int port = 1883; // port, デフォルトは1883
    const char *id = "Test"; // id名
    const char *topic = "test/sub1"; // トピック
    const char *message = "Hello"; // メッセージ

    // 強制終了時、終了用の処理を呼び出す
    if (SIG_ERR == signal(SIGINT, endCatch)) {
        perror("Signal error.\n");
        return -1;
    }

    printf("Preoareing mosquitto...\n");
    // mosquitto_apiの初期化
    mosquitto_lib_init(); 
    // mosquitto構造体の作成
    mosq = mosquitto_new(id, 0, NULL);
    if (!mosq) {
        perror("Failed to create mosquitto\n");
        mosquitto_lib_cleanup();
        return -1;
    }
    
    mosquitto_connect(mosq, ip, port, 60);
    printf("Server connected!\n");
    while (1) {
        mosquitto_publish(mosq, NULL, topic, strlen(message), message, 0, 0);
        printf("Publish \"%s\" about \"%s\" from %s to %s:%d\n", message, topic, id, ip, port);
        sleep(1);
    }
    return 0;
}

void endCatch(int sig)
{
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    printf("\nEnd Program\n\n");
    exit(0);
}