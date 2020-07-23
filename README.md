# 室内温度確認IoTシステム

## システムについて

Raspberry Piから取得した自室の気温、湿度、気圧をLINEから確認することができるIoTシステムを開発しました。<br>
現在は、LINE BOTに適当なメッセージを送ることで、最新のデータを１件見ることができます。

![LINE](https://user-images.githubusercontent.com/49883432/88264565-edb85580-cd06-11ea-80e8-59711fc2dd3d.jpeg)


---

## 動機

最近、家にウサギがやってきました。<br>
鳴くこともなく、うんちも臭くなく、とても飼いやすいのがウサギの特徴ですが、暑すぎたり、じめじめした環境があまり得意ではありません。<br>
そこで、ウサギの快適な環境を作るために、部屋の温度や湿度が良いので、このシステムを作成しました。

---

## 使用したツール・言語

**ツール**
- Raspberry Pi 3 Model B
- BME280（気温、湿度、気圧計測センサー）
- Beebotte
- heroku
- LINE MESSAGING API
- MongoDB Atlas

**言語**
- C
- Python

## 構成

![Structure](https://user-images.githubusercontent.com/49883432/88264505-d2e5e100-cd06-11ea-9b4d-7f8465eefc33.png)

## 今後の展望

- 任意の時刻のデータを取得
- データのグラフを取得
- データのcsvファイル等への出力
- 集めたデータに対して、機械学習をし、何かしらのモデルを構築する