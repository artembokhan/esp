/*******************************************************************************
Example 18: Wi-Fi コンシェルジェ 掲示板担当（LCD制御)
HTTPによるWebサーバ機能搭載 Wi-Fiコンシェルジェが液晶画面を制御します。

                                          Copyright (c) 2016-2019 Wataru KUNINO
*******************************************************************************/

#include <ESP8266WiFi.h>                    // Wi-Fi機能を利用するために必要
extern "C" {
#include "user_interface.h"                 // ESP8266用の拡張IFライブラリ
}
#include <WiFiUdp.h>                        // UDP通信を行うライブラリ
#define TIMEOUT 20000                       // タイムアウト 20秒
#define SSID "1234ABCD"                     // 無線LANアクセスポイントのSSID
#define PASS "password"                     // パスワード
#define PORT 1024                           // 受信ポート番号
WiFiUDP udp;                                // UDP通信用のインスタンスを定義
WiFiServer server(80);                      // Wi-Fiサーバ(ポート80=HTTP)定義

void setup(){                               // 起動時に一度だけ実行する関数
    lcdSetup(16,2);                         // 液晶の初期化(16桁×2行)
    wifi_set_sleep_type(LIGHT_SLEEP_T);     // 省電力モード設定
    WiFi.mode(WIFI_STA);                    // 無線LANをSTAモードに設定
    WiFi.begin(SSID,PASS);                  // 無線LANアクセスポイントへ接続
    while(WiFi.status() != WL_CONNECTED){   // 接続に成功するまで待つ
        delay(500);                         // 待ち時間処理
    }
    server.begin();                         // サーバを起動する
    udp.begin(PORT);                        // UDP通信御開始
    lcdPrint("Example 18 LCD");             // 「Example 18」をLCDに表示する
    lcdPrintIp2(WiFi.localIP());            // IPアドレスを液晶の2行目に表示
}

void loop(){                                // 繰り返し実行する関数
    WiFiClient client;                      // Wi-Fiクライアントの定義
    char c;                                 // 文字変数cを定義
    char s[65];                             // 文字列変数を定義 65バイト64文字
    char lcd[65]="no+data";                 // LCD表示用文字列変数 64文字
    int len=0;                              // 文字列長を示す整数型変数を定義
    int t=0;                                // 待ち受け時間のカウント用の変数
    int postF=0;                            // POSTフラグ(0:未 1:POST 2:BODY)
    int postL=64;                           // POSTデータ長

    client = server.available();            // 接続されたTCPクライアントを生成
    if(client==0){                          // TCPクライアントが無かった場合
        len = udp.parsePacket();            // UDP受信パケット長を変数lenに代入
        if(len==0)return;                   // TCPとUDPが未受信時にloop()先頭へ
        memset(s, 0, 65);                   // 文字列変数sの初期化(65バイト)
        udp.read(s, 64);                    // UDP受信データを文字列変数sへ代入
        lcdPrint(s);                        // 液晶に表示する
        return;                             // loop()の先頭に戻る
    }
    lcdPrint("TCP Connected");              // 接続されたことを表示
    while(client.connected()){              // 当該クライアントの接続状態を確認
        if(client.available()){             // クライアントからのデータを確認
            t=0;                            // 待ち時間変数をリセット
            c=client.read();                // データを文字変数cに代入
            if(c=='\n'){                    // 改行を検出した時
                if(postF==0){               // ヘッダ処理
                    if(len>11 && strncmp(s,"GET /?TEXT=",11)==0){
                        strncpy(lcd,&s[11],64);     // 受信文字列をlcdへコピー
                        break;              // 解析処理の終了
                    }else if (len>5 && strncmp(s,"GET /",5)==0){
                        break;              // 解析処理の終了
                    }else if(len>6 && strncmp(s,"POST /",6)==0){
                        postF=1;            // POSTのBODY待ち状態へ
                    }
                }else if(postF==1){
                    if(len>16 && strncmp(s,"Content-Length: ",16)==0){
                        postL=atoi(&s[16]); // 変数postLにデータ値を代入
                    }
                }
                if( len==0 ) postF++;       // ヘッダの終了
                len=0;                      // 文字列長を0に
            }else if(c!='\r' && c!='\0'){
                s[len]=c;                   // 文字列変数に文字cを追加
                len++;                      // 変数lenに1を加算
                s[len]='\0';                // 文字列を終端
                if(len>=64) len=63;         // 文字列変数の上限
            }
            if(postF>=2){                   // POSTのBODY処理
                if(postL<=0){               // 受信完了時
                    if(len>5 && strncmp(s,"TEXT=",5)==0){
                        strncpy(lcd,&s[5],64);      // 受信文字列をlcdへコピー
                    }
                    break;                  // 解析処理の終了
                }
                postL--;                    // 受信済POSTデータ長の減算
            }
        }
        t++;                                // 変数tの値を1だけ増加させる
        if(t>TIMEOUT) break; else delay(1); // TIMEOUTに到達したらwhileを抜ける
    }
    delay(1);                               // クライアント側の応答待ち時間
    trUri2txt(lcd);                         // URLエンコードの変換処理
    lcdPrint(lcd);                          // 受信文字データを液晶へ表示
    if(client.connected()){                 // 当該クライアントの接続状態を確認
        html(client,lcd,WiFi.localIP());    // HTMLコンテンツを出力する
    }
//  client.stop();                          // クライアントの切断
}
