//---------------------------------------------------------------------------------------------
void h_mixer()//mixer
{
  LoginContr();
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Режим работы миксера</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".style1 {");
  message += F("border-style: solid;");
  message += F("border-width: 1px;");
  message += F("text-align: center;");
  message += F("}");
  message += textStyle();


  message += F("</style>");
  message += F("<script type=\"text/javascript\">");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
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
  message += refreshTempMessage("mixer");

  message += F("function filStTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerMixDaySt').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerMixMonthSt').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerMixYearSt').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerMixHourSt').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerMixMinSt').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerMixSecSt').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");

  message += F("function filEndTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerMixDayEnd').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerMixMonthEnd').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerMixYearEnd').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerMixHourEnd').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerMixMinEnd').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerMixSecEnd').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");


  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Режим работы миксера</h3><p>");

  message += F("ЧЧ : ММ : СС ");
  message += F("<br>");
  message += F("<input name=\"MixOnHour\" type=\"text\" value=\""); message += String(MixOnHour) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"MixOnMin\" type=\"text\" value=\""); message += String(MixOnMin) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"MixOnSec\" type=\"text\" value=\""); message += String(MixOnSec) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("Работа");
  message += F("<br>");
  message += F("<input name=\"MixOffHour\" type=\"text\" value=\""); message += String(MixOffHour) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"MixOffMin\" type=\"text\" value=\""); message += String(MixOffMin) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"MixOffSec\" type=\"text\" value=\""); message += String(MixOffSec) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("Простой");
  message += F("<br>");
  /*message += F("<input name=\"MixHour\" type=\"text\" value=\""); message += String(MixHour) + F("\" class=\"textStyle1\" />");
    message += F("<input name=\"MixMin\" type=\"text\" value=\""); message += String(MixMin) + F("\" class=\"textStyle1\" />");
    message += F("<input name=\"MixSec\" type=\"text\" value=\""); message += String(MixSec) + F("\" class=\"textStyle1\" />");*/

  message += F("<p>");

  /*message += F("Время работы");
    message += F("<input id=\"MixHour\" name=\"MixHour\" type=\"text\" value=\"");
    message += String(MixHour) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('MixHour')\">");
    message += F("<input id=\"MixMin\" name=\"MixMin\" type=\"text\" value=\"");
    message += String(MixMin) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('MixMin')\">");
    message += F("<input id=\"MixSec\" name=\"MixSec\" type=\"text\" value=\"");
    message += String(MixSec) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('MixSec')\">ЧЧ:ММ:СС<br />");
    message += F("<br />");*/


  message += F("Остановка при достижении");
  message += F("<br />");
  message += F("<input type=\"button\" value=\"-\" onclick=\"document.getElementById('TMixContr').value=PowChange(document.getElementById('TMixContr').value,-1)\" />");
  message += F("<input id=\"TMixContr\" name=\"TMixContr\" type=\"text\" maxlength=\"6\" value=\"");
  message += String(TMixContr) + F("\" onchange=\"CheckVal('TMixContr')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input type=\"button\" value=\"+\" onclick=\"document.getElementById('TMixContr').value=PowChange(document.getElementById('TMixContr').value,1)\" /> Температура,С");
  message += F("<br />");

  message += F("<select name=\"NsenseMixContr\" title=\"Использовать датчик \">");

  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<option value="); message += String(i);
      if (NsenseMixContr == i) message += F(" selected ");
      if (tNameSens[i].length() > 0) {
        message += F("> "); message += tNameSens[i] + F("</option>");
      }
      else {
        message += F(">Датчик "); message += String(i) + F("</option>");
      }
    }
  }

  message += F("</select>");
  message += F(" для контроля за нагревом<p>");

  message += F("<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Таймеры</b></legend>");
  message += F("Перерывы в работе миксера (ЧЧ:ММ):<br>");
  for (byte i = 0; i < NomPrerMixAll; i++) {

    message += F("<input type=\"checkbox\" id=\"PrerMixAvail"); message += String(i); message += F("\" onchange=\"openUrl('/switch?PrerMixAvail"); message += String(i); message += F("=' + this.checked);\" ");
    if (PrerMix[i].Avail == HIGH) message += F("checked");
    message += F("/><label for=\"PrerMixAvail"); message += String(i) + F("\">Исп.</label>");

    message += F(" Нач.");

    message += F("<input name=\"PrerMixHourSt"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerMix[i].PrerMixHourSt) + F("\" class=\"textStyle1\" title=\"час начала паузы\" maxlength=\"2\"/>");

    /*message += F("<select name=\"PrerMixHourSt"); message += String(i) + F("\" title=\"час начала паузы\" onchange=\"openUrl('/switch?PrerMixHourSt"); message += String(i) + F("=' + this.value);\" >");
      for (byte k = 0; k < 24; k++) {
      message += F("<option value="); message += String(k); //message += F("\"");
      if (PrerMix[i].PrerMixHourSt == k) message += F(" selected ");
      message += F(">"); message += AddNull(String(k)) + F("</option>");
      }
      message += F("</select>");*/

    message += F("<input name=\"PrerMixMinSt"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerMix[i].PrerMixMinSt) + F("\" class=\"textStyle1\" title=\"минута начала паузы\" maxlength=\"2\"/>");
    /*message += F("<select name=\"PrerMixMinSt"); message += String(i) + F("\" title=\"минута начала паузы\" onchange=\"openUrl('/switch?PrerMixMinSt"); message += String(i) + F("=' + this.value);\" >");
      for (byte k = 0; k < 60; k++) {
      message += F("<option value="); message += String(k); //message += F("\"");
      if (PrerMix[i].PrerMixMinSt == k) message += F(" selected ");
      message += F(">"); message += AddNull(String(k)) + F("</option>");
      }
      message += F("</select>");*/

    message += F(" Кон.");
    message += F("<input name=\"PrerMixHourEnd"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerMix[i].PrerMixHourEnd) + F("\" class=\"textStyle1\" title=\"час завершения паузы\" maxlength=\"2\"/>");
    /*message += F("<select name=\"PrerMixHourEnd"); message += String(i) + F("\" title=\"час завершения паузы\" onchange=\"openUrl('/switch?PrerMixHourEnd"); message += String(i) + F("=' + this.value);\" >");
      for (byte k = 0; k < 24; k++) {
      message += F("<option value="); message += String(k); //message += F("\"");
      if (PrerMix[i].PrerMixHourEnd == k) message += F(" selected ");
      message += F(">"); message += AddNull(String(k)) + F("</option>");
      }
      message += F("</select>");*/

    message += F("<input name=\"PrerMixMinEnd"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerMix[i].PrerMixMinEnd) + F("\" class=\"textStyle1\" title=\"минута завершения паузы\" maxlength=\"2\"/>");
    /*message += F("<select name=\"PrerMixMinEnd"); message += String(i) + F("\" title=\"минута завершения паузы\" onchange=\"openUrl('/switch?PrerMixMinEnd"); message += String(i) + F("=' + this.value);\" >");
      for (byte k = 0; k < 60; k++) {
      message += F("<option value="); message += String(k); //message += F("\"");
      if (PrerMix[i].PrerMixMinEnd == k) message += F(" selected ");
      message += F(">"); message += AddNull(String(k)) + F("</option>");
      }
      message += F("</select>");*/
    message += F("<br>");
  }
  message += F("<br>");

  //------------
  message += F(" Запуск в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerMixAvailSt\" onchange=\"openUrl('/switch?TimerMixAvailSt=' + this.checked);\" ");
  if (TimerMixAvailSt == HIGH) message += F("checked");
  message += F("/><label for=\"TimerMixAvailSt\">Исп.</label>");

  message += F("<input name=\"TimerMixDaySt\" id=\"TimerMixDaySt\" type=\"text\" value=\""); message += String(TimerMixDaySt) + F("\" class=\"textStyle1\" title=\"день запуска\" maxlength=\"2\"/>");
  /*  message += F("<select name=\"TimerMixDaySt\" title=\"день запуска\" onchange=\"openUrl('/switch?TimerMixDaySt=' + this.value);\" >");
    for (byte k = 0; k < 32; k++) {
      message += F("<option value="); message += String(k); //message += F("\"");
      if (TimerMixDaySt == k) message += F(" selected ");
      message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F("<input name=\"TimerMixMonthSt\" id=\"TimerMixMonthSt\" type=\"text\" value=\""); message += String(TimerMixMonthSt) + F("\" class=\"textStyle1\" title=\"месяц запуска\" maxlength=\"2\"/>");
  /*  message += F("<select name=\"TimerMixMonthSt\" title=\"месяц запуска\" onchange=\"openUrl('/switch?TimerMixMonthSt=' + this.value);\" >");
    for (byte k = 0; k < 13; k++) {
      message += F("<option value="); message += String(k); //message += F("\"");
      if (TimerMixMonthSt == k) message += F(" selected ");
      message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/
  message += F("<input name=\"TimerMixYearSt\" id=\"TimerMixYearSt\" type=\"text\" value=\""); message += String(TimerMixYearSt) + F("\" class=\"textStyle2\" title=\"год запуска\" maxlength=\"4\"/>");
  /*message += F("<select name=\"TimerMixYearSt\" title=\"год запуска\" onchange=\"openUrl('/switch?TimerMixYearSt=' + this.value);\" >");
    for (uint16_t k = 2018; k < 2040; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixYearSt == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F(" : ");

  message += F("<input name=\"TimerMixHourSt\" id=\"TimerMixHourSt\" type=\"text\" value=\""); message += String(TimerMixHourSt) + F("\" class=\"textStyle1\" title=\"час запуска\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixHourSt\" title=\"час запуска\" onchange=\"openUrl('/switch?TimerMixHourSt=' + this.value);\" >");
    for (byte k = 0; k < 24; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixHourSt == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/
  message += F("<input name=\"TimerMixMinSt\" id=\"TimerMixMinSt\" type=\"text\" value=\""); message += String(TimerMixMinSt) + F("\" class=\"textStyle1\" title=\"минута запуска\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixMinSt\" title=\"минута запуска\" onchange=\"openUrl('/switch?TimerMixMinSt=' + this.value);\" >");
    for (byte k = 0; k < 60; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixMinSt == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F("<input name=\"TimerMixSecSt\" id=\"TimerMixSecSt\" type=\"text\" value=\""); message += String(TimerMixSecSt) + F("\" class=\"textStyle1\" title=\"секунда запуска\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixSecSt\" title=\"секунда запуска\" onchange=\"openUrl('/switch?TimerMixSecSt=' + this.value);\" >");
    for (byte k = 0; k < 60; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixSecSt == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/
  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filStTimer();\" title=\"Заполнить поля текущими датой и временем\">");

  message += F("<br>");

  //------------
  message += F(" Остан. в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerMixAvailEnd\" onchange=\"openUrl('/switch?TimerMixAvailEnd=' + this.checked);\" ");
  if (TimerMixAvailEnd == HIGH) message += F("checked");
  message += F("/><label for=\"TimerMixAvailEnd\">Исп.</label>");

  message += F("<input name=\"TimerMixDayEnd\" id=\"TimerMixDayEnd\" type=\"text\" value=\""); message += String(TimerMixDayEnd) + F("\" class=\"textStyle1\" title=\"день останова\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixDayEnd\" title=\"день останова\" onchange=\"openUrl('/switch?TimerMixDayEnd=' + this.value);\" >");
    for (byte k = 0; k < 32; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixDayEnd == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F("<input name=\"TimerMixMonthEnd\" id=\"TimerMixMonthEnd\" type=\"text\" value=\""); message += String(TimerMixMonthEnd) + F("\" class=\"textStyle1\" title=\"месяц останова\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixMonthEnd\" title=\"месяц останова\" onchange=\"openUrl('/switch?TimerMixMonthEnd=' + this.value);\" >");
    for (byte k = 0; k < 13; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixMonthEnd == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F("<input name=\"TimerMixYearEnd\" id=\"TimerMixYearEnd\" type=\"text\" value=\""); message += String(TimerMixYearEnd) + F("\" class=\"textStyle2\" title=\"год останова\" maxlength=\"4\"/>");
  /*message += F("<select name=\"TimerMixYearEnd\" title=\"год останова\" onchange=\"openUrl('/switch?TimerMixYearEnd=' + this.value);\" >");
    for (uint16_t k = 2018; k < 2040; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixYearEnd == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F(" : ");
  message += F("<input name=\"TimerMixHourEnd\" id=\"TimerMixHourEnd\" type=\"text\" value=\""); message += String(TimerMixHourEnd) + F("\" class=\"textStyle1\" title=\"час останова\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixHourEnd\" title=\"час останова\" onchange=\"openUrl('/switch?TimerMixHourEnd=' + this.value);\" >");
    for (byte k = 0; k < 24; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixHourEnd == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F("<input name=\"TimerMixMinEnd\" id=\"TimerMixMinEnd\" type=\"text\" value=\""); message += String(TimerMixMinEnd) + F("\" class=\"textStyle1\" title=\"минута останова\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixMinEnd\" title=\"минута останова\" onchange=\"openUrl('/switch?TimerMixMinEnd=' + this.value);\" >");
    for (byte k = 0; k < 60; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixMinEnd == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/

  message += F("<input name=\"TimerMixSecEnd\" id=\"TimerMixSecEnd\" type=\"text\" value=\""); message += String(TimerMixSecEnd) + F("\" class=\"textStyle1\" title=\"секунда останова\" maxlength=\"2\"/>");
  /*message += F("<select name=\"TimerMixSecEnd\" title=\"секунда останова\" onchange=\"openUrl('/switch?TimerMixSecEnd=' + this.value);\" >");
    for (byte k = 0; k < 60; k++) {
    message += F("<option value="); message += String(k); //message += F("\"");
    if (TimerMixSecEnd == k) message += F(" selected ");
    message += F(">"); message += AddNull(String(k)) + F("</option>");
    }
    message += F("</select>");*/
  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filEndTimer();\" title=\"Заполнить поля текущими датой и временем\">");
  message += F("</fieldset>");
  message += F("<br>");





  message += F("<p>");
  message += F("<input type=\"button\" value=\"Назад\"  onclick=\"location.href='/'\"><input type=\"submit\" value=\"Сохранить\" />");
  message += F("</form>");
  message += F("</body>");
  message += F("</html>");

  server.send(200, "text/html", message);
}
//--------------------------------------------------------------------
void ManageRele(boolean StRele)
{
  if (Prg_swt2 == true)
  {
    if (relay2Level == 0) StRele = !StRele;
    MydigitalWrite(swt2_pin, StRele);
  }
  else
  {
    if (relay2Level == 1)
      MydigitalWrite(swt2_pin, LOW);
    else
      MydigitalWrite(swt2_pin, HIGH);
  }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void working_Mix()
{
  unsigned int t_prom;
  bool StatusMix, now_StatusMix;

  TMixContr_now = -128;
  for (byte i = 0; i < NSenseFact; i++) {
    if (Prg_NsenseMixContr == i) TMixContr_now = tempC[i];
  }
  t_prom = millis() / 1000; //текущее время

  if (Prg_swt2 == true)
  {
    if (prev_swt2 != Prg_swt2)
    {
      mqttClient.publish(String(mqttClientId + "/swt/2").c_str(), String(Prg_swt2).c_str(), true);
      prev_swt2 = Prg_swt2;
      if (Prg == true)
      {
        if (Prog[NumStrPrg].statErr == 0)
        {
          t_mix = t_prom;
          t_pow_on = 0;
          t_pow_off = 0;
          Serial.println("  swt2 true = " + String(Prg_swt2));
        }
      }
      else
      {
        t_mix = t_prom;
        t_pow_on = 0;
        t_pow_off = 0;
        Serial.println("  swt2 true = " + String(Prg_swt2));
      }
    }
  }
  else
  {
    if (prev_swt2 != Prg_swt2)
    {
      Serial.println("  swt2 false = " + String(Prg_swt2));
      prev_swt2 = Prg_swt2;
      mqttClient.publish(String(mqttClientId + "/swt/2").c_str(), String(Prg_swt2).c_str(), true);
    }
  }

  if (Prg_swt2 == true)
  {
    t_work_mix = t_prom - t_mix;

    if ((t_work_mix >= Prg_MixTime) && (Prg_MixTime != 0))
    { //отключение по таймеру
      Prg_swt2 = false; prev_swt2 = LOW; StatusMix = LOW;
      if (Prg == true) {
        Prog[NumStrPrg].MCompl = 2; //шаг по миксеру исполнен
      }
    }


    if ((Prg_TMixContr != 0) && (Prg_NsenseMixContr != 0))
    { //если температура контроля и датчик выбраны
      if (TMixContr_now == -127)
      { //датчик не зашарился
        Prg_swt2 = LOW; prev_swt2 = LOW;
        StatusMix = LOW;
        Serial.println(F("module working_Mix: mix sensor err"));
        erSt = 1;
        if (Prg == true) {
          Prog[NumStrPrg].statErr = 1; //статус ошибки
        }
        else {

        }
      }
    }
    if (Prg_MixWorkTime != 0) {//если установлено время "Миксер включен"
      if ((t_pow_on == 0) && (t_pow_off == 0)) t_pow_on = t_prom;
      if (((t_prom - t_pow_on) < Prg_MixWorkTime) && (t_pow_off == 0)) StatusMix = HIGH;
      if (((t_prom - t_pow_on) >= Prg_MixWorkTime) && (t_pow_off == 0))
      {
        t_pow_on = 0;
        if (Prg_MixStopTime != 0) t_pow_off = t_prom;
        else
        {
          Prg_swt2 = LOW; prev_swt2 = LOW; StatusMix = LOW;
          if (Prg == true) {
            Prog[NumStrPrg].MCompl = 2; //шаг по миксеру исполнен
          }
        }
      }
      if (Prg_MixStopTime != 0) { //если установлено время "Миксер выключен"
        if (((t_prom - t_pow_off) < Prg_MixStopTime) && (t_pow_on == 0)) StatusMix = LOW;
        if (((t_prom - t_pow_off) >= Prg_MixStopTime) && (t_pow_on == 0)) {
          t_pow_on = t_prom;
          t_pow_off = 0;
        }
      }
    }
    else {//иначе просто включен
      StatusMix = HIGH;
    }

    if ((TMixContr_now >= Prg_TMixContr) && (Prg_TMixContr != 0))
    { //останов по превышению разреш температуры обычно до 55 чтоб не было пены
      StatusMix = LOW;
      Serial.println(F("module working_Mix: mix stop, overwarm"));
    }

    // управление таймерами/перерывами
    now_StatusMix = HIGH;
    if (now_year > 1970) {
      //считаем время установлено
      parseUnixTime(now_timeUnx, now_hour, now_min, now_sec, now_wd, now_day, now_month, now_year);
      for (byte i = 0; i < NomPrerMixAll; i++) {
        //перебираем все интервалы
        if ((PrerMix[i].PrerMixStUnx < PrerMix[i].PrerMixEndUnx) && (PrerMix[i].Avail == 1))
        { //проверяем интервал, время начала должно быть меньше времени окончания и интервал активен
          //получаем юникс время тек.интервала
          PrerMix[i].PrerMixStUnx = combineUnixTime(PrerMix[i].PrerMixHourSt, PrerMix[i].PrerMixMinSt, 0, now_day, now_month, now_year); // Собрать время в формат UNIX-time
          PrerMix[i].PrerMixEndUnx = combineUnixTime(PrerMix[i].PrerMixHourEnd, PrerMix[i].PrerMixMinEnd, 0, now_day, now_month, now_year); // Собрать время в формат UNIX-time

          if ((now_timeUnx > PrerMix[i].PrerMixStUnx) && (now_timeUnx < PrerMix[i].PrerMixEndUnx)) {
            //время попадает в выбранный интервал - миксер отключаем, ставим статус
            now_StatusMix = now_StatusMix & LOW;
          }
        }
      }

      if ((TimerMixStUnx > 0) && (TimerMixAvailSt == 1)) { //время отсроченного старта установлено
        if (now_timeUnx > TimerMixStUnx) {//сейчас время больше чем время вкл, значит включаем
          now_StatusMix = now_StatusMix & HIGH;
        } else { //выключаем
          now_StatusMix = now_StatusMix & LOW;
        }
      }
      if ((TimerMixEndUnx > 0) && (TimerMixAvailEnd == 1)) { //время отсроченного выключения установлено
        if (now_timeUnx > TimerMixEndUnx) {//сейчас время больше чем время откл, значит выключаем
          now_StatusMix = now_StatusMix & LOW;
        } else { //включаем
          now_StatusMix = now_StatusMix & HIGH;
        }
      }
    }
  }
  else {//если движок миксер выключен
    StatusMix = LOW;
  }
  StatusMix = StatusMix & now_StatusMix;
  ManageRele(StatusMix);
}
//------------------------------------------------------------------------------------------------------------------


