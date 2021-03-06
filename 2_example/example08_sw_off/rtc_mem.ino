/*******************************************************************************
RTC内のメモリの読み書きドライバ(整数値)

下記のウェブサイトの情報に基づいて作成しました。

http://jiwashin.blogspot.jp/2016/07/esp30.html
https://lowreal.net/2016/01/10/1
*******************************************************************************/
//#define DEBUG
#define kOffset         65
int WAKE_COUNT;

struct RtcStorage{
    char iot[4];
    int count;
    int data;
};

#ifdef DEBUG
void printRtcInt(char *iot,int count, int data,int size){
    Serial.print("Ident = "); Serial.print(iot);
    Serial.print(", Count = "); Serial.print(count);
    Serial.print(", Value = "); Serial.print(data);
    Serial.print(", Size  = "); Serial.println(size);
}
#endif

int readRtcInt(){
    struct RtcStorage mem_init={"IoT",0,0};
    struct RtcStorage mem_read={"...",0,0};
    bool ok;

    ok = system_rtc_mem_read(kOffset, &mem_read, sizeof(mem_read));
    #ifdef DEBUG
        Serial.println("Read from RTC Memory");
        printRtcInt(mem_read.iot, mem_read.count, mem_read.data, sizeof(mem_read));
    #else
        Serial.print(mem_read.count); Serial.print(" ");
        Serial.println(mem_read.data);
    #endif
    if(!ok || strncmp(mem_init.iot,mem_read.iot,3) ){
        #ifdef DEBUG
            Serial.println("Initializing...");
            printRtcInt(mem_init.iot, mem_init.count, mem_init.data, sizeof(mem_init));
        #endif
        ok=system_rtc_mem_write(kOffset, &mem_init, sizeof(mem_init));
        mem_read.count=1;
        if (!ok) Serial.println("readRtcInt : write fail");
    }else{
        mem_read.count++;
        ok = system_rtc_mem_write(kOffset, &mem_read, 4 + sizeof(int) );
        if (!ok) Serial.println("readRtcInt : write fail");
    }
    WAKE_COUNT=mem_read.count;
    return mem_read.data;
}

bool writeRtcInt(int in) {
    struct RtcStorage mem={"IoT",WAKE_COUNT,in};
    bool ok;

    #ifdef DEBUG
        Serial.println("Write to RTC Memory");
        printRtcInt(mem.iot, mem.count, mem.data, sizeof(mem));
    #endif
    ok = system_rtc_mem_write(kOffset, &mem, sizeof(mem));
    if(!ok) Serial.println("Error : writeRtcInt : system_rtc_mem_write fail");
    return ok;
}
