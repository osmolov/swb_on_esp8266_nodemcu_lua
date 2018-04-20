//------------------------------------------------------------------
void h_otbor() {
  LoginContr();
  String message;
  message =  F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<title>Управление отбором</title>");
  message += F("<script type=\"text/javascript\">");
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
  message += refreshTempMessage(F("otbor"));
  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Управление отбором</h3><p>");
  message += F("<input id=\"ButPercOtbMinus\" type=\"button\" value=\"-\" onclick=\"document.getElementById('PercOtb').value=PowChange(document.getElementById('PercOtb').value,-1)\" />");
  message += F("<input id=\"PercOtb\" name=\"PercOtb\" type=\"text\" maxlength=\"6\" value=\"");
  message += String(PercOtb) + F("\" onchange=\"CheckVal('PercOtb')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input id=\"ButPercOtbPlust\" type=\"button\" value=\"+\" onclick=\"document.getElementById('PercOtb').value=PowChange(document.getElementById('PercOtb').value,1)\" /> Длительность вкл,%");
  message += F("<br />");
  message += F("<input id=\"ButTimeOtbPeriodMinus\" type=\"button\" value=\"-\" onclick=\"document.getElementById('TimeOtbPeriod').value=PowChange(document.getElementById('TimeOtbPeriod').value,-1)\" />");
  message += F("<input id=\"TimeOtbPeriod\" name=\"TimeOtbPeriod\" type=\"text\" value=\"");
  message += String(TimeOtbPeriod) + F("\" onchange=\"CheckVal('TimeOtbPeriod')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input id=\"ButTimeOtbPeriodPlust\" type=\"button\" value=\"+\" onclick=\"document.getElementById('TimeOtbPeriod').value=PowChange(document.getElementById('TimeOtbPeriod').value,1)\" /> период,с");
  message += F("<br />");
  message += F("<input id=\"ButTstMinus\" type=\"button\" value=\"-\" onclick=\"document.getElementById('TstOtb').value=PowChange(document.getElementById('TstOtb').value,-1)\" />");
  message += F("<input id=\"TstOtb\" name=\"TstOtb\" type=\"text\" maxlength=\"6\" value=\""); message += String(TstOtb) + F("\" onchange=\"CheckVal('TstOtb')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input id=\"ButTstPlust\" type=\"button\" value=\"+\" onclick=\"document.getElementById('TstOtb').value=PowChange(document.getElementById('TstOtb').value,1)\" /> Начало отбора,С");
  message += F("<br />");
  message += F("<input id=\"ButTendMinus\" type=\"button\" value=\"-\" onclick=\"document.getElementById('TendOtb').value=PowChange(document.getElementById('TendOtb').value,-1)\" />");
  message += F("<input id=\"TendOtb\" name=\"TendOtb\" type=\"text\" maxlength=\"6\" value=\""); message += String(TendOtb) + F("\" onchange=\"CheckVal('TendOtb')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input id=\"ButTendPlust\" type=\"button\" value=\"+\" onclick=\"document.getElementById('TendOtb').value=PowChange(document.getElementById('TendOtb').value,1)\" /> Завершение отбора,С<br />");
  message += F("<br />");
  message += F("Использовать для управления отбором");
  message += F("<select name=\"NsenseOtbContr\" title=\"Использовать датчик \">");
  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<option value="); message += String(i);
      if (NsenseOtbContr == i) message += F(" selected ");
      if (tNameSens[i].length() > 0) {
        message += F("> "); message += tNameSens[i] + F("</option>");
      }
      else {
        message += F(">Датчик "); message += String(i) + F("</option>");  
      }
    }
  }
  message += F("</select><br>");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\"><input type=\"submit\" value=\"Сохранить\" />");
  message += F("</form>");
  message += F("</body>");
  message += F("</html>");
  server.send(200, "text/html", message);
}
//------------------------------------------------------------------------------
void PowerManageDeviceOtb(bool StOtb) {
  int PwmWorkTime, PwmStopTime, t_pwm_tek;
  bool StPwmOtb;

  if (TimeOtbPeriod == 0) TimeOtbPeriod = 10;
  PwmWorkTime = PercOtb * TimeOtbPeriod * 10; //сколько работает
  PwmStopTime = (100 - PercOtb) * TimeOtbPeriod * 10; //сколько стоит

  t_pwm_tek = millis();  //текущее время
  if ((t_pwm_on_otb == 0) && (t_pwm_off_otb == 0)) t_pwm_on_otb = t_pwm_tek;
  if (((t_pwm_tek - t_pwm_on_otb) < PwmWorkTime) && (t_pwm_off_otb == 0)) {
    StPwmOtb = HIGH;
  }
  if (((t_pwm_tek - t_pwm_on_otb) >= PwmWorkTime) && (t_pwm_off_otb == 0)) {
    t_pwm_on_otb = 0;
    t_pwm_off_otb = t_pwm_tek;
  }
  if (((t_pwm_tek - t_pwm_off_otb) < PwmStopTime) && (t_pwm_on_otb == 0)) StPwmOtb  = LOW;
  if (((t_pwm_tek - t_pwm_off_otb) >= PwmStopTime) && (t_pwm_on_otb == 0)) {
    t_pwm_on_otb = t_pwm_tek;
    t_pwm_off_otb = 0;
  }
  if (PwmWorkTime == 0) StPwmOtb  = LOW;
  if (PwmStopTime == 0) StPwmOtb  = HIGH;
  if (Prg_swt3 == true) {
    if ((StPwmOtb == HIGH) && (StOtb == HIGH)) {
      if (relay3Level == 1) MydigitalWrite(swt3_pin, HIGH);
      if (relay3Level == 0) MydigitalWrite(swt3_pin, LOW);
    }
    else {
      if (relay3Level == 1) MydigitalWrite(swt3_pin, LOW);
      if (relay3Level == 0) MydigitalWrite(swt3_pin, HIGH);
    }
  }
  else {
    if (relay3Level == 1) MydigitalWrite(swt3_pin, LOW);
    if (relay3Level == 0) MydigitalWrite(swt3_pin, HIGH);
  }
}
//-----------------------------------------------------------------------------
void working_Otbor()
{
  unsigned int t_prom;
  bool StatusOtb;

  t_prom = millis() / 1000; //текущее время

  for (byte i = 0; i < NSenseFact; i++) {
    if (Prg_NsenseOtbContr == i) Tk_otb = tempC[i];
  }
  if (Prg_swt3 == true) {
    if (Prg_swt3 != prev_swt3) {
      t_otb = t_prom;
      prev_swt3 = Prg_swt3;
    }
  }
  else {
    if (Prg_swt3 != prev_swt3) {
      prev_swt3 = Prg_swt3;
    }
  }
  if (Prg_swt3 == HIGH)
  { //требуется отбирать
    t_work_otb = t_prom - t_otb;
    if ((Tk_otb >= Prg_TstOtb) && (Tk_otb <= Prg_TendOtb)) {
      StatusOtb = HIGH; //ВКЛ отбора
    }
    else {
      StatusOtb = LOW; //ВЫКЛ отбора
    }
    if ((Prg_TstOtb == 0) && (Prg_TendOtb == 0)) StatusOtb = HIGH; //ВКЛ отбора
  }
  else  {
    StatusOtb = LOW; //ВЫКЛ отбора
  }
  PowerManageDeviceOtb(StatusOtb);
}
