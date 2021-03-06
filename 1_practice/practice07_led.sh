#!/bin/bash
# 天気をLEDの状態で表示する
#
# ご注意：
#   ・Yahoo!天気・災害の情報を商用で利用する場合はYahoo! Japanの承諾が必要です。
#   ・Yahoo!サービスの利用規約にしたがって利用ください。
#           https://about.yahoo.co.jp/docs/info/terms/

IP_LED="192.168.0.2"                                        # ワイヤレスLEDのIP
WEATHER=`curl -s rss.weather.yahoo.co.jp/rss/days/43.xml\
|cut -d'<' -f17|cut -d'>' -f2|tail -1\
|cut -d' ' -f5|cut -c1-3`                                   # 天気を取得する
echo -n `date "+%Y/%m/%d %R"`", "$WEATHER", "               # テキスト表示
case $WEATHER in                                            # 天気に応じた処理
    "晴" )  LED=1;;                                         # 晴の時は明るく点灯
    "曇" )  LED=-1;;                                        # 曇の時は暗く点灯
    * ) LED=5;;                                             # その他の時は点滅
esac                                                        # caseの終了
curl -s $IP_LED -XPOST -d"L=$LED"|grep "<p>"|grep -v "http"\
|cut -d'>' -f2|cut -d'<' -f1                                # ワイヤレスLED制御
