void LoginContr()
{
  if (AccessMode == true)
  {
    char _AccessLogin[sizeof(AccessLogin)], _AccessPassword[sizeof(AccessPassword)];
    AccessLogin.toCharArray(_AccessLogin, sizeof(_AccessLogin));
    AccessPassword.toCharArray(_AccessPassword, sizeof(_AccessPassword));
    if (!server.authenticate(_AccessLogin, _AccessPassword)) return server.requestAuthentication();
  }
}
//---------------------------------------------------------------------------
String refreshTempMessage(String url)
{
  String message;
  message = F("function refreshTempMessage(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_tempMess', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.nom_mess != 255) {location.href ='/tempMess?nom_mess='+data.nom_mess+'&url="); message += url; message += F("'}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshTempMessage, 1000);\n");

  return message;
}

String textStyle()
{
  String message;

  message = F(".textStyle1 {");
  message += F("width: 25px; height: 20px; text-align: center;");
  message += F("text-align: center;");
  message += F("}");
  message += F(".textStyle2 {");
  message += F("width: 45px; height: 20px; text-align: center;");
  message += F("text-align: center;");
  message += F("}");

  return message;
}
//--------------------------------------------
String fillTimer()
{
  String message;


  return message;
}
//---------------------------------------------------------------------------
void handleRoot()
{
  LoginContr();

  erSt = 0;
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<title>Котел на ESP</title>");
  message += F("<style type=\"text/css\">");
  message += F(".checkbox {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".checkbox + label {cursor:pointer;}");
  message += F(".checkbox:not(checked) {position:absolute; opacity:0; }");
  message += F(".checkbox:not(checked) + label {position:relative; padding:0 0 0 60px;}");
  message += F(".checkbox:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:50px; height:26px; border-radius:13px; background:#CDD1DA;box-shadow:inset 0 2px 3px rgba(0,0,0,.2);}");
  message += F(".checkbox:not(checked) + label:after {content:''; position:absolute; top:-2px; left:2px; width:22px; height:22px; border-radius:10px; background:#FFF; box-shadow:0 2px 5px rgba(0,0,0,.3); transition:all .2s;}");

  message += F(".checkbox:checked + label:before {background:#ec1212;}");
  message += F(".checkbox:checked + label:after {left:26px;}");

  message += F(".menu_but {width: 200px; text-align: center; padding: 5px;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += F("function refreshDataAlert(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('relay1').checked = data.relay1;\n");
  message +=         F("document.getElementById('relay2').checked = data.relay2;\n");
  message +=         F("document.getElementById('relay3').checked = data.relay3;\n");
  message +=         F("document.getElementById('strtworkwarm').innerHTML = data.strtworkwarm;\n");
  message +=         F("document.getElementById('power_ten').innerHTML = data.power_ten;\n");
  message +=         F("document.getElementById('strtworkmix').innerHTML = data.strtworkmix;\n");
  message +=         F("document.getElementById('strtworkotb').innerHTML = data.strtworkotb;\n");

  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] == 1) {
      message += F("document.getElementById('tempC"); message += String(i); message += F("').innerHTML = data.tempC"); message += String(i); message += F(";\n");
    }
  }
  message +=         F("document.getElementById('TimeOn').innerHTML = data.TimeOn;\n");
  message +=         F("document.getElementById('timeStr').innerHTML = data.timeStr;\n");
  message +=         F("if (data.beepeep > 0) {document.location.href = \"/alert\"}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshDataAlert, 1000);\n");
  //-------------------------
  message += F("function refreshTempMessage(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_tempMess', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.nom_mess != 255) {location.href ='/tempMess?nom_mess='+data.nom_mess+'&url=index.html'}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshTempMessage, 1000);\n");
  //------------------------
  message += refreshTempMessage(F("index.html"));

  message += F("function check_message(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/check', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.Prg == true) {document.getElementById('relay1').disabled=true} else {document.getElementById('relay1').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('relay2').disabled=true} else {document.getElementById('relay2').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('relay3').disabled=true} else {document.getElementById('relay3').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('relay3').disabled=true} else {document.getElementById('relay3').disabled=false};\n");

  message +=         F("if (data.Prg == true) {document.getElementById('butt_adjWarm').disabled=true} else {document.getElementById('butt_adjWarm').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_adjMix').disabled=true} else {document.getElementById('butt_adjMix').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_adjOtb').disabled=true} else {document.getElementById('butt_adjOtb').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_adjContr').disabled=true} else {document.getElementById('butt_adjContr').disabled=false};\n");

  message +=         F("if (data.Prg == true) {document.getElementById('butt_adjWifi').disabled=true} else {document.getElementById('butt_adjWifi').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_adjDevPrg').disabled=true} else {document.getElementById('butt_adjDevPrg').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_reboot').disabled=true} else {document.getElementById('butt_reboot').disabled=false};\n");

  message +=         F("if (data.needAlert == 1) {alert(data.AlertMessage);openUrl('/switch?Prg_message_show='+data.NumStrPrg);};\n");
  message +=         F("if (data.endPrg == 1) {alert(data.AlertMessage);openUrl('/switch?End_message_show='+data.NumStrPrg);}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(check_message, 2000);\n");

  message += F("</script>\n");
  message += F("</head>\n");
  message += F("<body>\n");
  message += F("<form>\n");
  message += F("<h3>Управление котлом v.2.4</h3><p>\n");
  message += F("<span id=\"timeStr\">.</span><br>\n");
  message += F("Время работы: <span id=\"TimeOn\">.</span></p>\n");
  message += F("<input type=\"checkbox\" class=\"checkbox\" id=\"relay1\" onchange=\"openUrl('/switch?swt1=' + this.checked);\" ");
  if (Prg_swt1 == HIGH) message += F("checked");
  message += F("/><label for=\"relay1\">Нагрев</label> </p>");
  message += F("<span id=\"strtworkwarm\">.</span> P%,<span id=\"power_ten\">0</span> </p>\n");

  message += F("<input type = \"checkbox\" class=\"checkbox\" id=\"relay2\" onchange=\"openUrl('/switch?swt2=' + this.checked);\" ");
  if (Prg_swt2 == HIGH) message += F("checked ");
  message += F("/><label for=\"relay2\">Мешалка</label><p>\n");

  message += F("<span id=\"strtworkmix\">.</span> </p>");
  message += F("<input type = \"checkbox\" class=\"checkbox\" id=\"relay3\" onchange=\"openUrl('/switch?swt3=' + this.checked);\" ");
  if (Prg_swt3 == HIGH) message += F("checked ");
  message += F("/><label for = \"relay3\">Отбор</label><p>\n");
  message += F("<span id=\"strtworkotb\">.</span> </p>\n");
  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] == 1) {
      message += F("Т"); message += String(i); message += F(": <span id=\"tempC"); message += String(i); message += F("\">.</span> &#176С ");
      if (tNameSens[i].length() > 0) {
        message += F(" /"); message += tNameSens[i] + F("/");
      }
      message += F("<br />\n");
    }
  }
  message += F("<p>\n");

  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjWarm\" value=\"Настройка нагрева\" onclick=\"location.href='/warm';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjMix\" value=\"Настройка мешалки\" onclick=\"location.href='/mixer';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjOtb\" value=\"Настройка отбора\" onclick=\"location.href='/otbor';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjContr\" value=\"Настройка контроля\" onclick=\"location.href='/select';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjDispTemp\" value=\"Настройка уведомлений\" onclick=\"location.href='/dispTemp';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Выбор программы\" onclick=\"location.href='/selprog';\" /><br>\n");
  message += F("<p>");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjWifi\" value=\"Настройка Wi-fi\" onclick=\"location.href='/wifi';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjTime\" value=\"Настройка времени\" onclick=\"location.href='/timeConf';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjDevPrg\" value=\"Обновление прошивки\" onclick=\"location.href='/update';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Менеджер файлов\" onclick=\"location.href='/spiffs';\" /><br>\n");
  message += F("<p>");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Перезагрузка\" id=\"butt_reboot\" onclick=\"if (confirm('Перезагрузить модуль?') == true) location.href='/reboot'\" /><br>\n");


  message += F("</form>\n");
  message += F(" </body>\n");
  message += F(" </html>\n");
  server.send(200, F("text/html"), message);
}
//------------------------------------
void h_data_resetMess()//data_resetMess
{
  String argName, argValue;
  uint8_t nom_mess;
  Serial.println(F("module data_resetMess"));
  Serial.print(F("args()="));
  Serial.println(server.args());
  for (byte i = 0; i < server.args(); i++)  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print("=");
    argValue = server.arg(i);
    Serial.println(argValue);

    if (argName == F("nom_mess")) {
      nom_mess = argValue.toInt();
      mesTemp[nom_mess].accompl = 1;
      Serial.println(F("установка признака получения сообщения"));
    }
  }
  server.send(200, F("text/html"), F("nishtiyk"));
}
//------------------------------------------------
void h_tempMess()//tempMess
{
  LoginContr();

  String argName, argValue, url;
  uint8_t nom_mess;
  Serial.println(F("module tempMess"));
  Serial.print(F("args()="));
  Serial.println(server.args());
  for (byte i = 0; i < server.args(); i++)  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print(F("="));
    argValue = server.arg(i);
    Serial.println(argValue);

    if (argName == F("nom_mess")) {
      nom_mess = argValue.toInt();
    }
    if (argName == F("url"))  url = argValue;
  }

  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Сообщения</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"5; /"); message += url; message += F("\">");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += F("function resetMess() {\n");
  message += F("openUrl('/data_resetMess?nom_mess='+'"); message += String(nom_mess) + F("');\n");
  message += F("};\n ");
  message += F("</script>");
  message += F("</head>");
  message += F("<body onload=setTimeout(\"resetMess()\",2500)>");
  message += F("Оповещение о достижении температуры.");
  message += F("<p>");
  message += String(mesTemp[nom_mess].Message);
  message += F("<p>");
  message += F("<B><big><font color=\"#FF0000\";\">"); message += String(mesTemp[nom_mess].TempM); message += F("</font></big></B><br>");
  message += F("<p>Ждите 3 сек. или нажмите <a href=\""); message += url; message += F("\">сюда</a> для возврата.");
  message += F("<audio autoplay loop=3>");
  message += F("<source src=\""); message += mesTemp[nom_mess].WavFile; message += F("\"");
  message += F("</audio>");

  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);

}
//---------------------------------------------------------------------------------
void h_data_tempMess()//data_tempMess
{
  LoginContr();
  String message;
  uint8_t nom_mess = 255;

  if (Prg_swt1 == true)
  { // кнопка нагрев
    for (byte k = 0; k < NomMessAll; k++) {
      if (mesTemp[k].Need == 1) {
        if ((tempC[mesTemp[k].NsenseM] >= mesTemp[k].TempM) && (mesTemp[k].accompl == 0)) {
          Serial.print("Достигли температуры "); Serial.print(mesTemp[k].TempM); Serial.print(" /"); Serial.println(mesTemp[k].Message);
          //mesTemp[k].accompl = 1;
          nom_mess = k;
          break;
        }
      }
    }
  }

  message += F("{");
  message += F("\"nom_mess\":"); message += nom_mess;
  message += F("}");

  server.send(200, F("text/html"), message);
}
//----------------------------------------------------------------------------------------------
void h_dispTemp()//dispTemp
{
  LoginContr();

  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<title>Котел на ESP</title>");
  message += F("<style type=\"text/css\">");
  message += F(".textfield {width: 50px; text-align: center;}");
  message += F(".textfield2 {width: 200px; text-align: left;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += refreshTempMessage("dispTemp");
  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"POST\" action=\"/save_m\">");
  message += F("<h3>Настройка уведомлений по температуре</h3><p>");

  if (NomMessAll > 0) {
    for (uint8_t i = 0; i < NomMessAll; i++)  {
      //-----------------------выводим строки                                           disabled = \"true\"
      message += F("<input type = \"checkbox\" name=\"accompl"); message += String(i) + F("\" id=\"accompl"); message += String(i) + F("\" title=\"данный сигнал прозвучал\"");
      if (mesTemp[i].accompl == 1) message += " checked=\"checked\"";
      message += F("onchange=\"openUrl('/switch?accompl_m=' + this.id);\" ");
      message += F("<label for=\"accompl"); message += String(i) + F("\"></label>");

      message += F("<input type = \"checkbox\" name=\"Need"); message += String(i) + F("\" id=\"Need"); message += String(i) + F("\" title=\"использовать данный сигнал\"");
      if (mesTemp[i].Need == 1) message += " checked=\"checked\"";
      message += F("onchange=\"openUrl('/switch?Need_m=' + this.id);\" ");
      message += F("<label for=\"Need"); message += String(i) + F("\">исп </label>");

      message += F("<select name=\"NsenseM"); message += String(i) + F("\" title=\"датчик \">");

      for (byte k = 0; k < NSenseFact; k++) {
        if (t[k] != 0) {
          Serial.println();
          message += F("<option value="); message += String(k);
          if (mesTemp[i].NsenseM == k) message += F(" selected");
          if (tNameSens[k].length() > 0) {
            message += F("> "); message += tNameSens[k] + F("</option>");
          }
          else {
            message += F(">Датчик "); message += String(k) + F("</option>");
          }
        }
      }
      message += F("</select> ");
      //--mesTemp[i].TempM
      message += F("<input id=\"TempM"); message += String(i) + F("\" name=\"TempM"); message += String(i) + F("\" type=\"text\" class=\"textfield\" value=\"");
      message += mesTemp[i].TempM;
      message += F("\" maxlength=\"5\"/>&#176С ");

      //--WawFile
      message += F("<select name=\"WavFile"); message += String(i) + F("\" id=\"WavFile"); message += String(i) + F("\" title=\"\" >\n");
      Dir dir = SPIFFS.openDir("/");

      while (dir.next())
      {
        String fileName = dir.fileName();
        if (fileName.startsWith("/")) fileName = fileName.substring(1);
        //Serial.println(fileName);

        if (fileName.endsWith(".wav"))
        {
          message += F("<option value=\"");
          message += fileName;
          message += F("\"");
          if (mesTemp[i].WavFile == fileName) message += F(" selected ");
          message += F(">");
          message += fileName;
          message += F("</option>");
        }
      }
      message += F("</select> ");

      //--mesTemp[i].Message
      message += F("<input id=\"Message"); message += String(i) + F("\" name=\"Message"); message += String(i) + F("\" type=\"text\" class=\"textfield2\" value=\"");
      message += mesTemp[i].Message;
      message += F("\" maxlength=\"150\"/>");

      //--кнопка удаления
      message += F("<input type=\"button\" id=\"butt_del_m"); message += String(i) + F("\" value=\" X \" title=\"Удалить текущую строку\" onclick=\"openUrl('/switch?Del_m='+this.id); location.href='/dispTempProm'; \" >\n");
      message += F("<br />");
    }
  }
  message += F("<p>");
  message += F("<input type=\"button\" id=\"butt_add_m\" value=\" Добавить сигнал \" title=\"Добавить сигнал в список\" onclick=\"openUrl('/switch?Add_m='+this.id); location.href='/dispTempProm'; \" >\n");
  message += F("<p>");

  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\"> ");
  message += F("<input type=\"submit\" id=\"butt_save_m\" value=\"Сохранить\" action=\"/save_m\">\n");
  message += F("</form>");

  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------
void h_dispTempInf()//dispTempProm
{
  LoginContr();

  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"1; /dispTemp\">");
  message += F("<style type=\"text/css\">");

  message += F("</head>");
  message += F("<body>");
  //message += F("<form method=\"GET\" class=\"modal\" action=\"\">");

  message += F("Удаление/добавление выполнено успешно.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/dispTemp\">сюда</a> для перехода в настройку сообщений.");

  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------
void save_SensorConfFile()
{
  Serial.println("Try open " + SensorConfFile);
  File f = SPIFFS.open("/" + SensorConfFile, "w");
  if (!f)
  {
    Serial.println(F("file open failed"));
  }
  else
  {
    Serial.println(F(" Writing SPIFFS file "));
    String strM;

    for (int i = 0; i < NSenseFact; i++) {
      strM = F("{\"t\":"); strM += String(t[i]) + ",";
      strM += F("\"frame\":[");
      for (uint8_t k = 0; k < 8; k++) {
        strM += String(insideThermometer[i][k]);
        if (k != 7) strM += F(",");
      }
      strM += F("],");
      strM += F("\"tNameSens\":\""); strM += String(tNameSens[i]) + F("\"");
      strM += F("}");
      Serial.println(strM);
      f.println(strM);
    }

    f.print(F("END"));
    f.close();
    Serial.println(F(" done."));

  }
}
//-----------------------------------------------------------------------------------------

void save_CfgFile()
{
  Serial.print("Try save " + NameSettingsFile);
  File f = SPIFFS.open("/" + NameSettingsFile, "w");
  if (!f)
  {
    Serial.println(F("....failed"));
  }
  else
  {
    Serial.println(F("..... Writing SPIFFS file "));

    String strM;
    strM = F("{\"Vol\":"); strM += F("0,");
    strM += F("\"WarmVol\":"); strM += String(WarmVol) + F(",");
    strM += F("\"TkVol\":"); strM += String(TkVol) + F(",");
    strM += F("\"ModeWarm\":"); strM += String(ModeWarm) + F(",");
    strM += F("\"consK\":["); strM += String(consKp) + F(","); strM += String(consKi) + F(","); strM += String(consKd) + F("],");
    strM += F("\"aggK\":["); strM += String(aggKp) + F(","); strM += String(aggKi) + F(","); strM += String(aggKd) + F("],");
    strM += F("\"gap\":"); strM += String(gap) + F(",");
    strM += F("\"TSec\":"); strM += String(TSec) + F(",");
    strM += F("\"WarmTime\":["); strM += String(WarmHour) + F(","); strM += String(WarmMin) + F(","); strM += String(WarmSec) + F("],");
    strM += F("\"Nsense\":"); strM += String(Nsense) + F(",");
    strM += F("\"TWarmContr\":"); strM += String(TWarmContr) + F(",");
    strM += F("\"NsenseWarmContr\":"); strM += String(NsenseWarmContr) + F(",");;

    TimerWarmStUnx = combineUnixTime(TimerWarmHourSt, TimerWarmMinSt, TimerWarmSecSt, TimerWarmDaySt, TimerWarmMonthSt, TimerWarmYearSt); // Собрать время в формат UNIX-time
    TimerWarmEndUnx = combineUnixTime(TimerWarmHourEnd, TimerWarmMinEnd, TimerWarmSecEnd, TimerWarmDayEnd, TimerWarmMonthEnd, TimerWarmYearEnd); // Собрать время в формат UNIX-time

    strM += F("\"TimerWarmAvailSt\":"); strM += String(TimerWarmAvailSt) + F(",");
    strM += F("\"TimerWarmStUnx\":"); strM += String(TimerWarmStUnx) + F(",");
    strM += F("\"TimerWarmAvailEnd\":"); strM += String(TimerWarmAvailEnd) + F(",");
    strM += F("\"TimerWarmEndUnx\":"); strM += String(TimerWarmEndUnx);
    strM += F("}");
    Serial.println(strM); f.println(strM);

    strM = F("{\"Vol\":"); strM += F("1,");
    strM += F("\"MixOnTime\":["); strM += String(MixOnHour) + F(","); strM += String(MixOnMin) + F(","); strM += String(MixOnSec) + F("],");
    strM += F("\"MixOffTime\":["); strM += String(MixOffHour) + F(","); strM += String(MixOffMin) + F(","); strM += String(MixOffSec) + F("],");
    strM += F("\"MixTime\":["); strM += String(MixHour) + F(","); strM += String(MixMin) + F(","); strM += String(MixSec) + F("],");
    strM += F("\"TMixContr\":"); strM += String(TMixContr) + F(",");
    strM += F("\"NsenseMixContr\":"); strM += String(NsenseMixContr) + F(",");;

    for (byte i = 0; i < NomPrerMixAll; i++) {
      PrerMix[i].PrerMixStUnx = combineUnixTime(PrerMix[i].PrerMixHourSt, PrerMix[i].PrerMixMinSt, 0, 1, 1, 1970); // Собрать время в формат UNIX-time
      PrerMix[i].PrerMixEndUnx = combineUnixTime(PrerMix[i].PrerMixHourEnd, PrerMix[i].PrerMixMinEnd, 0, 1, 1, 1970); // Собрать время в формат UNIX-time

      strM += F("\"Avail"); strM +=   String(i) + F("\":"); strM += String(PrerMix[i].Avail) + F(",");
      strM += F("\"PrerMixStUnx"); strM +=  String(i) + F("\":"); strM += String(PrerMix[i].PrerMixStUnx) + F(",");
      strM += F("\"PrerMixEndUnx"); strM +=  String(i) + F("\":"); strM += String(PrerMix[i].PrerMixEndUnx) + F(",");
    }

    TimerMixStUnx = combineUnixTime(TimerMixHourSt, TimerMixMinSt, TimerMixSecSt, TimerMixDaySt, TimerMixMonthSt, TimerMixYearSt); // Собрать время в формат UNIX-time
    TimerMixEndUnx = combineUnixTime(TimerMixHourEnd, TimerMixMinEnd, TimerMixSecEnd, TimerMixDayEnd, TimerMixMonthEnd, TimerMixYearEnd); // Собрать время в формат UNIX-time

    strM += F("\"TimerMixAvailSt\":"); strM += String(TimerMixAvailSt) + F(",");
    strM += F("\"TimerMixStUnx\":"); strM += String(TimerMixStUnx) + F(",");
    strM += F("\"TimerMixAvailEnd\":"); strM += String(TimerMixAvailEnd) + F(",");
    strM += F("\"TimerMixEndUnx\":"); strM += String(TimerMixEndUnx);


    strM += F("}");
    Serial.println(strM); f.println(strM);
    strM = F("{\"Vol\":"); strM += F("2,");
    strM += F("\"PercOtb\":"); strM += String(PercOtb) + F(",");
    strM += F("\"TimeOtbPeriod\":"); strM += String(TimeOtbPeriod) + F(",");
    strM += F("\"TstOtb\":"); strM += String(TstOtb) + F(",");
    strM += F("\"TendOtb\":"); strM += String(TendOtb) + F(",");
    strM += F("\"NsenseOtbContr\":"); strM += String(NsenseOtbContr);
    strM += F("}");
    Serial.println(strM); f.println(strM);
    strM = F("{\"Vol\":"); strM += F("3,");
    strM += F("\"relayLevel\":["); strM += String(relay1Level) + F(","); strM += String(relay2Level) + F(","); strM += String(relay3Level) + F("],");
    strM += F("\"ntpServer\":[\""); strM += ntpServer1 + F("\",\""); strM += ntpServer2 + F("\",\""); strM += ntpServer3 + F("\"],");
    strM += F("\"updateInterval\":"); strM += String(updateInterval) + F(",");
    strM += F("\"timeZone\":"); strM += String(timeZone) + F(",");
    strM += F("\"ntpUpd\":"); strM += String(ntpUpd) + F(",");

    strM += F("\"Zaderj\":"); strM += String(Zaderj) + F(",");
    strM += F("\"jamp_t\":"); strM += String(jamp_t) + F(",");
    strM += F("\"error_read_ds_Max\":"); strM += String(error_read_ds_Max) + F(",");
    strM += F("\"t_msec_get_ds\":"); strM += String(t_msec_get_ds);
    strM += F("}");
    Serial.println(strM); f.println(strM);
    f.print(F("END"));
    f.close();
    Serial.println(F(" done."));
  }
}
//------------------------------------------------------------
void save_MsgFile()
{
  Serial.print("Try save " + NameMsgFile);
  File f = SPIFFS.open("/" + NameMsgFile, "w");
  if (!f)
  {
    Serial.println(F("....failed"));
  }
  else
  {
    Serial.println(F("..... Writing SPIFFS file "));

    for (byte k = 0; k < NomMessAll; k++)
    {
      String strM;
      strM = F("{\"Need\":"); strM += String(mesTemp[k].Need) + F(",");
      strM += F("\"NsenseM\":"); strM += String(mesTemp[k].NsenseM) + F(",");
      strM += F("\"TempM\":"); strM += String(mesTemp[k].TempM) + F(",");
      strM += F("\"WavFile\":\""); strM += mesTemp[k].WavFile; strM += F("\",");
      strM += F("\"Message\":\""); strM += mesTemp[k].Message; strM += F("\"}");
      Serial.println(strM);
      f.println(strM);
    }

    f.print(F("END"));
    f.close();
    Serial.println(F(" done."));

  }
}
//------------------------------------------------------------
void h_save_m()//save_m
{
  LoginContr();

  if (NomMessAll > 0) {
    String argName, argValue;
    Serial.println(F("module save_m"));
    Serial.print(F("args()="));
    Serial.println(server.args());

    for (uint8_t k = 0; k < NomMessAll; k++) {
      mesTemp[k].Need = 0;
    }
    for (uint8_t i = 0; i < server.args(); i++) {
      argName = server.argName(i);
      Serial.print(argName);
      Serial.print(F("="));
      argValue = server.arg(i);
      Serial.println(argValue);

      for (uint8_t k = 0; k < NomMessAll; k++) {
        String argN;
        argN = F("Need"); argN += String(k);
        if (argName == argN) {
          if (argValue == F("on")) mesTemp[k].Need = 1;
          else mesTemp[k].Need = 0;
        }
        argN = F("NsenseM"); argN += String(k);
        if (argName == argN) mesTemp[k].NsenseM = argValue.toInt();
        argN = F("TempM"); argN += String(k);
        if (argName == argN) mesTemp[k].TempM = atof(argValue.c_str());
        argN = F("WavFile"); argN += String(k);
        if (argName == argN) mesTemp[k].WavFile = argValue;
        argN = F("Message"); argN += String(k);
        if (argName == argN) mesTemp[k].Message = argValue;
      }
    }
    save_MsgFile();
  }
  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /dispTemp\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Настройи сохранены успешно.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/dispTemp\">сюда</a> для перехода в настройку сообщений.");
  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------
/*void h_save_sens()//save_sens
  {
  LoginContr();

  if (NomMessAll > 0) {
    String argName, argValue;
    Serial.println(F("module save_sens"));
    Serial.print(F("args()="));
    Serial.println(server.args());

    for (uint8_t k = 0; k < NomMessAll; k++) {
      mesTemp[k].Need = 0;
    }
    for (uint8_t i = 0; i < server.args(); i++) {
      argName = server.argName(i);
      Serial.print(argName);
      Serial.print(F("="));
      argValue = server.arg(i);
      Serial.println(argValue);

      for (uint8_t k = 0; k < NomMessAll; k++) {
        String argN;
        argN = F("Need"); argN += String(k);
        if (argName == argN) {
          if (argValue == F("on")) mesTemp[k].Need = 1;
          else mesTemp[k].Need = 0;
        }
      }
    }
  }
  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /dispTemp\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Настройи сохранены успешно.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/dispTemp\">сюда</a> для перехода в настройку сообщений.");
  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
  }
  //---------------------------------------------------------------------------------
*/
void h_save() //save
{
  LoginContr();
  String argName, argValue;
  Serial.println("module save");
  Serial.print("args()=");
  Serial.println(server.args());
  for (byte i = 0; i < server.args(); i++)
  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print("=\"");
    argValue = server.arg(i);
    Serial.print(argValue);
    Serial.println("\"");

    if (argName == F("ssid"))                  ssid = argValue;
    else if (argName == F("password"))     password = argValue;
    else if (argName == F("AccessLogin"))     AccessLogin = argValue;
    else if (argName == F("AccessPassword"))     AccessPassword = argValue;

    else if (argName == F("ip1"))               ip1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip2"))               ip2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip3"))               ip3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip4"))               ip4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("ms1"))               ms1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms2"))               ms2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms3"))               ms3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms4"))               ms4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("gt1"))               gt1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt2"))               gt2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt3"))               gt3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt4"))               gt4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("dn1"))               dn1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn2"))               dn2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn3"))               dn3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn4"))               dn4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("MixOnHour"))   MixOnHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("MixOnMin"))     MixOnMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("MixOnSec"))     MixOnSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("MixOffHour")) MixOffHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("MixOffMin"))   MixOffMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("MixOffSec"))   MixOffSec = constrain(argValue.toInt(), 0, 59);

    else if (argName == F("MixHour"))     MixHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("MixMin"))       MixMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("MixSec"))       MixSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TMixContr")) TMixContr = argValue.toInt();
    else if (argName == F("NsenseMixContr")) NsenseMixContr = argValue.toInt();

    else if (argName == F("TkVol"))           TkVol = atof(argValue.c_str());
    else if (argName == F("WarmVol"))       WarmVol = constrain(argValue.toInt(), 0, 150);
    else if (argName == F("Nsense"))         Nsense = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ModeWarm"))     ModeWarm = argValue.toInt();
    else if (argName == F("WarmHour"))     WarmHour = constrain(argValue.toInt(), 0, 100);
    else if (argName == F("WarmMin"))       WarmMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("WarmSec"))       WarmSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TSec"))             TSec = argValue.toInt();

    else if (argName == F("aggKp"))             aggKp = atof(argValue.c_str());
    else if (argName == F("aggKi"))             aggKi = atof(argValue.c_str());
    else if (argName == F("aggKd"))             aggKd = atof(argValue.c_str());
    else if (argName == F("consKp"))           consKp = atof(argValue.c_str());
    else if (argName == F("consKi"))           consKi = atof(argValue.c_str());
    else if (argName == F("consKd"))           consKd = atof(argValue.c_str());
    else if (argName == F("gap"))           gap = atof(argValue.c_str());

    else if (argName == F("PercOtb")) PercOtb = argValue.toInt();
    else if (argName == F("TimeOtbPeriod")) TimeOtbPeriod = argValue.toInt();
    else if (argName == F("TstOtb"))         TstOtb = atof(argValue.c_str());
    else if (argName == F("TendOtb"))       TendOtb = atof(argValue.c_str());
    else if (argName == F("NsenseOtbContr")) NsenseOtbContr = argValue.toInt();

    else if (argName == F("TWarmContr")) TWarmContr = atof(argValue.c_str());
    else if (argName == F("NsenseWarmContr")) NsenseWarmContr = argValue.toInt();
    else if (argName == F("NameProg"))               NameProg = argValue;

    else if (argName == F("Zaderj"))                        Zaderj = constrain(argValue.toInt(), 0, 1000);
    else if (argName == F("jamp_t"))                        jamp_t = constrain(argValue.toInt(), 0, 99);
    else if (argName == F("error_read_ds_Max"))  error_read_ds_Max = constrain(argValue.toInt(), 2, 99);
    else if (argName == F("t_msec_get_ds"))          t_msec_get_ds = constrain(argValue.toInt(), 100, 40000);

    else if (argName == F("ntpServer1"))     ntpServer1 = argValue;
    else if (argName == F("ntpServer2"))     ntpServer2 = argValue;
    else if (argName == F("ntpServer3"))     ntpServer3 = argValue;
    else if (argName == F("updateInterval"))     updateInterval = argValue.toInt();
    else if (argName == F("timeZone"))     timeZone = argValue.toInt();

    else if (argName == F("TimerWarmDaySt"))  TimerWarmDaySt = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerWarmMonthSt"))  TimerWarmMonthSt = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerWarmYearSt"))  TimerWarmYearSt = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerWarmHourSt"))  TimerWarmHourSt = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerWarmMinSt"))  TimerWarmMinSt = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerWarmSecSt"))  TimerWarmSecSt = constrain(argValue.toInt(), 0, 59);


    else if (argName == F("TimerWarmDayEnd"))  TimerWarmDayEnd = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerWarmMonthEnd"))  TimerWarmMonthEnd = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerWarmYearEnd"))  TimerWarmYearEnd = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerWarmHourEnd"))  TimerWarmHourEnd = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerWarmMinEnd"))  TimerWarmMinEnd = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerWarmSecEnd"))  TimerWarmSecEnd = constrain(argValue.toInt(), 0, 59);
    //---------------
    else if (argName == F("TimerMixDaySt"))  TimerMixDaySt = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerMixMonthSt"))  TimerMixMonthSt = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerMixYearSt"))  TimerMixYearSt = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerMixHourSt"))  TimerMixHourSt = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerMixMinSt"))  TimerMixMinSt = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerMixSecSt"))  TimerMixSecSt = constrain(argValue.toInt(), 0, 59);


    else if (argName == F("TimerMixDayEnd"))  TimerMixDayEnd = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerMixMonthEnd"))  TimerMixMonthEnd = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerMixYearEnd"))  TimerMixYearEnd = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerMixHourEnd"))  TimerMixHourEnd = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerMixMinEnd"))  TimerMixMinEnd = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerMixSecEnd"))  TimerMixSecEnd = constrain(argValue.toInt(), 0, 59);

    String _argName;
    for (byte i = 0; i < NomPrerMixAll; i++) {

      _argName = F("PrerMixHourSt"); _argName += String(i);
      if (argName == _argName) {
        PrerMix[i].PrerMixHourSt = argValue.toInt();
      }

      _argName = F("PrerMixMinSt"); _argName += String(i);
      if (argName == _argName) {
        PrerMix[i].PrerMixMinSt = argValue.toInt();
      }

      _argName = F("PrerMixHourEnd"); _argName += String(i);
      if (argName == _argName) {
        PrerMix[i].PrerMixHourEnd = argValue.toInt();
      }

      _argName = F("PrerMixMinEnd"); _argName += String(i);
      if (argName == _argName) {
        PrerMix[i].PrerMixMinEnd = argValue.toInt();
      }
    }

    for (uint8_t k = 0; k < NSenseMax; k++)  {
      String argN;
      argN = F("tNameSens"); argN += String(k);
      if (argName == argN) tNameSens[k] = argValue;
    }
  }
  writeConfig();
  save_SensorConfFile();
  save_CfgFile();
  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /index.html\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Настройи сохранены успешно.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/index.html\">сюда</a> для перехода в главное меню.");
  message += F("</body>");
  message += F("</html>");

  server.send(200, F("text/html"), message);

}
//-------------------------------------------------------------------------

void h_alert() //alert
{
  LoginContr();
  Serial.println(F("/alert"));

  String message =
    F("<!DOCTYPE html>\n\
<html>\n\
<head>\n\
  <title>Alert</title>\n\
  <meta http-equiv=\"refresh\" content=\"5; /index.html\">\n\
  <meta charset=\"utf-8\">\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
</head>\n\
<body>\n");
  if (erSt == 1) {
    message += F("Внимание! Некорректные показания датчиков температуры!<br>");
    message += F("<B><big><font color=\"#FF0000\";\">ОСТАНОВ ВСЕГО, ЧТО ЗАВЯЗАНО НА ТЕМПЕРАТУРУ!</font></big></B><br>");
  }
  if (erSt == 2) {
    message += F("Внимание! Произошел перегрев холодильника!<br>");
    message += F("<B><big><font color=\"#FF0000\";\">ОСТАНОВ НАГРЕВА!</font></big></B><br>");
  }
  if (erSt == 3) {
    message += F("Внимание! Некорректные показания датчик контроля мешалки!<br>");
    message += F("<B><big><font color=\"#FF0000\";\">ОСТАНОВКА МЕШАЛКИ!</font></big></B><br>");
  }
  message += F("<br>\n\
  Через 5 сек. вы будете перенаправлены на основную страницу!\n\
  <audio autoplay>\n");
  if (erSt == 1) message += F("<source src=\"snd_err_sense.wav\"\n");
  if (erSt == 2) message += F("<source src=\"snd_err_overwarm.wav\"\n");
  if (erSt == 3) message += F("<source src=\"snd_err_mix.wav\"\n");
  message += F("</audio>\n\
</body>\n\
</html>");

  server.send(200, F("text/html"), message);

}
//-----------------------------------------------------------------------
void h_select()//select
{
  LoginContr();
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Управление контролем</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".checkbox {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".checkbox + label {cursor:pointer;}");
  message += F(".checkbox:not(checked) {position:absolute; opacity:0; }");
  message += F(".checkbox:not(checked) + label {position:relative; padding:0 0 0 60px;}");
  message += F(".checkbox:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:50px; height:26px; border-radius:13px; background:#CDD1DA;box-shadow:inset 0 2px 3px rgba(0,0,0,.2);}");
  message += F(".checkbox:not(checked) + label:after { content:''; position:absolute; top:-2px; left:2px; width:22px; height:22px; border-radius:10px; background:#FFF; box-shadow:0 2px 5px rgba(0,0,0,.3); transition:all .2s;}");
  message += F(".checkbox:checked + label:before {background:#9FD468;}");
  message += F(".checkbox:checked + label:after {left:26px;}");
  message += textStyle();
  message += F("</style>");
  message += F("<script type=\"text/javascript\">");
  message += F("function openUrl(url) {");
  message += F("var request = new XMLHttpRequest();");
  message += F("request.open('GET', url, true);");
  message += F("request.send(null);");
  message += F("}");
  message += F("function PowChange(Powval,k){");
  message += F("var ret;");
  message += F("if (isNaN(Powval)==true) return 0;");
  message += F("ret=(parseFloat(Powval,10)+k);");
  message += F("if (ret>100) ret=100;");
  message += F("if (ret<0) ret=0;");
  message += F("return ret;}");
  message += F("function CheckVal(obj){");
  message += F("var ret;");
  message += F("ret=(parseFloat(document.getElementById(obj).value,10));");
  message += F("if (isNaN(ret)==true) document.getElementById(obj).value=0;");
  message += F("if (isNaN(ret)==false) document.getElementById(obj).value=ret;}");
  message += F("function refreshSens(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('relay1Level').checked = data.relay1Level;\n");
  message +=         F("document.getElementById('relay2Level').checked = data.relay2Level;\n");
  message +=         F("document.getElementById('relay3Level').checked = data.relay3Level;\n");
  message +=         F("if (data.beepeep > 0) {document.location.href = \"/alert\"}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshSens, 1000);\n");
  message += refreshTempMessage("select");
  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Управление контролем</h3>");
  //message += "<br>";
  message += F("&nbsp;<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Активация реле высоким уровнем</b></legend>");
  message += F("<br>");
  message += F("<input type=\"checkbox\" name=\"relay1Level\" class=\"checkbox\" id=\"relay1Level\" onchange=\"openUrl('/switch?relay1Level=' + this.checked);\" ");
  if (relay1Level == 1) message += F("checked ");
  message += F("/><label for=\"relay1Level\">Нагрев</label><p>");

  message += F("<input type=\"checkbox\" name=\"relay2Level\" class=\"checkbox\" id=\"relay2Level\" onchange=\"openUrl('/switch?relay2Level=' + this.checked);\" ");
  if (relay2Level == 1) message += F("checked ");
  message += F("/><label for=\"relay2Level\">Мешалка</label><p>");

  message += F("<input type=\"checkbox\" name=\"relay3Level\" class=\"checkbox\" id=\"relay3Level\" onchange=\"openUrl('/switch?relay3Level=' + this.checked);\" ");
  if (relay3Level == 1) message += F("checked ");
  message += F("/><label for=\"relay3Level\">Отбор</label>");
  message += F("</fieldset>");

  message += F("&nbsp;<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Активация датчиков</b></legend>");
  message += F("<br>");

  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<input type=\"checkbox\" name=\"t"); message += String(i); message += F("\" class=\"checkbox\" id=\"t"); message += String(i);
      message += F("\" onchange=\"openUrl('/switch?SenseStatus"); message += String(i); message += F("=' + this.checked);\" ");
      if (t[i] == 1) message += F("checked ");
      message += F("/><label for=\"t"); message += String(i); message += F("\">Датчик "); message += String(i); message += F(" </label>");
      message += F("<input type=\"text\" name=\"tNameSens"); message += String(i); message += F("\" id=\"tNameSens"); message += String(i) + (" maxlength=\"30\" value=\"");
      message += tNameSens[i]; message += F("\" />");

      message += F("<p>");
    }
  }
  message += F("</fieldset>");

  message += F("&nbsp;<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Настройка датчиков</b></legend>");
  
  message += F("<input name = \"error_read_ds_Max\" id=\"error_read_ds_Max\" type=\"text\" value=\"");
  message += String(error_read_ds_Max) + F("\" class=\"textStyle2\" title=\"Разрешенное количество ошибок (подряд) при опросе датчиков температуры\" maxlength=\"2\"");
  message += F("/> Кол.ошибок (подряд) при опросе<br />");

  message += F("<input name=\"t_msec_get_ds\" id=\"t_msec_get_ds\" type=\"text\" value=\"");
  message += String(t_msec_get_ds) + F("\" class=\"textStyle2\" title=\"Интервал опроса датчиков,мСек\" maxlength=\"5\""); message += F("/> Интервал опроса,мСек<br />");

  message += F("<input name=\"Zaderj\" id=\"Zaderj\" type=\"text\" value=\"");
  message += String(Zaderj) + F("\" class=\"textStyle2\" title=\"задержка опроса датчиков,мСек\" maxlength=\"5\""); message += F("/> Задержка опроса,мСек<br />");

  message += F("<input name=\"jamp_t\" id=\"jamp_t\" type=\"text\" value=\"");
  message += String(jamp_t) + F("\" class=\"textStyle2\" title=\"Максимальная значение изменния температуры за опрос\" maxlength=\"2\""); message += F("/> Макс.скор.измен темп.,С/опрос<br />");

  message += F("</fieldset>");

  message += F("<p>");
  if ((error_read_ds > 0) || (error_read_ds_all > 0)) {
    message += F("Ошибок при чтении t (всего): "); message += String(error_read_ds_all) + F("<br />");
  }
  if (error_read_correct_ds_all > 0) {
    message += F("Корректность чтения t (всего): "); message += String(error_read_correct_ds_all) + F("<br />");
  }
  message += F("<input type=\"button\" id=\"butt_search_sense\" value=\"Поиск\" onclick=\"openUrl('/switch?Srch=' + '1'); location.href='/selectProm'; \" >\n");

  //openUrl('/switch?SaveSense=1');
  //message += F("<input type=\"button\" id=\"butt_search_sense\" value=\"Сохр датчики\" onclick=\"openUrl('/switch?SaveSense=1');\" >\n");
  message += F("<br />");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\"><input type=\"submit\" value=\"Сохранить\" />");

  message += F("</form>");
  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//-------------------------------------------------------------------------------
void h_selectProm()//selectProm
{
  LoginContr();

  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /select\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Поиск датчиков выполнен.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/select\">сюда</a> для перехода в настройку сообщений.");
  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------
void h_data_mainPage()//data_mainPage
{
  LoginContr();
  String message;
  message += F("{");
  message += F("\"relay1\":");
  if (Prg_swt1) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay2\":");
  if (Prg_swt2) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay3\":");
  if (Prg_swt3) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay1Level\":");
  if (relay1Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay2Level\":");
  if (relay2Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay3Level\":");
  if (relay3Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"strtworkwarm\":\""); message += String(strtworkwarm) + F("\",");
  message += F("\"power_ten\":\""); message += String(power_ten) + F("\",");
  message += F("\"strtworkmix\":\""); message += String(strtworkmix) + F("\",");
  message += F("\"strtworkotb\":\""); message += String(strtworkotb) + F("\",");

  for (byte i = 0; i <= NSenseFact; i++) {
    if (t[i] == 1) {//датчик активен (0-не использ,1-активен,2-используется но не активен)
      message += F("\"tempC"); message += String(i); message += F("\":"); message += tempC[i]; message += F(",");
    }
  }
  message += F("\"beepeep\":"); message += erSt;

  message += F(",");
  message += F("\"timeStr\":\""); message += String(timeStr) + F("\"");
  message += F(",");
  message += F("\"TimeOn\":\""); message += String(TimeOn) + F("\"");
  message += F("}");

  server.send(200, F("text/html"), message);
}
//
void handleGetTimer() {

  LoginContr();
  int8_t R_hour, R_min, R_sec, R_day, R_month;
  uint8_t R_wd;
  int16_t R_year;

  parseUnixTime(startTime, R_hour, R_min, R_sec, R_wd, R_day, R_month, R_year);
  server.send(200, F("text/html"), "ok");
}
//-------------------------------------
void handleSetTimer() {
  LoginContr();

  int8_t R_hour, R_min, R_sec, R_day, R_month;
  uint8_t R_wd;
  int16_t R_year;
  String message;

  parseUnixTime(now_timeUnx, R_hour, R_min, R_sec, R_wd, R_day, R_month, R_year);

  message += F("{");
  message += F("\"R_hour\":"); message += String(R_hour) + F(",");
  message += F("\"R_min\":"); message += String(R_min) + F(",");
  message += F("\"R_sec\":"); message += String(R_sec) + F(",");

  message += F("\"R_day\":"); message += String(R_day) + F(",");
  message += F("\"R_month\":"); message += String(R_month) + F(",");
  message += F("\"R_year\":"); message += String(R_year);
  message += F("}");

  server.send(200, F("text/html"), message);
}

