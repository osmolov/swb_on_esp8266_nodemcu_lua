void h_prog()//selprog
{
  /*
    Первая строка - заголовок программы
    01             Prg_Nom (0)Номер строки программы
    02          WarmPrgChB (1)Использовать нагрев
    03         Prg_WarmVol (2)-мощность тэна
    04           Prg_TkVol (3)-температура нагрева
    05        Prg_ModeWarm (4)-режим нагрева:удержание,фикс.мощн
    06          Prg_Nsense (5)-какой датчик использовать для нагрева
    07      Prg_TWarmContr (6)-температура аварии
    08 Prg_NsenseWarmContr (7)-какой датчик использовать для аварии
    09        Prg_WarmTime (8)-время нагрева

    10           MixPrgChB (9) Использовать миксер
    11        Prg_MixOnSec(10) -время ВКЛ
    12       Prg_MixOffSec(11) -время ВЫКЛ
    13         Prg_MixTime(12) -время работы
    14  Prg_NsenseMixContr(13) -какой датчик использовать для миксера
    15       Prg_TMixContr(14) -температура до которой работает миксер

    16           OtbPrgChB(15) Использовать клапан отбора
    17  Prg_NsenseOtbContr(16) -какой датчик использовать для отбора
    18          Prg_TstOtb(17) -температура ВКЛ
    19         Prg_TendOtb(18) -температура ВЫКЛ

    20       Prg_WorkContr(19) контроль выполнения: по нагреву, по миксеру
    21         Prg_NextStr(20) -переход к следующему шагу: выдать предупреждение и ждать подтверждения, просто перейти
    22         Prg_Message(21) -сообщение
               fileStrData[22] -шаг по нагреву исполнен
               fileStrData[23] -шаг по мешалке исполнен
               fileStrData[24] -начато выполнение
               fileStrData[25] -получен ответ на сообщение
               fileStrData[26] -статус ошибки
    Последняя строка - END
  */

  /*
    Zernovoy  zator dly bragi
    ЗЕРНОВОЙ ЗАТОР ДЛЯ БРАГИF
    01/02/03/04/05/06/07/08/09/10/11/12/13/14/15/16/17/18/19/20/21
    1/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 1/ЗАПОЛН.БАК ВОДОЙ 19л.ПРОВ.УРОВЕНЬ ВОДЫ/F
    1/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 1/ОТКР.ВЕРХН.КРАН ПВР/F
    1/ 1/ 1/ 5/60/ 6/30/60/0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/НАГРЕВ Тк до 60С/F
    1/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 0/ 1/ЗАКР.ВЕРХН.КРАН ПВР/F

  */

  /*  MESSAGES[0][0] = "ЗЕРНОВОЙ ЗАТОР ДЛЯ БРАГИ";
    MESSAGES[0][1] = "24";

    FillMass(1, 0, 0, 0, 0, 0, 1);
    MESSAGES[1][0] = "ЗАПОЛН.БАК ВОДОЙ 19л.";
    MESSAGES[1][1] = "ПРОВ.УРОВЕНЬ ВОДЫ";

    FillMass(2, 0, 0, 0, 0, 0, 1);
    MESSAGES[2][0] = "ОТКР.ВЕРХН.КРАН ПВР";

    FillMass(3, 60, 0, 0, 0, 0, 1);
    MESSAGES[3][0] = "НАГРЕВ Тк до 60С";
    MESSAGES[3][1] = "ЗАКР.ВЕРХН.КРАН ПВР";

    FillMass(4, 65, 0, 0, 0, 0, 0);
    MESSAGES[4][0] = "НАГРЕВ Тк до 65С";

    FillMass(5,  0, 0, 0, 0, 0, 1);
    MESSAGES[5][0] = "ПОДГ.ЗАСЫПЬ";

    FillMass(6,  0, 0, 1, 0, 0, 1);
    MESSAGES[6][0] = "МЕШ.ВКЛ.ВНЕС.ЗАСЫПЬ";

    FillMass(7, 0, 0, 0, 0, 0, 1);
    MESSAGES[7][0] = "ВНЕС.АЛЬФААМИЛАЗУ";

    FillMass(8, 70, 0, 1, 0, 0, 0);
    MESSAGES[8][0] = "МЕШ.ВКЛ.НАГРЕВ Тк до 70С";

    FillMass(9,  0, 0, 0, 0, 0, 1);
    MESSAGES[9][0] = "ПРОВ.ДАВЛЕНИЕ(0,3АТМ)";

    FillMass(10, 75, 0, 1, 0, 0, 0);
    MESSAGES[10][0] = "МЕШ.ВКЛ.НАГРЕВ Тк до 75С";

    FillMass(11,  0, 0, 1, 0, 0, 1);
    MESSAGES[11][0] = "МЕШ.ВКЛ.ДОБ.В БАК 5л.ВОДЫ";

    FillMass(12, 96, 0, 1, 0, 0, 0);
    MESSAGES[12][0] = "МЕШ.ВКЛ.НАГРЕВ Тк 96С";

    FillMass(13, 96, 120 * 60, 1, 0, 0, 0);
    MESSAGES[13][0] = "МЕШ.ВКЛ.";
    MESSAGES[13][1] = "ПОДДЕРЖ.Тк 96С 2ч.";

    FillMass(14, 0, 0, 1, 0, 0, 1);
    MESSAGES[14][0] = "МЕШ.ВКЛ.ТЭН ОТКЛ";
    MESSAGES[14][1] = "ВКЛ.ВОДУ НА ОХЛАЖД.";

    FillMass(15, 64, 0, 1, 0, 0, 0);
    MESSAGES[15][0] = "МЕШ.ВКЛ.ТЭН ОТКЛ.";
    MESSAGES[15][1] = "СНИЖ.Тк до 62-64С";

    FillMass(16, 0, 0, 0, 0, 0, 1);
    MESSAGES[16][0] = "МЕШ.ОТКЛ.СТОП ОХЛАЖД.";
    MESSAGES[16][1] = "СЛЕЙТЕ ВОДУ ДО СР.КР.";

    FillMass(17, 0, 0, 0, 0, 0, 1);
    MESSAGES[17][0] = "ВНЕС.ГЛЮКАВАМОРИН";

    FillMass(18, 62, 120 * 60, 1, 0, 0, 0);
    MESSAGES[18][0] = "МЕШ.ВКЛ.ПОДДЕРЖ Тк62-64С 2ч.";
    MESSAGES[18][1] = "ОСАХАР.ЗАВЕРШЕНО";

    FillMass(19, 0, 0, 0, 0, 0, 1);
    MESSAGES[19][0] = "МЕШ.ОТКЛ.ПОДКЛ.ВОДУ";

    FillMass(20, 30, 0, 1, 0, 0, 1);
    MESSAGES[20][0] = "МЕШ.ВКЛ.ТЭН ОТКЛ.";
    MESSAGES[20][1] = "СНИЖ.Тк до 30С";

    FillMass(21,  0, 0, 0, 0, 0, 1);
    MESSAGES[21][0] = "МЕШ.ОТКЛ.ВНЕС.ДРОЖЖИ";

    FillMass(22, 0, 0, 1, 2 * 60, 0, 1);
    //FillMass(22, 0, 0, 1, 15, 0, 1);
    MESSAGES[22][0] = "МЕШ.ВКЛ.НА 2мин";

    FillMass(23, 0, 0, 1, 10, 4 * 60 * 60, 0);
    //FillMass(23, 0, 0, 1, 10, 5, 0);
    MESSAGES[23][0] = "МЕШ.ВКЛ.4ч.НА 10сек.";

    FillMass(24, 0, 0, 0, 0, 0, 0);
    MESSAGES[24][0] = "СТОП";
  */

  LoginContr();

  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Выбор программы</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".textfield {width: 50px; text-align: center;}");
  message += F(".selectfield {width: 150px; text-align: center;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += F("function OpenPrgFile(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/open_file', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=      F("if (request.readyState == 4) {\n");
  message +=        F("var data = JSON.parse(request.responseText);\n ");
  message +=        F("document.getElementById('Prg_Name').value = data.fileTitle}};\n");
  message += F("request.send(null);\n");
  message += F("}\n");
  message += F("function refreshDataFile(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_file', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('Prg_Nom').value = data.Prg_Nom;\n");
  message +=         F("document.getElementById('WarmPrgChB').checked = data.WarmPrgChB;\n");
  message +=         F("document.getElementById('Prg_WarmVol').value = data.Prg_WarmVol;if (data.WarmPrgChB == true) {document.getElementById('Prg_WarmVol').disabled=false} else {document.getElementById('Prg_WarmVol').disabled=true};\n");
  message +=         F("document.getElementById('Prg_TkVol').value = data.Prg_TkVol;if (data.WarmPrgChB == true) {document.getElementById('Prg_TkVol').disabled=false} else {document.getElementById('Prg_TkVol').disabled=true};\n");
  message +=         F("document.getElementById('Prg_ModeWarm').value = data.Prg_ModeWarm;if (data.WarmPrgChB == true) {document.getElementById('Prg_ModeWarm').disabled=false} else {document.getElementById('Prg_ModeWarm').disabled=true};\n");
  message +=         F("document.getElementById('Prg_Nsense').value = data.Prg_Nsense;if (data.WarmPrgChB == true) {document.getElementById('Prg_Nsense').disabled=false} else {document.getElementById('Prg_Nsense').disabled=true};\n");
  message +=         F("document.getElementById('Prg_TWarmContr').value = data.Prg_TWarmContr;if (data.WarmPrgChB == true) {document.getElementById('Prg_TWarmContr').disabled=false} else {document.getElementById('Prg_TWarmContr').disabled=true};\n");
  message +=         F("document.getElementById('Prg_NsenseWarmContr').value = data.Prg_NsenseWarmContr;if (data.WarmPrgChB == true) {document.getElementById('Prg_NsenseWarmContr').disabled=false} else {document.getElementById('Prg_NsenseWarmContr').disabled=true};\n");
  message +=         F("document.getElementById('Prg_WarmTime').value = data.Prg_WarmTime;if (data.WarmPrgChB == true) {document.getElementById('Prg_WarmTime').disabled=false} else {document.getElementById('Prg_WarmTime').disabled=true};\n");

  message +=         F("document.getElementById('MixPrgChB').checked = data.MixPrgChB;\n");
  message +=         F("document.getElementById('Prg_MixOnSec').value = data.Prg_MixOnSec;if (data.MixPrgChB == true) {document.getElementById('Prg_MixOnSec').disabled=false} else {document.getElementById('Prg_MixOnSec').disabled=true};\n");
  message +=         F("document.getElementById('Prg_MixOffSec').value = data.Prg_MixOffSec;if (data.MixPrgChB == true) {document.getElementById('Prg_MixOffSec').disabled=false} else {document.getElementById('Prg_MixOffSec').disabled=true};\n");
  message +=         F("document.getElementById('Prg_MixTime').value = data.Prg_MixTime;if (data.MixPrgChB == true) {document.getElementById('Prg_MixTime').disabled=false} else {document.getElementById('Prg_MixTime').disabled=true};\n");
  message +=         F("document.getElementById('Prg_NsenseMixContr').value = data.Prg_NsenseMixContr;if (data.MixPrgChB == true) {document.getElementById('Prg_NsenseMixContr').disabled=false} else {document.getElementById('Prg_NsenseMixContr').disabled=true};\n");
  message +=         F("document.getElementById('Prg_TMixContr').value = data.Prg_TMixContr;if (data.MixPrgChB == true) {document.getElementById('Prg_TMixContr').disabled=false} else {document.getElementById('Prg_TMixContr').disabled=true};\n");

  message +=         F("document.getElementById('OtbPrgChB').checked = data.OtbPrgChB;\n");
  message +=         F("document.getElementById('Prg_NsenseOtbContr').value = data.Prg_NsenseOtbContr;if (data.OtbPrgChB == true) {document.getElementById('Prg_NsenseOtbContr').disabled=false} else {document.getElementById('Prg_NsenseOtbContr').disabled=true};\n");
  message +=         F("document.getElementById('Prg_TstOtb').value = data.Prg_TstOtb;if (data.OtbPrgChB == true) {document.getElementById('Prg_TstOtb').disabled=false} else {document.getElementById('Prg_TstOtb').disabled=true};\n");
  message +=         F("document.getElementById('Prg_TendOtb').value = data.Prg_TendOtb;if (data.OtbPrgChB == true) {document.getElementById('Prg_TendOtb').disabled=false} else {document.getElementById('Prg_TendOtb').disabled=true};\n");

  message +=         F("document.getElementById('Prg_WorkContr').value = data.Prg_WorkContr;\n");
  message +=         F("document.getElementById('Prg_NextStr').value = data.Prg_NextStr;\n");
  message +=         F("document.getElementById('Prg_Message').value = data.Prg_Message;\n");

  message +=         F("}};\n");
  message += F("request.send(null);\n");
  message += F("}\n");
  //-----------------
  message += F("function accessContrButt(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_contr', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_open_file').disabled=true} else {document.getElementById('butt_open_file').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('NameProg').disabled=true} else {document.getElementById('NameProg').disabled=false};\n");
  message +=         F("if ((data.Prg == true)||(data.NumStrPrgAll<1)) {document.getElementById('butt_save').disabled=true} else {document.getElementById('butt_save').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_add').disabled=true} else {document.getElementById('butt_add').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_del').disabled=true} else {document.getElementById('butt_del').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_prev').disabled=true} else {document.getElementById('butt_prev').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_start_prg').disabled=true} else {document.getElementById('butt_start_prg').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_next').disabled=true} else {document.getElementById('butt_next').disabled=false};\n");
  message +=         F("if (data.Prg == true) {document.getElementById('butt_cont_prg').disabled=false} else {document.getElementById('butt_cont_prg').disabled=true};\n");

  message +=         F("}};\n");
  message += F("request.send(null);\n");
  message += F("}\n");
  message += F("setInterval(accessContrButt, 500);\n");
  //----------
  message += F("function tekStat(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_tekStat', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('WarmPrgChB_V').checked = data.WarmPrgChB_V;\n");
  message +=         F("document.getElementById('Prg_WarmVol_V').value = data.Prg_WarmVol_V;\n");
  message +=         F("document.getElementById('Prg_TkVol_V').value = data.Prg_TkVol_V;\n");
  message +=         F("document.getElementById('Prg_TWarmContr_V').value = data.Prg_TWarmContr_V;\n");
  message +=         F("document.getElementById('Prg_WarmTime_V').value = data.Prg_WarmTime_V;\n");
  message +=         F("document.getElementById('MixPrgChB_V').checked = data.MixPrgChB_V;\n");
  message +=         F("document.getElementById('Prg_MixOnSec_V').value = data.Prg_MixOnSec_V;\n");
  message +=         F("document.getElementById('Prg_MixOffSec_V').value = data.Prg_MixOffSec_V;\n");
  message +=         F("document.getElementById('Prg_MixTime_V').value = data.Prg_MixTime_V;\n");
  message +=         F("document.getElementById('Prg_TMixContr_V').value = data.Prg_TMixContr_V;\n");
  message +=         F("document.getElementById('OtbPrgChB_V').checked = data.OtbPrgChB_V;\n");
  message +=         F("document.getElementById('Prg_TstOtb_V').value = data.Prg_TstOtb_V;\n");


  message +=         F("}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(tekStat, 700);\n");

  message += F("function EditDataFile(){\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_WarmVol').disabled=false} else {document.getElementById('Prg_WarmVol').disabled=true};\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_TkVol').disabled=false} else {document.getElementById('Prg_TkVol').disabled=true};\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_ModeWarm').disabled=false} else {document.getElementById('Prg_ModeWarm').disabled=true};\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_Nsense').disabled=false} else {document.getElementById('Prg_Nsense').disabled=true};\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_TWarmContr').disabled=false} else {document.getElementById('Prg_TWarmContr').disabled=true};\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_NsenseWarmContr').disabled=false} else {document.getElementById('Prg_NsenseWarmContr').disabled=true};\n");
  message +=  F("if (document.getElementById('WarmPrgChB').checked == true) {document.getElementById('Prg_WarmTime').disabled=false} else {document.getElementById('Prg_WarmTime').disabled=true};\n");

  message +=  F("if (document.getElementById('MixPrgChB').checked == true) {document.getElementById('Prg_MixOnSec').disabled=false} else {document.getElementById('Prg_MixOnSec').disabled=true};\n");
  message +=  F("if (document.getElementById('MixPrgChB').checked == true) {document.getElementById('Prg_MixOffSec').disabled=false} else {document.getElementById('Prg_MixOffSec').disabled=true};\n");
  message +=  F("if (document.getElementById('MixPrgChB').checked == true) {document.getElementById('Prg_MixTime').disabled=false} else {document.getElementById('Prg_MixTime').disabled=true};\n");
  message +=  F("if (document.getElementById('MixPrgChB').checked == true) {document.getElementById('Prg_NsenseMixContr').disabled=false} else {document.getElementById('Prg_NsenseMixContr').disabled=true};\n");
  message +=  F("if (document.getElementById('MixPrgChB').checked == true) {document.getElementById('Prg_TMixContr').disabled=false} else {document.getElementById('Prg_TMixContr').disabled=true};\n");

  message +=  F("if (document.getElementById('OtbPrgChB').checked == true) {document.getElementById('Prg_NsenseOtbContr').disabled=false} else {document.getElementById('Prg_NsenseOtbContr').disabled=true};\n");
  message +=  F("if (document.getElementById('OtbPrgChB').checked == true) {document.getElementById('Prg_TstOtb').disabled=false} else {document.getElementById('Prg_TstOtb').disabled=true};\n");
  message +=  F("if (document.getElementById('OtbPrgChB').checked == true) {document.getElementById('Prg_TendOtb').disabled=false} else {document.getElementById('Prg_TendOtb').disabled=true};\n");
  message += F("}\n");

  message += F("function check_message(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/check', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.needAlert == 1) {alert(data.AlertMessage);openUrl('/switch?Prg_message_show='+data.NumStrPrg);refreshDataFile();};\n");
  message +=         F("if (data.endPrg == 1) {alert(data.AlertMessage);openUrl('/switch?End_message_show='+data.NumStrPrg);};\n");
  //message +=         F("if ((parseInt(document.getElementById('Prg_Nom').value) > 0) && (parseInt(document.getElementById('Prg_Nom').value) != data.NumStrPrg)) {refreshDataFile();};\n");
  message +=         F("if (parseInt(document.getElementById('Prg_Nom').value) != data.NumStrPrg) {refreshDataFile();};\n");
  message +=         F("if (data.needRefrPrg == 1) {refreshDataFile();}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(check_message, 1000);\n");


  message += F("function refreshDataAlert(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.beepeep > 0) {document.location.href = \"/alert\"}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshDataAlert, 1000);\n");
  message += refreshTempMessage("selprog");
  message += F("</script>");
  message += F("</head>");
  message += F("<body onload=\"EditDataFile();\">");
  message += "<form method=\"get\" action=\"/save_prg\">";
  //message += "<form method=\"get\" >";
  //message += "<form method=\"get\">";
  message += F("<h3>Выбор программы</h3><p>");
  message += F("<br />");
  message += F("Использовать программу: ");
  //message += "<select name=\"NameProg\" id=\"NameProg\" title=\"Исп\" onchange=\"openUrl('/switch?NameProg='+document.getElementById('NameProg').value); refreshData();\" >\n";
  message += F("<select name=\"NameProg\" id=\"NameProg\" title=\"Исп\" onchange=\"openUrl('/switch?NameProg='+document.getElementById('NameProg').value);\" >\n");
  message += F("<option value=\"\"></option>");
  Dir dir = SPIFFS.openDir("/");
  Serial.println(NameProg);
  while (dir.next())
  {
    String fileName = dir.fileName();
    if (fileName.startsWith("/")) fileName = fileName.substring(1);
    if (fileName.endsWith(".prg"))  {
      message += F("<option value=\"");
      message += fileName;
      message += F("\"");
      if (NameProg == fileName) message += F(" selected ");
      message += F(">");
      message += fileName;
      message += F("</option>");
    }
  }
  message += F("</select>");
  message += F("<input type=\"button\"  id=\"butt_open_file\" value=\"Открыть\" onclick=\"openUrl('/switch?NameProg='+document.getElementById('NameProg').value); OpenPrgFile();refreshDataFile();\" >\n");
 // message += F("<br />");
 // message += F("<br />");
 // message += F("<input id=\"Prg_Name\" name=\"Prg_Name\" type=\"text\" value=\"");
 // message += filePrg[1] + F("\" maxlength=\"250\" style=\"width: 350px;\"/>");
  message += F("<p>");

  //______________________________________________________________________________________________________________________________________________

  message += F("<input id=\"Prg_Nom\" name=\"Prg_Nom\" type=\"text\"  class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].N; message +=  F("\" maxlength=\"2\" /> Шаг,№<br />");
  message += F("<p>");
  message += F("<input type = \"checkbox\" name=\"WarmPrgChB_V\" id=\"WarmPrgChB_V\" disabled = \"true\" <label for=\"WarmPrgChB_V\"> тек.   </label>");
  message += F("<input type = \"checkbox\" name=\"WarmPrgChB\" id=\"WarmPrgChB\" ");
  if (Prog[NumStrPrg].WOn == 1) message += F(" checked=\"checked\"");
  message += F("onchange=\"openUrl('/switch?Prg_swt1=' + this.checked); EditDataFile();\" ");
  message += F("<label for=\"WarmPrgChB\"> использовать нагрев</label>");
  message += F("<br />");
  message += F("<input id=\"Prg_WarmVol_V\" name=\"Prg_WarmVol_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_WarmVol\" name=\"Prg_WarmVol\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].WPow;
  message += F("\" maxlength=\"3\" /> Мощность,%<br />");
  message += F("<input id=\"Prg_TkVol_V\" name=\"Prg_TkVol_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_TkVol\" name=\"Prg_TkVol\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].WTk;
  message += F("\" maxlength=\"6\" /> Температура(нагрев),С<br />");
  message += F("<input id=\"Prg_ModeWarm_V\" name=\"Prg_ModeWarm_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<select name=\"Prg_ModeWarm\" id=\"Prg_ModeWarm\" title=\"Режим\">");
  message += F("<option value=\"1\""); if (Prog[NumStrPrg].WMode == 1) message += F(" selected "); message += F(" > Удержание</option>");
  message += F("<option value=\"3\""); if (Prog[NumStrPrg].WMode == 3) message += F(" selected "); message += F(" > Пост.мощность</option>");
  message += F("</select>");
  message += F(" Режим");
  message += F("<br />");
  message += F("<input id=\"Prg_Nsense_V\" name=\"Prg_Nsense_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_Nsense\" name=\"Prg_Nsense\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].WNs;
  message += F("\" maxlength=\"2\" /> номер датчика(нагрев)<br />");

  message += F("<input id=\"Prg_TWarmContr_V\" name=\"Prg_TWarmContr_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_TWarmContr\" name=\"Prg_TWarmContr\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].WTC;
  message += F("\" maxlength=\"6\" /> Температура(контроль),С<br />");

  message += F("<input id=\"Prg_NsenseWarmContr_V\" name=\"Prg_NsenseWarmContr_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_NsenseWarmContr\" name=\"Prg_NsenseWarmContr\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].WNsC;
  message += F("\" maxlength=\"2\" /> номер датчика(контроль)<br />");

  message += F("<input id=\"Prg_WarmTime_V\" name=\"Prg_WarmTime_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_WarmTime\" name=\"Prg_WarmTime\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].WTime;
  message += F("\" maxlength=\"10\" /> Время(нагрев),сек<br />");
  message += F("<br />");

  message += F("<input type = \"checkbox\" name=\"MixPrgChB_V\" id=\"MixPrgChB_V\" disabled = \"true\" <label for=\"MixPrgChB_V\"> тек.   </label>");
  message += F("<input type = \"checkbox\" name=\"MixPrgChB\" id=\"MixPrgChB\"");
  if (Prog[NumStrPrg].MOn == 1) message += F(" checked=\"checked\"");
  message += F("onchange=\"openUrl('/switch?Prg_swt2=' + this.checked);EditDataFile();\" ");
  message += F("<label for=\"MixPrgChB\"> использовать мешалку</label>");
  message += F("<br />");

  message += F("<input id=\"Prg_MixOnSec_V\" name=\"Prg_MixOnSec_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_MixOnSec\" name=\"Prg_MixOnSec\" type=\"text\" class=\"textfield\"  value=\"");
  message += Prog[NumStrPrg].MOnS;
  message += F("\" maxlength=\"10\" /> Время(миксер вкл),сек<br />");

  message += F("<input id=\"Prg_MixOffSec_V\" name=\"Prg_MixOffSec_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_MixOffSec\" name=\"Prg_MixOffSec\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].MOffS;
  message += F("\" maxlength=\"10\" /> Время(миксер выкл),сек<br />");

  message += F("<input id=\"Prg_MixTime_V\" name=\"Prg_MixTime_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_MixTime\" name=\"Prg_MixTime\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].MTime;
  message += F("\" maxlength=\"11\" /> Время(работы миксер),сек<br />");

  message += F("<input id=\"Prg_NsenseMixContr_V\" name=\"Prg_NsenseMixContr_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_NsenseMixContr\" name=\"Prg_NsenseMixContr\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].MNsC;
  message += F("\" maxlength=\"2\" /> номер датчика(контроль миксер)<br />");

  message += F("<input id=\"Prg_TMixContr_V\" name=\"Prg_TMixContr_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_TMixContr\" name=\"Prg_TMixContr\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].MTC;
  message += F("\" maxlength=\"6\" /> Температура до(миксер вкл),С<br />");
  message += F("<br />");

  message += F("<input type = \"checkbox\" name=\"OtbPrgChB_V\" id=\"OtbPrgChB_V\" disabled = \"true\" <label for=\"OtbPrgChB_V\"> тек.   </label>");
  message += F("<input type = \"checkbox\" name=\"OtbPrgChB\" id=\"OtbPrgChB\"");
  if (Prog[NumStrPrg].OOn == 1) message += " checked=\"checked\"";
  message += F("onchange=\"openUrl('/switch?Prg_swt3=' + this.checked);EditDataFile();\" ");
  message += F("<label for=\"OtbPrgChB\"> использовать клапан отбора</label>");
  message += F("<br />");

  message += F("<input id=\"Prg_NsenseOtbContr_V\" name=\"Prg_NsenseOtbContr_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_NsenseOtbContr\" name=\"Prg_NsenseOtbContr\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].ONsC;
  message += F("\" maxlength=\"2\" /> номер датчика(контроль отбор)<br />");

  message += F("<input id=\"Prg_TstOtb_V\" name=\"Prg_TstOtb_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_TstOtb\" name=\"Prg_TstOtb\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].OTst;
  message += F("\" maxlength=\"6\" /> Температура от(отбор вкл),С<br />");

  message += F("<input id=\"Prg_TendOtb_V\" name=\"Prg_TendOtb_V\" type=\"text\" class=\"textfield\" disabled = \"true\" />  ");
  message += F("<input id=\"Prg_TendOtb\" name=\"Prg_TendOtb\" type=\"text\" class=\"textfield\" value=\"");
  message += Prog[NumStrPrg].OTend;
  message += F("\" maxlength=\"6\" /> Температура до(отбор вкл),С<br />");
  message += F("<br />");

  message += F("<select name=\"Prg_WorkContr\" id=\"Prg_WorkContr\" title=\"Завершение текущего шага программы\">");
  message += F("<option value=\"0\""); if (Prog[NumStrPrg].Contr == 0) message += F(" selected "); message += F(" > По нагреву</option>");
  message += F("<option value=\"1\""); if (Prog[NumStrPrg].Contr == 1) message += F(" selected "); message += F(" > По миксеру</option>");
  message += F("</select> Завершение текущего шага");
  message += F("<br />");
  message += F("<select name=\"Prg_NextStr\" id=\"Prg_NextStr\" title=\"Действие после выполнения текущего шага\">");
  message += F("<option value=\"0\""); if (Prog[NumStrPrg].NextN == 0) message += F(" selected "); message += F(" > Предупредить и ждать</option>");
  message += F("<option value=\"1\""); if (Prog[NumStrPrg].NextN == 1) message += F(" selected "); message += F(" > Просто перейти</option>");
  message += F("</select> По выполнению шага");
  message += F("<br />");
  message += F("<input id=\"Prg_Message\" name=\"Prg_Message\" type=\"text\" value=\"");
  message += Prog[NumStrPrg].Mess;
  message += F("\" maxlength=\"200\" style=\"width: 350px; text-align: center;\" /><br />");
  message += F("<br />");


  message += F("<p>");
  //message += F("<input type=\"submit\" id=\"butt_apply\" value=\"Применить\" action=\"/save_prg\">\n");// onclick=\"openUrl('/save_prg');\" >\n");
  message += F("<input type=\"submit\" id=\"butt_save\" value=\"Сохранить\" action=\"/save_prg\">\n");

  //message += F("<input type=\"submit\" id=\"butt_save\" value=\"Сохранить\" onclick=\"openUrl('/switch?Prg_Save='+'1');\" >\n");
  message += F("<input type=\"button\" id=\"butt_add\" value=\"Добавить\" title=\"Добавить строку в программу перед текущей\" onclick=\"openUrl('/switch?Key='+'add'); refreshDataFile();\" >\n");
  message += F("<input type=\"button\" id=\"butt_del\" value=\"Удалить\"  title=\"Удалить текущую строку программы\" onclick=\"openUrl('/switch?Key='+'del'); refreshDataFile();\" >\n");

  message += F("<br />");
  message += F("<br />");

  message += F("<input type=\"button\" id=\"butt_prev\" value=\"Пред\" onclick=\"openUrl('/switch?KeyPress='+'-1'); refreshDataFile();\" >\n");
  message += F("<input type=\"button\" id=\"butt_start_prg\" value=\"Пуск\" onclick=\"openUrl('/switch?Prg='+'true'); refreshDataFile();\" >\n");
  message += F("<input type=\"button\" id=\"butt_cont_prg\" value=\"Продолжить\" onclick=\"openUrl('/switch?Prg='+'cont');\" >\n");
  message += F("<input type=\"button\" id=\"butt_stop_prg\" value=\"Стоп\" onclick=\"openUrl('/switch?Prg='+'false'); \" >\n");
  message += F("<input type=\"button\" id=\"butt_next\" value=\"След\" onclick=\"openUrl('/switch?KeyPress='+'1'); refreshDataFile();\" >\n");

  message += F("<p>");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\">");
  message += F("</form>");

  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------------------
void h_data_tekStat_prg()//data_tekStat
{
  LoginContr();
  KeyPress = 0;
  String message;
  /*
    Первая строка - заголовок программы
    01             Prg_Nom (0)Номер строки программы
    02          WarmPrgChB (1)Использовать нагрев
    03         Prg_WarmVol (2)-мощность тэна
    04           Prg_TkVol (3)-температура нагрева
    05        Prg_ModeWarm (4)-режим нагрева:удержание,фикс.мощн
    06          Prg_Nsense (5)-какой датчик использовать для нагрева
    07      Prg_TWarmContr (6)-температура аварии
    08 Prg_NsenseWarmContr (7)-какой датчик использовать для аварии
    09        Prg_WarmTime (8)-время нагрева

    10           MixPrgChB (9) Использовать миксер
    11        Prg_MixOnSec(10) -время ВКЛ
    12       Prg_MixOffSec(11) -время ВЫКЛ
    13         Prg_MixTime(12) -время работы
    14  Prg_NsenseMixContr(13) -какой датчик использовать для миксера
    15       Prg_TMixContr(14) -температура до которой работает миксер

    16           OtbPrgChB(15) Использовать клапан отбора
    17  Prg_NsenseOtbContr(16) -какой датчик использовать для отбора
    18          Prg_TstOtb(17) -температура ВКЛ
    19         Prg_TendOtb(18) -температура ВЫКЛ*/
  bool resp;
  message += F("{");
  if (Prg == true)
  {
    message += F("\"Prg\":1");
    message += F(",");
    //-----warm-------
    message += F("\"WarmPrgChB_V\":");
    if (relay1Level == 1) resp = digitalRead(swt1_pin);
    if (relay1Level == 0) resp = !digitalRead(swt1_pin);
    if (resp == HIGH) message += F("true");
    else message += F("false");
    message += F(",");
    message += F("\"Prg_WarmVol_V\":");
    message += power_ten;
    message += F(",");
    message += F("\"Prg_TkVol_V\":");
    //message += F("\"");
    message += Tk_now;

    message += F(",");
    message += F("\"Prg_TWarmContr_V\":");
    message += TWarmContr_now;
    message += F(",");
    message += F("\"Prg_WarmTime_V\":");
    if ((t_work_warm_ModeWarm != 0) && (Prg_swt1 == HIGH))  message += millis() / 1000 - t_work_warm_ModeWarm;
    else message += F("\"-\"");
    message += F(",");
    //-----mix-------
    message += F("\"MixPrgChB_V\":");
    if (relay2Level == 1) resp = digitalRead(swt2_pin);
    if (relay2Level == 0) resp = !digitalRead(swt2_pin);
    if (resp == HIGH) message += F("true");
    else message += F("false");
    message += F(",");

    message += F("\"Prg_MixOnSec_V\":");
    if ((t_pow_on != 0) && (Prg_swt2 == HIGH)) message += millis() / 1000 - t_pow_on;
    else message += F("\"-\"");
    message += F(",");

    message += F("\"Prg_MixOffSec_V\":");
    if ((t_pow_off != 0) && (Prg_swt2 == HIGH)) message += millis() / 1000 - t_pow_off;
    else message += F("\"-\"");
    message += F(",");

    message += F("\"Prg_MixTime_V\":");
    if ((t_mix != 0) && (Prg_swt2 == HIGH)) message += millis() / 1000 - t_mix;
    else message += F("\"-\"");
    message += F(",");

    message += F("\"Prg_TMixContr_V\":");
    if ((Prg_swt2 == HIGH) && (Prg_NsenseMixContr != 0)) message += TMixContr_now;
    else message += F("\"-\"");
    message += F(",");

    //----отбор------
    message += F("\"OtbPrgChB_V\":");
    if (relay3Level == 1) resp = digitalRead(swt3_pin);
    if (relay3Level == 0) resp = !digitalRead(swt3_pin);
    if (resp == HIGH) message += F("true");
    else message += F("false");
    message += F(",");

    message += F("\"Prg_TstOtb_V\":");
    if ((Prg_swt3 == HIGH) && (Prg_NsenseOtbContr != 0)) message += Tk_otb;
    else message += F("\"-\"");

  }
  else
  {
    message += F("\"Prg\":0,");
    //---нагрев----
    message += F("\"WarmPrgChB_V\":false,");
    message += F("\"Prg_WarmVol_V\":\"-\",");
    message += F("\"Prg_TkVol_V\":\"-\",");
    message += F("\"Prg_TWarmContr_V\":\"-\",");
    message += F("\"Prg_WarmTime_V\":\"-\",");
    //---mix----
    message += F("\"MixPrgChB_V\":false,");
    message += F("\"Prg_MixOnSec_V\":\"-\",");
    message += F("\"Prg_MixOffSec_V\":\"-\",");
    message += F("\"Prg_MixTime_V\":\"-\",");
    message += F("\"Prg_TMixContr_V\":\"-\",");
    //---отбор----
    message += F("\"OtbPrgChB_V\":false,");
    message += F("\"Prg_TstOtb_V\":\"-\"");

  }

  message += F("}");

  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------------------

void h_prg_check()//check
{

  LoginContr();
  KeyPress = 0;
  bool Add;
  String message, strAdd;
  message += F("{");

  //Serial.println(String(erSt));
  message += F("\"AlertMessage\":");
  message += F("\"");
  message += Prog[NumStrPrg].Mess;
  message += F("\"");


  message += F(",");
  message += F("\"needAlert\":");

  Add = 0;
  if (Prg == true)
  {
    if  ((Prog[NumStrPrg].WCompl == 1) && (Prog[NumStrPrg].Contr == 0)) //шаг по нагреву исполнен и контроль по нагреву
    {
      if  (Prog[NumStrPrg].NextN == 0)//переход к след шагу выдать предупреждение и ждать
      {
        if  (Prog[NumStrPrg].respGet == 0)//если не получен ответ на сообщение
        { //тогда передаем сообщение
          Serial.println(Prog[NumStrPrg].Mess);
          Add = 1;
        }
      }
    }
    else if ((Prog[NumStrPrg].MCompl == 2) && (Prog[NumStrPrg].Contr == 1)) //шаг по миксеру исполнен и контроль по миксеру
    {
      if  (Prog[NumStrPrg].NextN == 0)//переход к след шагу выдать предупреждение и ждать
      {
        if  (Prog[NumStrPrg].respGet == 0)//если не получен ответ на сообщение
        { //тогда передаем сообщение
          Add = 1;
        }
      }
    }
  }
  message += Add;
  //для обновления данных на странице программы при запущ.программе

  message += F(",");
  message += F("\"needRefrPrg\":");

  Add = 0;
  if (Prg == true)
  {
    if (PrevNumStrPrg != NumStrPrg)
    { //значит след строка программы начала исполняться
      PrevNumStrPrg = NumStrPrg;
      Add = 1;
    }
  }
  message += Add;

  message += F(",");
  message += F("\"endPrg\":");
  Add = 0;

  if ((Prg == false) && (Prg_accomp == true))
  {
    Add = 1;
    //Prg_accomp = false;
  }
  message += Add;

  message += F(",");
  message += F("\"NumStrPrg\":");
  message += NumStrPrg;

  message += F(",");
  if (Prg == true) message += F("\"Prg\":1");
  else message += F("\"Prg\":0");

  message += F("}");
  server.send(200, F("text/html"), message);

}
//----------------------------------------------------------------------------------------------

void h_data_check_working_prg()//data_contr
{ //
  LoginContr();
  String message;
  message += F("{");
  message += F("\"Prg\":");
  if (Prg == true) message += F("true");
  else message += F("false");
  message += F(",");
  message += F("\"NumStrPrgAll\":");
  message += NumStrPrgAll;
  message += F("}");
  server.send(200, F("text/html"), message);
}

//--------------------------------------
void h_prg_open_file()//h_prg_open_file
{
  LoginContr();
  String message, s;
  // open file for reading
  Serial.println(NameProg);
  if (NameProg.endsWith(F(".prg")))
  {
    Serial.println(F("Try open ")); Serial.println(NameProg);
    File f = SPIFFS.open("/" + NameProg, "r");
    if (!f) {
      Serial.println(F("file open failed"));
    }
    else {
      Serial.println(F(" Reading from SPIFFS file "));
      uint8_t st_start, st_end, st_len;
      for (int i = 0; i <= NumStrPrgMax; i++) {
        s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
        st_start = s.indexOf("{"); st_end = s.indexOf("}") + 1;
        Serial.println(s);
        if (s.indexOf(F("END")) == -1) {

          if ((st_start != -1) && (st_end != -1)) {
            s = s.substring(st_start, st_end); st_len = s.length();
            StaticJsonBuffer<1000> jsonBuffer;   //Memory pool
            JsonObject& root = jsonBuffer.parseObject(s);
            if (root.success()) {
              Prog[i].N = root["N"];
              Prog[i].WOn = root["WOn"];
              //Serial.print(F("i="));Serial.println(i);
              //Serial.print(F("Prog[i].WOn="));Serial.println(Prog[i].WOn);
              Prog[i].WPow = root["WPow"];
              Prog[i].WTk = root["WTk"];
              Prog[i].WMode = root["WMode"];
              Prog[i].WNs = root["WNs"];
              Prog[i].WTC = root["WTC"];
              Prog[i].WNsC = root["WNsC"];
              Prog[i].WTime = root["WTime"];

              Prog[i].MOn = root["MOn"];
              Prog[i].MOnS = root["MOnS"];
              Prog[i].MOffS = root["MOffS"];
              Prog[i].MTime = root["MTime"];
              Prog[i].MNsC = root["MNsC"];
              Prog[i].MTC = root["MTC"];

              Prog[i].Contr = root["Contr"];
              Prog[i].NextN = root["NextN"];
              const char* Mess = root["Mess"]; if (Mess != noDef) Prog[i].Mess = String(Mess);

            } else {
              Serial.println(F("Проблемы с парсингом"));
            }
          } else {
            Serial.println(F("Не форматная строка"));
          }
        } else { //нашли слово END в конце файла
          NumStrPrgAll = i;
          NumStrPrg = 0;
          Serial.println(F("Дошли до конца файла программы"));
          Serial.print(F("NumStrPrgAll = ")); Serial.println(NumStrPrgAll);
          break;
        }
      }
      f.close();
      //message += F("{\"fileTitle\":\"");
      //message += filePrg[1];
      //message += F("\"}");
    }
  }
  message = F("ok");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------------------

void Prg_fillData(int8_t next)
{
  if (NumStrPrgAll > 0)
  {
    int _NumStrPrg = NumStrPrg;
    Serial.print(F("module: Prg_fillData: next: ")); Serial.println(next);

    _NumStrPrg = _NumStrPrg + next;
    Serial.print(F("module: Prg_fillData: ")); Serial.print(F("next/prev str: ")); Serial.println(_NumStrPrg);

    if (_NumStrPrg < 0) _NumStrPrg = 0;
    if (_NumStrPrg > NumStrPrgAll - 1) _NumStrPrg = NumStrPrgAll - 1;
    NumStrPrg = _NumStrPrg;
    Serial.print(F("module: Prg_fillData: ")); Serial.print(F("after if next/prev str: ")); Serial.println(_NumStrPrg);

    if (Prg == true)
    {
      Prog[NumStrPrg].WCompl = 0; //шаг по нагреву исполнен
      Prog[NumStrPrg].MCompl = 0; //шаг по мешалке исполнен
      Prog[NumStrPrg].inProgr = 0; //начато выполнение
      Prog[NumStrPrg].respGet = 0; //получен ответ на сообщение
      Prog[NumStrPrg].statErr = 0; //статус ошибки
    }
  }
}
//---------------------------------------------------------------------------------------------
void h_prg_fill_data()//data_file
{
  LoginContr();
  String message;
  if (NumStrPrgAll > 0) {
    Prg_fillData(KeyPress);

    message += F("{");
    message += F("\"Prg_Nom\":");
    message += Prog[NumStrPrg].N;
    message += F(",");

    message += F("\"WarmPrgChB\":");
    if (Prog[NumStrPrg].WOn == 1)
      message += F("true");
    else
      message += F("false");
    message += F(",");

    message += F("\"Prg_WarmVol\":"); message += Prog[NumStrPrg].WPow; message += F(",");
    message += F("\"Prg_TkVol\":"); message += Prog[NumStrPrg].WTk; message += F(",");
    message += F("\"Prg_ModeWarm\":"); message += Prog[NumStrPrg].WMode;  message += F(",");
    message += F("\"Prg_Nsense\":"); message += Prog[NumStrPrg].WNs; message += F(",");
    message += F("\"Prg_TWarmContr\":"); message += Prog[NumStrPrg].WTC; message += F(",");
    message += F("\"Prg_NsenseWarmContr\":"); message += Prog[NumStrPrg].WNsC; message += F(",");
    message += F("\"Prg_WarmTime\":"); message += Prog[NumStrPrg].WTime; message += F(",");

    message += F("\"MixPrgChB\":");
    if (Prog[NumStrPrg].MOn == 1) message += F("true");
    else message += F("false");
    message += F(",");

    message += F("\"Prg_MixOnSec\":"); message += Prog[NumStrPrg].MOnS; message += F(",");
    message += F("\"Prg_MixOffSec\":"); message += Prog[NumStrPrg].MOffS; message += F(",");
    message += F("\"Prg_MixTime\":"); message += Prog[NumStrPrg].MTime; message += F(",");
    message += F("\"Prg_NsenseMixContr\":"); message += Prog[NumStrPrg].MNsC; message += F(",");
    message += F("\"Prg_TMixContr\":"); message += Prog[NumStrPrg].MTC; message += F(",");

    message += F("\"OtbPrgChB\":");
    if (Prog[NumStrPrg].OOn == 1) message += F("true");
    else message += F("false");
    message += F(",");

    message += F("\"Prg_NsenseOtbContr\":"); message += Prog[NumStrPrg].ONsC; message += F(",");
    message += F("\"Prg_TstOtb\":"); message += Prog[NumStrPrg].OTst; message += F(",");
    message += F("\"Prg_TendOtb\":"); message += Prog[NumStrPrg].OTend; message += F(",");

    message += F("\"Prg_WorkContr\":"); message += Prog[NumStrPrg].Contr; message += F(",");
    message += F("\"Prg_NextStr\":"); message += Prog[NumStrPrg].NextN; message += F(",");
    message += F("\"Prg_Message\":\""); message += Prog[NumStrPrg].Mess; message += F("\"");
    message += F("}");

  }
  else
  {
    message += F("{");
    message += F("\"Prg_Nom\":\"\"");
    message += F(",");

    message += F("\"WarmPrgChB\":");
    message += F("false");
    message += F(",");

    message += F("\"Prg_WarmVol\":\"\""); message += F(",");
    message += F("\"Prg_TkVol\":\"\"");  message += F(",");
    message += F("\"Prg_ModeWarm\":\"\"");  message += F(",");
    message += F("\"Prg_Nsense\":\"\""); message += F(",");
    message += F("\"Prg_TWarmContr\":\"\""); message += F(",");
    message += F("\"Prg_NsenseWarmContr\":\"\""); message += F(",");
    message += F("\"Prg_WarmTime\":\"\""); message += F(",");

    message += F("\"MixPrgChB\":");
    message += F("false");
    message += F(",");

    message += F("\"Prg_MixOnSec\":\"\""); message += F(",");
    message += F("\"Prg_MixOffSec\":\"\""); message += F(",");
    message += F("\"Prg_MixTime\":\"\""); message += F(",");
    message += F("\"Prg_NsenseMixContr\":\"\""); message += F(",");
    message += F("\"Prg_TMixContr\":\"\""); message += F(",");

    message += F("\"OtbPrgChB\":");
    message += F("false");
    message += F(",");

    message += F("\"Prg_NsenseOtbContr\":\"\""); message += F(",");
    message += F("\"Prg_TstOtb\":\"\""); message += F(",");
    message += F("\"Prg_TendOtb\":\"\""); message += F(",");

    message += F("\"Prg_WorkContr\":\"\""); message += F(",");
    message += F("\"Prg_NextStr\":\"\""); message += F(",");
    message += F("\"Prg_Message\":\""); message += F("\"");
    message += F("}");
  }

  server.send(200, F("text/html"), message);
}

//--------------------------------------------------------------------
void h_save_prg() //save_prg
{
  LoginContr();
  Serial.println(F("module save_prg"));
  if (NumStrPrgAll > 0) {
    String argName, argValue;
    Serial.print(F("args()=")); Serial.println(server.args());
    for (byte i = 0; i < server.args(); i++)  {
      argName = server.argName(i);
      Serial.println(argName);
      Serial.print(F("="));
      argValue = server.arg(i);
      Serial.println(argValue);

      //if (argName == F("Prg_Name")) Prog[NumStrPrg].WOn = argValue.toInt();
      if (argName == F("Prg_Nom"))               Prog[NumStrPrg].N = argValue.toInt();
      else if (argName == F("WarmPrgChB")) {
        if (argValue == F("on"))                      Prog[NumStrPrg].WOn = 1;
        else                                          Prog[NumStrPrg].WOn = 0;
      }
      else if (argName == F("Prg_WarmVol"))           Prog[NumStrPrg].WPow = argValue.toInt();
      else if (argName == F("Prg_TkVol"))             Prog[NumStrPrg].WTk = atof(argValue.c_str());
      else if (argName == F("Prg_ModeWarm"))          Prog[NumStrPrg].WMode = argValue.toInt();
      else if (argName == F("Prg_Nsense"))            Prog[NumStrPrg].WNs = argValue.toInt();
      else if (argName == F("Prg_TWarmContr"))        Prog[NumStrPrg].WTC = atof(argValue.c_str());
      else if (argName == F("Prg_NsenseWarmContr"))   Prog[NumStrPrg].WNsC = argValue.toInt();
      else if (argName == F("Prg_WarmTime"))          Prog[NumStrPrg].WTime = argValue.toInt();
      else if (argName == F("MixPrgChB")) {
        if (argValue == F("on"))                      Prog[NumStrPrg].MOn = 1;
        else                                          Prog[NumStrPrg].MOn = 0;
      }
      else if (argName == F("Prg_MixOnSec"))         Prog[NumStrPrg].MOnS = argValue.toInt();
      else if (argName == F("Prg_MixOffSec"))        Prog[NumStrPrg].MOffS = argValue.toInt();
      else if (argName == F("Prg_MixTime"))          Prog[NumStrPrg].MTime = argValue.toInt();
      else if (argName == F("Prg_NsenseMixContr"))   Prog[NumStrPrg].MNsC = argValue.toInt();
      else if (argName == F("Prg_TMixContr"))        Prog[NumStrPrg].MTC = atof(argValue.c_str());

      else if (argName == F("OtbPrgChB")) {
        if (argValue == F("on"))                     Prog[NumStrPrg].OOn = 1;
        else                                         Prog[NumStrPrg].OOn = 0;
      }
      else if (argName == F("Prg_NsenseOtbContr"))   Prog[NumStrPrg].ONsC = argValue.toInt();
      else if (argName == F("Prg_TstOtb"))           Prog[NumStrPrg].OTst = atof(argValue.c_str());
      else if (argName == F("Prg_TendOtb"))          Prog[NumStrPrg].OTend = atof(argValue.c_str());

      else if (argName == F("Prg_WorkContr"))        Prog[NumStrPrg].Contr = argValue.toInt();
      else if (argName == F("Prg_NextStr"))          Prog[NumStrPrg].NextN = argValue.toInt();
      else if (argName == F("Prg_Message"))          Prog[NumStrPrg].Mess = argValue;
    }
    Serial.println(NumStrPrg);
    if (NumStrPrgAll > 0 ) {
      Serial.print(F("Try open ")); Serial.println(NameProg);
      File f = SPIFFS.open("/" + NameProg, "w");
      if (!f) {
        Serial.println(F("file open failed"));
      }
      else {
        Serial.println(F(" Writing SPIFFS file "));
        String strM;
        for (int i = 0; i < NumStrPrgAll; i++) {
          strM = F("{\"N\":"); strM += i; strM += F(",");
          strM += F("\"WOn\":"); strM += Prog[i].WOn; strM += F(",");
          strM += F("\"WPow\":"); strM += Prog[i].WPow; strM += F(",");
          strM += F("\"WTk\":"); strM += Prog[i].WTk; strM += F(",");
          strM += F("\"WMode\":"); strM += Prog[i].WMode; strM += F(",");
          strM += F("\"WNs\":"); strM += Prog[i].WNs; strM += F(",");
          strM += F("\"WTC\":"); strM += Prog[i].WTC; strM += F(",");
          strM += F("\"WNsC\":"); strM += Prog[i].WNsC; strM += F(",");
          strM += F("\"WTime\":"); strM += Prog[i].WTime; strM += F(",");

          strM += F("\"MOn\":"); strM += Prog[i].MOn; strM += F(",");
          strM += F("\"MOnS\":"); strM += Prog[i].MOnS; strM += F(",");
          strM += F("\"MOffS\":"); strM += Prog[i].MOffS; strM += F(",");
          strM += F("\"MTime\":"); strM += Prog[i].MTime; strM += F(",");
          strM += F("\"MNsC\":"); strM += Prog[i].MNsC; strM += F(",");
          strM += F("\"MTC\":"); strM += Prog[i].MTC; strM += F(",");

          strM += F("\"OOn\":"); strM += Prog[i].OOn; strM += F(",");
          strM += F("\"ONsC\":"); strM += Prog[i].ONsC; strM += F(",");
          strM += F("\"OTst\":"); strM += Prog[i].OTst; strM += F(",");
          strM += F("\"OTend\":"); strM += Prog[i].OTend; strM += F(",");


          strM += F("\"Contr\":"); strM += Prog[i].Contr; strM += F(",");
          strM += F("\"NextN\":"); strM += Prog[i].NextN; strM += F(",");
          strM += F("\"Mess\":\""); strM += Prog[i].Mess; strM += F("\"");
          strM += F("}");
          Serial.println(strM);
          f.println(strM);
        }
        f.println(F("END"));
        f.close();
        Serial.println(F(" done."));
      }
    }

    String message = F("<!DOCTYPE html>");
    message += F("<html>");
    message += F("<head>");
    message += F("<title>Store Setup</title>");
    message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /selprog\">");
    message += F("</head>");
    message += F("<body>");
    message += F("Настройи сохранены успешно.");
    message += F("<p>Ждите 1 сек. или нажмите <a href=\"/index.html\">сюда</a> для перехода в главное меню.");
    message += F("</body>");
    message += F("</html>");

    server.send(200, F("text/html"), message);
  }
}
