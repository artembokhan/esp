/*******************************************************************************
Example 36(=32+4): 乾電池駆動の低消費電力動作のサンプル [Ambientへのデータ送信]
                                           Copyright (c) 2016-2017 Wataru KUNINO
*******************************************************************************/
#include <WiFi.h>                           // ESP32用WiFiライブラリ
#include <WiFiUdp.h>                        // UDP通信を行うライブラリ
#include "esp_deep_sleep.h"                 // ESP32用Deep Sleep ライブラリ
#define PIN_EN 2                            // GPIO 2(24番ピン)をセンサの電源に
#define PIN_AIN 34                          // GPIO 34 ADC1_CH6(6番ピン)をADCに

#include "Ambient.h"                        // Ambient用のライブラリの組み込み
#define SSID "1234ABCD"                     // 無線LANアクセスポイントのSSID
#define PASS "password"                     // パスワード
#define AmbientChannelId 100                // チャネル名(整数)
#define AmbientWriteKey "0123456789abcdef"  // ライトキー(16桁の16進数)
#define DATA_NUM 2                          // 起動時間のデータ番号
#define PIN_EN 13                           // IO 13(5番ピン)をセンサ用の電源に
#define SENDTO "192.168.0.255"              // 送信先のIPアドレス
#define PORT 1024                           // 送信のポート番号
#define SLEEP_P 9*60*1000000                // スリープ時間 9分(uint32_t)
#define DEVICE "adcnv_1,"                   // デバイス名(5文字+"_"+番号+",")

Ambient ambient;
WiFiClient client;
float t;

void setup(){
    t=-((float)millis())/1000;              // 現在のmillis値の負値を代入
    int waiting=0;                          // アクセスポイント接続待ち用
    pinMode(PIN_EN,OUTPUT);                 // センサ用の電源を出力に
    Serial.begin(115200);                   // 動作確認のためのシリアル出力開始
    Serial.println("ESP32 eg.04 LE");       // 「Example 04」をシリアル出力表示
    WiFi.mode(WIFI_STA);                    // 無線LANをSTAモードに設定
//  delay(10);                              // ESP32に必要な待ち時間(2017/8削除)
    WiFi.begin(SSID,PASS);                  // 無線LANアクセスポイントへ接続
    while(WiFi.status() != WL_CONNECTED){   // 接続に成功するまで待つ
        delay(100);                         // 待ち時間処理
        waiting++;                          // 待ち時間カウンタを1加算する
        digitalWrite(PIN_EN,waiting%2);     // LED(EN信号)の点滅
        if(waiting%10==0)Serial.print('.'); // 進捗表示
        if(waiting > 300) sleep();          // 300回(30秒)を過ぎたらスリープ
    }
    Serial.println(WiFi.localIP());         // 本機のIPアドレスをシリアル出力
    ambient.begin(AmbientChannelId, AmbientWriteKey, &client);  // Ambient開始
}

void loop(){
    WiFiUDP udp;                            // UDP通信用のインスタンスを定義
    float adc;                              // 変数adcを定義
    char s[20];                             // 表示用
    
    digitalWrite(PIN_EN,HIGH);              // センサ用の電源をONに
    delay(5);                               // 起動待ち時間
    adc=mvAnalogIn(PIN_AIN)/1000;           // AD変換器から値を取得 mV -> V
    digitalWrite(PIN_EN,LOW);               // センサ用の電源をOFFに
    udp.beginPacket(SENDTO, PORT);          // UDP送信先を設定
    udp.print(DEVICE);                      // デバイス名を送信
    udp.print(adc,3);                       // 変数adcの値を送信
    Serial.print(adc,3);                    // シリアル出力表示
    udp.print(", ");                        // カンマを送信
    Serial.print(", ");                     // カンマを出力表示
    t+=((float)millis())/1000;              // 現在のmillis値を加算
    udp.println(t,3);                       // 変数sの値を送信
    Serial.println(t,3);                    // シリアル出力表示
    udp.endPacket();                        // UDP送信の終了(実際に送信する)
    /* Ambientへ送信 */
    dtostrf(adc,2,3,s);                     // 電圧値を文字列に変換
    ambient.set(1,s);                       // Ambient(データ1)へ送信
    dtostrf(t,2,3,s);                       // 時間を文字列に変換
    ambient.set(DATA_NUM,s);                // Ambient(データ#)へ送信
    ambient.send();                         // Ambient送信の終了(実際に送信する)
    sleep();
}

void sleep(){
    delay(200);                             // 送信待ち時間
    esp_deep_sleep(SLEEP_P);                // Deep Sleepモードへ移行
}

float mvAnalogIn(uint8_t PIN){              // オートレンジ・ADC入力(出力 mV)
    float in;                               // ADC入力値
    int att;                                // 減衰量 adc_attenuation_t型
    int mv[4]={1100,1400,1900,3200};        // 基準電圧 mV
    for(att=3;att>=0;att--){                // 減衰量を減らしてゆく
        analogSetPinAttenuation(PIN,(adc_attenuation_t)att);    // 減衰量設定
        in=(float)analogRead(PIN_AIN)*(float)mv[att]/4095.;     // 電圧値入力
        if( att>0 ) if( (int)in > (mv[att-1]/9*8) ) break;      // 超過判定
    }
    return in;
}
