import os
import traceback
import paho.mqtt.client as mqtt
from mods.mqtt.InsertMessage import InsertMessage

host = os.getenv("MQTT_HOST")
port = int(os.getenv("MQTT_PORT"))
ca_certs = os.getenv("MQTT_CAFILE")
username = os.getenv("MQTT_USER")
topic = os.getenv("MQTT_TOPIC")

DEBUG = False
if os.getenv("MQTT_DEBUG") == "TRUE":
    DEBUG = True

def on_connect(client, userdata, flags, rc):
    if DEBUG:
        print("Server connected.")
    client.subscribe(topic)

def on_disconnect(client, userdata, rc):
    if DEBUG:
        print("Subscriber was disconnected from broker.")

def on_message(client, userdata, message):
    msg = message.payload.decode(encoding = "utf-8")
    if DEBUG:
        print("Subscribed message {0} on topic {1}".format(msg, message.topic))
    client.disconnect()

    if DEBUG:
        print("Insert message.")
    try:
        InsertMessage(msg).insert()
        if DEBUG:
            print("Insert message succeed.")
    except:
        if DEBUG:
            print("Insert message failed.")
            print(traceback.format_exc())            

# インスタンスの作成
client = mqtt.Client()

# Callback関数の登録
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_message = on_message

# tls設定
client.tls_set(ca_certs)
# 認証情報設定
client.username_pw_set(username)
# brokerへの接続
client.connect(host, port)

client.loop_forever(timeout = 600.0, max_packets = 1, retry_first_connection = False)