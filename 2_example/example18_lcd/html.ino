/*******************************************************************************
HTMLコンテンツ 液晶

                                          Copyright (c) 2016-2019 Wataru KUNINO
*******************************************************************************/

void html(WiFiClient &client, char *lcd, uint32_t ip){
    char s[65],s_ip[16];
    
    sprintf(s_ip,"%d.%d.%d.%d",
        ip & 255,
        ip>>8 & 255,
        ip>>16 & 255,
        ip>>24
    );
    client.println("HTTP/1.1 200 OK");              // HTTP OKを応答
    client.println("Content-Type: text/html");      // HTMLコンテンツ
    client.println("Connection: close");            // 応答終了後にセッションを閉じる
    client.println();
    client.println("<html>");
    client.println("<head><title>Wi-Fi コンシェルジェ 掲示板担当</title>");
    client.println("<meta http-equiv=\"Content-type\" content=\"text/html; charset=UTF-8\">");
    client.println("</head>");
    client.println("<body>");
    client.println("<h3>LCD STATUS</h3>");
    client.print("<p>");
    client.print(lcd);    
    client.println("</p>");
    client.println("<hr>");
    client.println("<h3>HTTP GET</h3>");
    client.print("<p>http://");
    client.print(s_ip);
    client.println("/?TEXT=文字列</p>");
    sprintf(s,"<form method=\"GET\" action=\"http://%s/\">",s_ip);
    client.println(s);
    client.println("<input type=\"submit\" name=\"TEXT\" value=\"Hello\">");
    client.println("</form>");
    client.println(s);
    client.println("<input type=\"text\" name=\"TEXT\" value=\"\">");
    client.println("<input type=\"submit\" value=\"送信\">");
    client.println("</form>");
    client.println("<hr>");
    client.println("<h3>HTTP POST</h3>");
    sprintf(s,"<form method=\"POST\" action=\"http://%s/\">",s_ip);
    client.println(s);
    client.println("<input type=\"submit\" name=\"TEXT\" value=\"Hello\">");
    client.println("</form>");
    client.println(s);
    client.println("<input type=\"text\" name=\"TEXT\" value=\"\">");
    client.println("<input type=\"submit\" value=\"送信\">");
    client.println("</form>");
    client.println("</body>");
    client.println("</html>");
}
