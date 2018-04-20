void h_warm()
{
  LoginContr();
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Управление ТЭНом</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".pidfild {width: 35px; text-align: center;}");
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
  message += refreshTempMessage("warm");
  
  message += F("function filStTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerWarmDaySt').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerWarmMonthSt').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerWarmYearSt').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerWarmHourSt').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerWarmMinSt').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerWarmSecSt').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");

  message += F("function filEndTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerWarmDayEnd').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerWarmMonthEnd').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerWarmYearEnd').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerWarmHourEnd').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerWarmMinEnd').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerWarmSecEnd').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");

  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Управление нагревом</h3><p>");
  message += F("<input id=\"ButPowMinus\" type=\"button\" value=\"-\" onclick=\"document.getElementById('WarmVol').value=PowChange(document.getElementById('WarmVol').value,-1)\" />");
  message += F("<input id=\"WarmVol\" name=\"WarmVol\" type=\"text\" maxlength=\"6\" value=\"");
  message += String(WarmVol) + F("\" onchange=\"CheckVal('WarmVol')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input id=\"ButPowPlust\" type=\"button\" value=\"+\" onclick=\"document.getElementById('WarmVol').value=PowChange(document.getElementById('WarmVol').value,1)\" /> Мощность,%");
  message += F("<br />");
  message += F("<input id=\"ButTkMinus\" type=\"button\" value=\"-\" onclick=\"document.getElementById('TkVol').value=PowChange(document.getElementById('TkVol').value,-1)\" />");
  message += F("<input id=\"TkVol\" name=\"TkVol\" type=\"text\" maxlength=\"5\" value=\"");
  message += String(TkVol) + F("\" onchange=\"CheckVal('TkVol')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input id=\"ButTkPlust\" type=\"button\" value=\"+\" onclick=\"document.getElementById('TkVol').value=PowChange(document.getElementById('TkVol').value,1)\" /> Температура,С<br />");
  message += F("<br />");
  
  message += F("<fieldset style=\"width: 304px\">");
  //message += F("&nbsp;<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Вариант управления ТЭНом</b></legend>");
  message += F("<input name=\"ModeWarm\" type=\"radio\"");
  if ((ModeWarm == 0) || (ModeWarm == 1))
  {
    ModeWarm = 1;
    message += F(" checked=\"checked\"");
  }
  message += F("id=\"hold\" value=\"1\"/><label for=\"hold\">Удержание температуры</label>");
  message += F("<br />");
  message += F("<input name=\"ModeWarm\" type=\"radio\"");
  if (ModeWarm == 2)
  {
    message += F(" checked=\"checked\"");
  }
  message += F("id=\"reach\" value=\"2\"/><label for=\"reach\">Достижение температуры</label>");
  message += F("<br />");

  message += F("<input name=\"ModeWarm\" type=\"radio\"");
  if (ModeWarm == 3)
  {
    message += F(" checked=\"checked\"");
  }
  message += F("id=\"manual\" value=\"3\"/><label for=\"manual\">Ручное управление мощностью</label>");
  message += F("<br />");

  message += F("<input name=\"ModeWarm\" type=\"radio\"");
  if (ModeWarm == 4)
  {
    message += F(" checked=\"checked\"");
  }
  message += F("id=\"manual\" value=\"4\"/><label for=\"manual\">Удержание температуры (ПИД)</label>");
  message += F("<br />");
  message += F("Коэффициенты (пост.) Kp/Ki/Kd<br/>");
  message += F("<input name=\"consKp\" type=\"text\" class=\"pidfild\" value=\""); message += String(consKp) + F("\" maxlength=\"6\" />");
  message += F("<input name=\"consKi\" type=\"text\" class=\"pidfild\" value=\""); message += String(consKi) + F("\" maxlength=\"6\" />");
  message += F("<input name=\"consKd\" type=\"text\" class=\"pidfild\" value=\""); message += String(consKd) + F("\" maxlength=\"6\" />");
  message += F("<br/>");
  message += F("Коэффициенты (агр.) Kp/Ki/Kd<br/>");
  message += F("<input name=\"aggKp\" type=\"text\" class=\"pidfild\" value=\""); message += String(aggKp) + F("\" maxlength=\"6\" />");
  message += F("<input name=\"aggKi\" type=\"text\" class=\"pidfild\" value=\""); message += String(aggKi) + F("\" maxlength=\"6\" />");
  message += F("<input name=\"aggKd\" type=\"text\" class=\"pidfild\" value=\""); message += String(aggKd) + F("\" maxlength=\"6\" />");

  message += F("<br/>");
  message += F("<input name=\"gap\" type=\"text\" class=\"pidfild\" value=\""); message += String(gap) + F("\" maxlength=\"4\" />"); message += F("Дельта,С");
  message += F("<p>");


  message += F("<input id=\"TSec\" name=\"TSec\" type=\"text\" value=\"");
  message += String(TSec) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('TSec')\">период, с");
  message += F("<br />");


  message += F("<input id=\"WarmHour\" name=\"WarmHour\" type=\"text\" value=\"");
  message += String(WarmHour) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('WarmHour')\">");
  message += F("<input id=\"WarmMin\" name=\"WarmMin\" type=\"text\" value=\"");
  message += String(WarmMin) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('WarmMin')\">");
  message += F("<input id=\"WarmSec\" name=\"WarmSec\" type=\"text\" value=\"");
  message += String(WarmSec) + F("\" style=\"width: 25px; text-align: center;\" onchange=\"CheckVal('WarmSec')\">ЧЧ:ММ:СС");
  message += F("</fieldset>");
  message += "<br>";

  message += F("<select name=\"Nsense\" title=\"Использовать датчик \">");
  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<option value="); message += String(i); //message += F("\"");
      if (Nsense == i) message += F(" selected ");

      if (tNameSens[i].length() > 0) {
        message += F("> "); message += tNameSens[i] + F("</option>");
      }
      else      {
        message += F(">Датчик "); message += String(i) + F("</option>");
      }

    }
  }
  message += F("</select> Датчик (управление нагревом)<br>");


  //message += "<br />";
  message += F("<p>");
  message += F("Аварийный контроль нагрева");
  message += F("<br />");
  message += F("<input type=\"button\" value=\"-\" onclick=\"document.getElementById('TWarmContr').value=PowChange(document.getElementById('TWarmContr').value,-1)\" />");
  message += F("<input id=\"TWarmContr\" name=\"TWarmContr\" type=\"text\" maxlength=\"6\" value=\"");
  message += String(TWarmContr) + F("\" onchange=\"CheckVal('TWarmContr')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input type=\"button\" value=\"+\" onclick=\"document.getElementById('TWarmContr').value=PowChange(document.getElementById('TWarmContr').value,1)\" /> Останов нагрева,С");
  message += F("<br />");


  message += F("<select name=\"NsenseWarmContr\" title=\"Использовать датчик \">");
  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<option value="); message += String(i);
      if (NsenseWarmContr == i) message += F(" selected ");
      if (tNameSens[i].length() > 0) {
        message += F("> "); message += tNameSens[i] + F("</option>");
      }
      else {
        message += F(">Датчик "); message += String(i) + F("</option>");
      }
    }
  }
  message += F("</select>Датчик (контроля за нагревом)<br>");

  //--таймеры
  //------------
  message += F("<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Таймеры</b></legend>");
  message += F(" Запуск в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerWarmAvailSt\" onchange=\"openUrl('/switch?TimerWarmAvailSt=' + this.checked);\" ");
  if (TimerWarmAvailSt == HIGH) message += F("checked");
  message += F("/><label for=\"TimerWarmAvailSt\">Исп.</label>");

  message += F("<input name=\"TimerWarmDaySt\" id=\"TimerWarmDaySt\" type=\"text\" value=\""); message += String(TimerWarmDaySt) + F("\" class=\"textStyle1\" title=\"день запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmMonthSt\" id=\"TimerWarmMonthSt\" type=\"text\" value=\""); message += String(TimerWarmMonthSt) + F("\" class=\"textStyle1\" title=\"месяц запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmYearSt\" id=\"TimerWarmYearSt\" type=\"text\" value=\""); message += String(TimerWarmYearSt) + F("\" class=\"textStyle2\" title=\"год запуска\" maxlength=\"4\"/>");
  message += F(" : ");
  message += F("<input name=\"TimerWarmHourSt\" id=\"TimerWarmHourSt\" type=\"text\" value=\""); message += String(TimerWarmHourSt) + F("\" class=\"textStyle1\" title=\"час запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmMinSt\" id=\"TimerWarmMinSt\" type=\"text\" value=\""); message += String(TimerWarmMinSt) + F("\" class=\"textStyle1\" title=\"минута запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmSecSt\" id=\"TimerWarmSecSt\" type=\"text\" value=\""); message += String(TimerWarmSecSt) + F("\" class=\"textStyle1\" title=\"секунда запуска\" maxlength=\"2\"/>");

  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filStTimer();\" title=\"Заполнить поля текущими датой и временем\">");

  message += F("<br>");
  //------------
  message += F(" Остан. в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerWarmAvailEnd\" onchange=\"openUrl('/switch?TimerWarmAvailEnd=' + this.checked);\" ");
  if (TimerWarmAvailEnd == HIGH) message += F("checked");
  message += F("/><label for=\"TimerWarmAvailEnd\">Исп.</label>");

  message += F("<input name=\"TimerWarmDayEnd\" id=\"TimerWarmDayEnd\" type=\"text\" value=\""); message += String(TimerWarmDayEnd) + F("\" class=\"textStyle1\" title=\"день останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmMonthEnd\" id=\"TimerWarmMonthEnd\" type=\"text\" value=\""); message += String(TimerWarmMonthEnd) + F("\" class=\"textStyle1\" title=\"месяц останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmYearEnd\" id=\"TimerWarmYearEnd\" type=\"text\" value=\""); message += String(TimerWarmYearEnd) + F("\" class=\"textStyle2\" title=\"год останова\" maxlength=\"4\"/>");
  message += F(" : ");
  message += F("<input name=\"TimerWarmHourEnd\" id=\"TimerWarmHourEnd\" type=\"text\" value=\""); message += String(TimerWarmHourEnd) + F("\" class=\"textStyle1\" title=\"час останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmMinEnd\" id=\"TimerWarmMinEnd\" type=\"text\" value=\""); message += String(TimerWarmMinEnd) + F("\" class=\"textStyle1\" title=\"минута останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWarmSecEnd\" id=\"TimerWarmSecEnd\" type=\"text\" value=\""); message += String(TimerWarmSecEnd) + F("\" class=\"textStyle1\" title=\"секунда останова\" maxlength=\"2\"/>");
  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filEndTimer();\" title=\"Заполнить поля текущими датой и временем\">");

  message += F("</fieldset>");

  message += F("<p>");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\"><input type=\"submit\" value=\"Сохранить\" />");
  message += F("</form>");
  message += F("</body>");
  message += F("</html>");
  server.send(200, "text/html", message);
}

//--------------------------------------------------------------------------------------
void PowerManageDevicePWM()
{
  int PwmWorkTime, PwmStopTime, t_pwm_tek;
  bool StPwmWarm;
  //PwmStopTime + PwmWorkTime = TSec
  if (TSec == 0) TSec = 1;
  PwmWorkTime = power_ten * TSec * 10; //сколько работает
  PwmStopTime = (100 - power_ten) * TSec * 10; //сколько стоит

  t_pwm_tek = millis();  //текущее время
  if ((t_pwm_on == 0) && (t_pwm_off == 0)) t_pwm_on = t_pwm_tek;
  if (((t_pwm_tek - t_pwm_on) < PwmWorkTime) && (t_pwm_off == 0)) {
    StPwmWarm = HIGH;//Serial.print("StPwmWarm = ");Serial.println(StPwmWarm);
  }
  if (((t_pwm_tek - t_pwm_on) >= PwmWorkTime) && (t_pwm_off == 0)) {
    t_pwm_on = 0;
    t_pwm_off = t_pwm_tek;
  }
  if (((t_pwm_tek - t_pwm_off) < PwmStopTime) && (t_pwm_on == 0)) StPwmWarm  = LOW;
  if (((t_pwm_tek - t_pwm_off) >= PwmStopTime) && (t_pwm_on == 0)) {
    t_pwm_on = t_pwm_tek;
    t_pwm_off = 0;
  }

  if (PwmWorkTime == 0) StPwmWarm  = LOW;
  if (PwmStopTime == 0) StPwmWarm  = HIGH;

  if (Prg_swt1 == true) {
    if ((StatusWarm == HIGH) && (StPwmWarm == HIGH)) {
      if (relay1Level == 1) MydigitalWrite(swt1_pin, HIGH);
      if (relay1Level == 0) MydigitalWrite(swt1_pin, LOW);
      //Serial.println("StatusWarm " + String(HIGH));
    }
    else {
      if (relay1Level == 1) MydigitalWrite(swt1_pin, LOW);
      if (relay1Level == 0) MydigitalWrite(swt1_pin, HIGH);
      //Serial.println("StatusWarm "+String(LOW));
      //Serial.println(" off");
    }
  }
  else {
    if (relay1Level == 1) MydigitalWrite(swt1_pin, LOW);
    if (relay1Level == 0) MydigitalWrite(swt1_pin, HIGH);

  }
}
//--------------------------------------------------------------------------------------------------------------------------

void Adjust_Power_Ten(float T_now, float T)
{
  int tek_razn;
  tek_razn = T - T_now;
  if (ModeWarm != 4) {
    if (T_now < T)
    { //смотрим на сколько меньше
      if (tek_razn > 10) power_ten = 100;//100%мощности
      if ((tek_razn > 5) && (tek_razn <= 10))  power_ten = 80;
      if ((tek_razn > 2) && (tek_razn <= 05))  power_ten = 50;
      if ((tek_razn > 0) && (tek_razn <= 02))  power_ten = 30;

      if (tek_razn <= 10)
      {
        if (T < 50) power_ten = power_ten * 0.2;
        if ((T >= 50) && (T < 65)) power_ten = power_ten * 0.6;
        if ((T >= 65) && (T < 80)) power_ten = power_ten * 0.8;
        if ((T >= 80) && (T < 90)) power_ten = power_ten * 0.9;
        if ((T >= 90) && (T <= 100)) power_ten = power_ten * 1;
      }
      StatusWarm = HIGH; //ВКЛ нагрева
    }
  }
  else {
    Setpoint = T;
    Input = T_now;
    //float gap_tek = abs(Setpoint - Input);

    if ((abs(Setpoint - Input)) < gap)
    {
      myPID.SetTunings(consKp, consKi, consKd);
      //Serial.println("консерв");
    }
    else
    {
      myPID.SetTunings(aggKp, aggKi, aggKd);
      //Serial.println("--агресс-");
    }

    //Serial.println("abs(Setpoint - Input)=" + String(abs(Setpoint - Input)) + " gap=" +  String(gap));
    //Serial.println("consKp=" + String(myPID.GetKp()) + " consKi=" +  String(myPID.GetKi()) + " consKd=" + String(myPID.GetKd()));
    myPID.Compute();
    power_ten = Output;

    StatusWarm = HIGH; //ВКЛ нагрева
  }
}
//------------------------------------------------------
double read_correct(double tmpC, double tmpC_now, int number_sens)
{
  if (abs(tmpC - tmpC_now) > jamp_t) {
    if ((tmpC_now != -127) && (tmpC != -127)) {
      error_read_correct_ds[number_sens]++;
      error_read_correct_ds_all++;
      if (error_read_correct_ds[number_sens] > error_read_ds_Max)  {
        //на error_read_ds_Max раз принимаем как есть))
        error_read_correct_ds[number_sens] = 0;
        //Serial.println(" clear error_read_correct_ds ["+String(number_sens)+"]");
        return tmpC_now;
      }
    }
    else
    {
      return tmpC_now;
    }
  }
  else
  {
    error_read_correct_ds[number_sens] = 0;
    return tmpC_now;
  }
  return tmpC;
}

//-------------------------------------
void working_Warm()
{
  uint32_t tek_razn, t_prom;
  double Tk;
  bool now_StatusWarm;

  t_prom = millis() / 1000; //текущее время
  uint32_t t_control_now = millis();
  
  if (t_msec_get_ds==0) t_msec_get_ds=2000;
  if (error_read_ds_Max==0) error_read_ds_Max=5;
  if (jamp_t==0) jamp_t=10;
  if (Zaderj==0) Zaderj=10;
  

  if (((t_control_now - t_control ) >= t_msec_get_ds) || (t_control_now < t_msec_get_ds))
  { //выполняем замер
    //Serial.println("t_control_now = "+String(t_control_now));
    //Serial.println("t_control = "+String(t_control));

    if (Zaderj > 100) Zaderj = 1;
    if (Zaderj < 0) Zaderj = 0;
    delay(Zaderj);
    sensors.requestTemperatures();

    for (byte i = 0; i <= NSenseFact; i++) {
      delay(Zaderj);
      if (t[i] == 1) {//датчик активен (0-не использ,1-активен,2-используется но не активен)
        tempC_now[i] = sensors.getTempC(insideThermometer[i]);

        //проверяем показания
        if (tempC_now[i] == -127) { //датчик не зашарился
          error_read_ds[i]++; error_read_ds_all++;
          if (error_read_ds[i] == error_read_ds_Max) {
            //пишем что есть
            tempC[i] = tempC_now[i];
            error_read_ds[i] = 0;
          }
        }
        else {//датчик зашарился, проверяем показания
          error_read_ds[i] = 0;//обнуляем ошибки
          tempC[i] = read_correct(tempC[i], tempC_now[i], i) + tdelta[i];
        }

        if (Prg_Nsense == i) Tk_now = tempC[i];
        if (Prg_NsenseWarmContr == i) TWarmContr_now = tempC[i];

      }
    }
    t_control = t_control_now;
  }


  if (Prg_swt1 == true)
  { // кнопка нагрев
    if (prev_swt1 != Prg_swt1)
    {
      prev_swt1 = Prg_swt1;
      if (Prg == true)
      {
        if (Prog[NumStrPrg].statErr == 0)
        {
          t_warm = t_prom; //засекаем время вкл нагрева
          reachT = 0;
          t_work_warm_ModeWarm = 0;
          erSt = 0;
        }
        Prog[NumStrPrg].statErr = 0;
      }
      else
      {
        t_warm = t_prom; //засекаем время вкл нагрева
        reachT = 0;
        t_work_warm_ModeWarm = 0;
        erSt = 0;
      }

    }
  }
  else
  {
    if (prev_swt1 != Prg_swt1)
    {
      prev_swt1 = Prg_swt1;
    }

  }

  Tk = 0; tek_razn = 0; power_ten = 0;

  if (Prg_swt1 == HIGH)
  { //требуется работа с ТЭНом
    t_work_warm = t_prom - t_warm ;//время работы тэна
    Tk = Prg_TkVol;
    tek_razn = Tk - Tk_now;
    if (Prg_ModeWarm == 1) //требуется поддержание Тк в течение t секунд
    {
      if (Tk_now < Tk)
      { //смотрим на сколько меньше
        Adjust_Power_Ten(Tk_now, Tk); //Tk_now - текущая температура,Tk - температура котор хотим
      }
      else
      {
        StatusWarm = LOW;
        if (reachT == 0)
        {
          //только достигли и засекаем
          t_work_warm_ModeWarm = t_prom;
          reachT = 1;
          Serial.println(" zasekaem vremy (mode 1)");
        }

      }

      if ((reachT == 1) && (Prg_WarmTime != 0))
      {
        if ((t_prom - t_work_warm_ModeWarm) >= Prg_WarmTime)
        { //мы поддерживали Tk в течении t секунд или если WarmWorkTime=0 то поддерживаем до ручного отключения
          Prg_swt1 = LOW;
          StatusWarm = LOW; //ВЫКЛ нагрева
          reachT = 0;
          //beebeep(300, 1000); //выдаем звук сигнал
          Serial.println("off warm (mode 1)");
          Serial.println("t_prom " + String(t_prom));
          Serial.println("t_work_warm_ModeWarm " + String(t_work_warm_ModeWarm));
          Serial.println("WarmWorkTime " + String(Prg_WarmTime));

          if (Prg == true)
          {
            Prog[NumStrPrg].WCompl = 1; //шаг по нагреву исполнен
          }

        }
      }
    }

    if (Prg_ModeWarm == 2)
    { //требуется достижение Tk
      if (Tk_now < Tk)
      {
        Adjust_Power_Ten(Tk_now, Tk); //Tk_now - текущая температура,Tk - температура котор хотим,power_ten - соответствующая мощность, StatusReleTv1 - статус твердого реле
      }
      else
      { // Tk достигнуто
        Prg_swt1 = LOW;
        StatusWarm = LOW; //ВЫКЛ нагрева
        //beebeep(300, 1000); //выдаем звук сигнал
        Serial.println(F(" off warm (mode 2)"));
      }
    }
    if (Prg_ModeWarm == 3)
    { //просто нагрев
      power_ten = Prg_WarmVol;
      StatusWarm = HIGH; //ВКЛ нагрева

      if ((t_work_warm >= Prg_WarmTime) && (Prg_WarmTime != 0))
      { //таймер выключения
        Prg_swt1 = LOW;
        StatusWarm = LOW; //ВЫКЛ нагрева
        //beebeep(300, 1000); //выдаем звук сигнал
        Serial.println(F(" off warm taimer (mode 3)"));
        if (Prg == true)
        {
          Prog[NumStrPrg].WCompl = 1; //шаг по нагреву исполнен
        }
      }
    }
    if (Prg_ModeWarm == 4)
    { //просто нагрев
      Adjust_Power_Ten(Tk_now, Tk); //Tk_now - текущая температура,Tk - температура котор хотим
      if (Tk_now > Tk)
      {
        if (reachT == 0)
        {
          //только достигли и засекаем
          t_work_warm_ModeWarm = t_prom;
          reachT = 1;
          Serial.println(" zasekaem vremy (mode 4)");
        }

      }

      if ((reachT == 1) && (Prg_WarmTime != 0))
      {
        if ((t_prom - t_work_warm_ModeWarm) >= Prg_WarmTime)
        { //мы поддерживали Tk в течении t секунд или если WarmWorkTime=0 то поддерживаем до ручного отключения
          Prg_swt1 = LOW;
          StatusWarm = LOW; //ВЫКЛ нагрева
          reachT = 0;
          //beebeep(300, 1000); //выдаем звук сигнал
          Serial.println("off warm (mode 4)");
          Serial.println("t_prom " + String(t_prom));
          Serial.println("t_work_warm_ModeWarm " + String(t_work_warm_ModeWarm));
          Serial.println("WarmWorkTime " + String(Prg_WarmTime));

          if (Prg == true)
          {
            Prog[NumStrPrg].WCompl = 1; //шаг по нагреву исполнен
          }

        }
      }

    }


    if ((TWarmContr_now >= Prg_TWarmContr) && (Prg_TWarmContr != 0))
    { // перегрев
      Prg_swt1 = LOW;
      StatusWarm = LOW; //ВЫКЛ нагрева
      Serial.println(F(" overwarm"));
      erSt = 2;
      if (Prg == true)
      {
        Prog[NumStrPrg].statErr = 1; //статус ошибки
      }
      else
      {

      }

    }
    for (byte i = 0; i < NSenseFact; i++) {
      if ((tempC[i] == -127) && (t[i] == 1))
      { //датчик не зашарился
        Prg_swt1 = LOW;
        StatusWarm = LOW; //ВЫКЛ нагрева
        Serial.println(F(" overwarm"));
        erSt = 1;
        if (Prg == true)
        {
          Prog[NumStrPrg].statErr = 1; //статус ошибки
        }
        else
        {

        }
      }
    }




    // управление таймерами/перерывами
    now_StatusWarm = HIGH;
    if (now_year > 1970) {
      //считаем время установлено
      parseUnixTime(now_timeUnx, now_hour, now_min, now_sec, now_wd, now_day, now_month, now_year);

      if ((TimerWarmStUnx > 0) && (TimerWarmAvailSt == 1)) { //время отсроченного старта установлено
        if (now_timeUnx > TimerWarmStUnx) {//сейчас время больше чем время вкл, значит включаем
          now_StatusWarm = now_StatusWarm & HIGH;
        } else { //выключаем
          now_StatusWarm = now_StatusWarm & LOW;
        }
      }
      if ((TimerWarmEndUnx > 0) && (TimerWarmAvailEnd == 1)) { //время отсроченного выключения установлено
        if (now_timeUnx > TimerWarmEndUnx) {//сейчас время больше чем время откл, значит выключаем
          now_StatusWarm = now_StatusWarm & LOW;
        } else { //включаем
          now_StatusWarm = now_StatusWarm & HIGH;
        }
      }
    }
  }
  else
  { //не требуется работа с ТЭНом
    StatusWarm = LOW; //ВЫКЛ нагрева
  }
  StatusWarm = now_StatusWarm & StatusWarm;
  PowerManageDevicePWM();
}

//------------------------------------------------------------------------------------------------------------------
