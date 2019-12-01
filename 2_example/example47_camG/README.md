# トラブルシューティング

## 電源が安定しているかどうか
電源が不安定だと、ESPモジュールが起動しない、または起動しても
正しく動作しないことがあります。
起動時やWi-Fi接続時、カメラ動作時は、多くの電流を消費するので、
目安として600mA程度の電流が流せる電源回路を使用してください。

## シリアルのTXDとRXDはクロス接続
カメラのTXDをESPモジュールのRXD(本サンプルではGPIO16(27番ピン))に、
カメラのRXDをESPモジュールのTXD(本サンプルではGPIO17(28番ピン))に
接続してください。

## LCDに「ESP32 eg15 Cam」が表示されたまま動作しない
SPIFFSが無効になっています。
コンパイル時に128KB以上のSPIFFS(最新SDKではFSと表示)を設定して
ください。

## LCDに「Cam Init」が表示されたまま動作しない①
Wi-Fiアクセスポイントとの接続に失敗しています。
無線LANアクセスポイントのSSIDとパスワードをプログラム内の
#define SSIDとPASSに設定して下さい。

## LCDに「Cam Init」が表示されたまま動作しない②
カメラとの通信に失敗しています。
カメラの電源電圧、シリアル配線などを確認してください。

## Raspberry Piで受信できない
しばらく待って、LCDに「Sleeping」「zzz...」と表示されることを
確認してください。表示されたら、ENボタンを押して、再送信して
みて下さい。
それでも、動作しない場合は、
ネットワーク内のDHCPサーバが動作していない、
異なる無線LANアクセスポイントへ接続されている、
異なるIPアドレスが設定されている、
無線LANアクセスポイントやRaspberry Piのファイヤーウォール等で
パケットが破棄されているなどが考えられます。

## 動作ログの確認方法（ご参考）
Arduino IDEのウィンドウ右上にある虫眼鏡のアイコンをクリックし、
「シリアルモニタ」を起動し、シリアルモニタの右下のボーレートを
115200に設定すると、動作ログが表示されます。