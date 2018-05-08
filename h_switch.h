void h_switch()//switch
{
  LoginContr();
  String message = F("ok");
  uint16_t resp = 200;
  String argName, argValue;
  for (byte i = 0; i < server.args(); i++)
  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print("=");
    argValue = server.arg(i);
    Serial.println(argValue);

    if (argName == F("swt1")) {
      if (argValue == F("true"))
      {
        Prg_swt1 = HIGH;
        //PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
        Input = 100;
        Setpoint = 100;
        if (resumeState == 1) {
          save_ResumeStateFile();
        }
      }
      else Prg_swt1 = LOW;
    }
    else if (argName == F("swt2")) {
      if (argValue == F("true")) Prg_swt2 = HIGH;
      else Prg_swt2 = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }
    else if (argName == F("swt3")) {
      if (argValue == F("true")) Prg_swt3 = HIGH;
      else Prg_swt3 = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }
    else if (argName == F("resumeState")) {
      if (argValue == F("true")) {
        resumeState = HIGH; save_ResumeStateFile();
      }
      else resumeState = LOW;

    }
    else if (argName == F("relay1Level")) {
      if (argValue == F("true")) relay1Level = 1;
      else relay1Level = 0;
    }
    else if (argName == F("relay2Level")) {
      if (argValue == F("true")) relay2Level = 1;
      else relay2Level = 0;
    }
    else if (argName == F("relay3Level")) {
      if (argValue == F("true")) relay3Level = 1;
      else relay3Level = 0;
    }
    else if (argName == F("NameProg")) {
      NameProg = argValue;
      Serial.println(NameProg);
    }
    else if (argName == F("KeyPress")) {
      KeyPress = argValue.toInt();
      Serial.println(KeyPress);
    }
    else if (argName == F("Prg_swt1")) {
      if (argValue == F("true")) Prog[NumStrPrg].WOn = 1;
      else Prog[NumStrPrg].WOn = 0;
    }
    else if (argName == F("Prg_swt2")) {
      if (argValue == F("true")) Prog[NumStrPrg].MOn = 1;
      else Prog[NumStrPrg].MOn = 0;
    }
    else if (argName == F("Prg_swt3")) {
      if (argValue == F("true")) Prog[NumStrPrg].OOn = 1;
      else Prog[NumStrPrg].OOn = 0;
    }
    else if (argName == F("ApMode")) {
      if (argValue == F("true")) ApMode  = 1;
      else ApMode = 0;
    }
    else if (argName == F("AccessMode")) {
      if (argValue == F("true")) AccessMode  = 1;
      else AccessMode = 0;
    }
    else if (argName == F("useMQTT")) {
      if (argValue == F("true")) useMQTT  = 1;
      else useMQTT = 0;
    }

    else if (argName == F("Prg_Save")) {
      /*if (NumStrPrgAll > 2) {
        Serial.println("Try open " + NameProg);
        File f = SPIFFS.open("/" + NameProg, "w");
        if (!f) Serial.println(F("file open failed"));
        else {
          Serial.println(F(" Writing SPIFFS file "));
          for (int i = 1; i <= NumStrPrgAll; i++) {
            Serial.print(".");
            f.println(filePrg[i]);
          }
          f.close();
          Serial.println(F(" done."));
        }
        }*/
    }

    else if (argName == F("Prg_create"))
    {
      if (argValue.length() > 0)
      {
        String name_prg = argValue + F(".prg");
        Serial.println("Try create prg " + name_prg);
        if (!SPIFFS.exists("/" + name_prg))
        {
          File f = SPIFFS.open("/" + name_prg, "w");

          if (!f) Serial.println(F("file open failed"));

          else {
            Serial.println(F(" Writing SPIFFS file "));
            String strM;
            strM = F("{\"N\":0"); strM += ",";
            strM += F("\"WOn\":1"); strM += ",";
            strM += F("\"WPow\":100"); strM += ",";
            strM += F("\"WTk\":62"); strM += ",";
            strM += F("\"WMode\":1"); strM += ",";
            strM += F("\"WNs\":0"); strM += ",";
            strM += F("\"WTC\":45"); strM += ",";
            strM += F("\"WNsC\":1"); strM += ",";
            strM += F("\"WTime\":600"); strM += ",";

            strM += F("\"MOn\":0"); strM += ",";
            strM += F("\"MOnS\":0"); strM += ",";
            strM += F("\"MOffS\":0"); strM += ",";
            strM += F("\"MTime\":0"); strM += ",";
            strM += F("\"MNsC\":1"); strM += ",";
            strM += F("\"MTC\":55"); strM += ",";

            strM += F("\"OOn\":0"); strM += F(",");
            strM += F("\"ONsC\":0"); strM += F(",");
            strM += F("\"OTst\":0"); strM += F(",");
            strM += F("\"OTend\":0"); strM += F(",");

            strM += F("\"Contr\":0"); strM += ",";
            strM += F("\"NextN\":0"); strM += ",";
            strM += F("\"Mess\":\"Напишите сообщение\"");
            strM += F("}");
            Serial.println(strM);
            f.println(strM);
            /*uint8_t            N;  // Номер строки программы
              bool             WOn;  // Использовать нагрев
              uint8_t         WPow;  // мощность тэна
              float            WTk;  // температура нагрева
              uint8_t        WMode;  // режим нагрева:удержание,фикс.мощн
              uint8_t          WNs;  // какой датчик использовать для нагрева
              float            WTC;  // температура аварии
              uint8_t         WNsC;  // какой датчик использовать для аварии
              uint32_t       WTime;  // время нагрева

              bool            MOn;  // Использовать миксер
              uint8_t        MOnS;  // время ВКЛ
              uint8_t       MOffS;  // время ВЫКЛ
              uint32_t      MTime;  // время работы
              uint8_t        MNsC;  // какой датчик использовать для миксера
              float           MTC;  // температура до которой работает миксер

              bool            OOn;  // Использовать клапан отбора
              uint8_t        ONsC;  // какой датчик использовать для отбора
              float          OTst;  // температура ВКЛ
              float         OTend;  // температура ВЫКЛ

              uint8_t       Contr;  // контроль выполнения: по нагреву, по миксеру
              uint8_t       NextN;  // переход к следующему шагу: выдать предупреждение и ждать подтверждения, просто перейти
              String         Mess;  // сообщение

              bool         WCompl;  // fileStrData[22] -шаг по нагреву исполнен
              bool         MCompl;  // fileStrData[23] -шаг по мешалке исполнен
              bool        inProgr;  // fileStrData[24] -начато выполнение
              bool        respGet;  // fileStrData[25] -получен ответ на сообщение
              uint8_t     statErr;  // fileStrData[26] -статус ошибки
              };
              stepProgr Prog[30];
            */



            // f.println(F("1/"));
            f.println(F("END"));
          }

          f.close();
          Serial.println(F(" done."));

        }
        else
        {
          resp = 403;
          message = F("Фаил с таким именем существует!");
        }
      }

    }

    else if (argName == F("Prg"))
    {
      if (argValue == F("true"))
      {
        Prg = true; Prg_accomp = false;
        Prog[NumStrPrg].WCompl = 0; //шаг по нагреву исполнен
        Prog[NumStrPrg].MCompl = 0; //шаг по мешалке исполнен
        Prog[NumStrPrg].inProgr = 0; //начато выполнение
        Prog[NumStrPrg].respGet = 0; //получен ответ на сообщение
        Prog[NumStrPrg].statErr = 0; //статус ошибки

      }
      else if (argValue == F("false")) {
        Prg = false; Prg_swt1 = LOW; Prg_swt2 = LOW; Prg_swt3 = LOW;
      }
      else if (argValue == F("cont")) {
        if (NumStrPrg > 1) {
          Prg_swt1 = Prog[NumStrPrg].WOn;
          Prg_swt2 = Prog[NumStrPrg].MOn;
          Prg_swt3 = Prog[NumStrPrg].OOn;
        }
      }
    }
    else if (argName == F("Prg_message_show")) {
      if (NumStrPrg == argValue.toInt()) {
        Prog[NumStrPrg].respGet = 1;
      }
      else Serial.println(F("already press"));
    }
    else if (argName == F("End_message_show")) {
      if (NumStrPrg == argValue.toInt()) {
        Prg_accomp = false;
      }
      else Serial.println(F("End already press"));
    }
    else if (argName == F("Key")) {
      if (argValue == F("del")) {
        if (NumStrPrgAll > 0) {
          NumStrPrgAll--;
          KeyPress = 0;

          for (int i = NumStrPrg; i < NumStrPrgAll; i++) {
            Prog[i].N = i;
            Prog[i].WOn = Prog[i + 1].WOn;
            Prog[i].WPow = Prog[i + 1].WPow;
            Prog[i].WTk = Prog[i + 1].WTk;
            Prog[i].WMode = Prog[i + 1].WMode;
            Prog[i].WNs = Prog[i + 1].WNs;
            Prog[i].WTC = Prog[i + 1].WTC;
            Prog[i].WNsC = Prog[i + 1].WNsC;
            Prog[i].WTime = Prog[i + 1].WTime;

            Prog[i].MOn = Prog[i + 1].MOn;
            Prog[i].MOnS = Prog[i + 1].MOnS;
            Prog[i].MOffS = Prog[i + 1].MOffS;
            Prog[i].MTime = Prog[i + 1].MTime;
            Prog[i].MNsC = Prog[i + 1].MNsC;
            Prog[i].MTC = Prog[i + 1].MTC;

            Prog[i].OOn = Prog[i + 1].OOn;
            Prog[i].ONsC = Prog[i + 1].ONsC;
            Prog[i].OTst = Prog[i + 1].OTst;
            Prog[i].OTend = Prog[i + 1].OTend;

            Prog[i].Contr = Prog[i + 1].Contr;
            Prog[i].NextN = Prog[i + 1].NextN;
            Prog[i].Mess = Prog[i + 1].Mess;
          }
          Prog[NumStrPrgAll].N = 0;

          Prog[NumStrPrgAll].WOn = 0;
          Prog[NumStrPrgAll].WPow = 0;
          Prog[NumStrPrgAll].WTk = 0;
          Prog[NumStrPrgAll].WMode = 0;
          Prog[NumStrPrgAll].WNs = 0;
          Prog[NumStrPrgAll].WTC = 0;
          Prog[NumStrPrgAll].WNsC = 0;
          Prog[NumStrPrgAll].WTime = 0;

          Prog[NumStrPrgAll].MOn = 0;
          Prog[NumStrPrgAll].MOnS = 0;
          Prog[NumStrPrgAll].MOffS = 0;
          Prog[NumStrPrgAll].MTime = 0;
          Prog[NumStrPrgAll].MNsC = 0;
          Prog[NumStrPrgAll].MTC = 0;

          Prog[NumStrPrgAll].OOn = 0;
          Prog[NumStrPrgAll].ONsC = 0;
          Prog[NumStrPrgAll].OTst = 0;
          Prog[NumStrPrgAll].OTend = 0;

          Prog[NumStrPrgAll].Contr = 0;
          Prog[NumStrPrgAll].NextN = 0;
          Prog[NumStrPrgAll].Mess = "";
        }
      }
      else if (argValue == F("add")) {
        if (NumStrPrgAll > 0) {

          NumStrPrgAll++;
          NumStrPrg++;
          KeyPress = 0;

          for (int i = NumStrPrgAll - 1; i > NumStrPrg; i--) {
            Prog[i].N = i;
            Prog[i].WOn = Prog[i - 1].WOn;
            Prog[i].WPow = Prog[i - 1].WPow;
            Prog[i].WTk = Prog[i - 1].WTk;
            Prog[i].WMode = Prog[i - 1].WMode;
            Prog[i].WNs = Prog[i - 1].WNs;
            Prog[i].WTC = Prog[i - 1].WTC;
            Prog[i].WNsC = Prog[i - 1].WNsC;
            Prog[i].WTime = Prog[i - 1].WTime;

            Prog[i].MOn = Prog[i - 1].MOn;
            Prog[i].MOnS = Prog[i - 1].MOnS;
            Prog[i].MOffS = Prog[i - 1].MOffS;
            Prog[i].MTime = Prog[i - 1].MTime;
            Prog[i].MNsC = Prog[i - 1].MNsC;
            Prog[i].MTC = Prog[i - 1].MTC;

            Prog[i].OOn = Prog[i - 1].OOn;
            Prog[i].ONsC = Prog[i - 1].ONsC;
            Prog[i].OTst = Prog[i - 1].OTst;
            Prog[i].OTend = Prog[i - 1].OTend;

            Prog[i].Contr = Prog[i - 1].Contr;
            Prog[i].NextN = Prog[i - 1].NextN;
            Prog[i].Mess = Prog[i - 1].Mess;
          }
          Prog[NumStrPrg].N = NumStrPrg;

          Prog[NumStrPrg].WOn = 0;
          Prog[NumStrPrg].WPow = 0;
          Prog[NumStrPrg].WTk = 0;
          Prog[NumStrPrg].WMode = 0;
          Prog[NumStrPrg].WNs = 0;
          Prog[NumStrPrg].WTC = 0;
          Prog[NumStrPrg].WNsC = 0;
          Prog[NumStrPrg].WTime = 0;

          Prog[NumStrPrg].MOn = 0;
          Prog[NumStrPrg].MOnS = 0;
          Prog[NumStrPrg].MOffS = 0;
          Prog[NumStrPrg].MTime = 0;
          Prog[NumStrPrg].MNsC = 0;
          Prog[NumStrPrg].MTC = 0;

          Prog[NumStrPrg].OOn = 0;
          Prog[NumStrPrg].ONsC = 0;
          Prog[NumStrPrg].OTst = 0;
          Prog[NumStrPrg].OTend = 0;

          Prog[NumStrPrg].Contr = 0;
          Prog[NumStrPrg].NextN = 0;
          Prog[NumStrPrg].Mess = "";
        }
      }
    }
    else if (argName == F("Srch"))//поиск датчиков
    {
      //------------------------

      //byte insideThermometer[6][8];
      bool ex_sense;


      NSenseFact = 0;

      for (int i = 0; i < NSenseMax; i++) {
        if (!sensors.getAddress(insideThermometer[i], i))  {
          //Serial.println("Unable to find address for Device 0");
          Serial.print(F("DeviceAddress insideThermometer")); Serial.print(i); Serial.println(";");
          ex_sense = 0;
          t[i] = 0;
        }
        else
        {
          t[i] = 1;
          NSenseFact++;
        }


      }
      //save_SensorConfFile();
      //------------------------
    }
    else if (argName == F("Del_m")) {
      uint8_t nom_del;
      //butt_del_m длина 10
      nom_del = argValue.substring(10, argValue.length()).toInt();

      for (byte k = nom_del; k < NomMessAll; k++)
      {
        mesTemp[k].NsenseM = mesTemp[k + 1].NsenseM;
        mesTemp[k].TempM = mesTemp[k + 1].TempM;
        mesTemp[k].WavFile = mesTemp[k + 1].WavFile;
        mesTemp[k].Message = mesTemp[k + 1].Message;
        mesTemp[k].accompl = mesTemp[k + 1].accompl;
      }
      NomMessAll--;
      save_MsgFile();
    }
    else if (argName == F("Add_m")) {

      mesTemp[NomMessAll].NsenseM = 0;
      mesTemp[NomMessAll].TempM = 0;
      mesTemp[NomMessAll].WavFile = "";
      mesTemp[NomMessAll].Message = "";
      mesTemp[NomMessAll].accompl = false;
      NomMessAll++;
      save_MsgFile();
    }
    else if (argName == F("accompl_m")) {
      uint8_t accompl;
      //accompl длина 7
      accompl = argValue.substring(7, argValue.length()).toInt();
      // Serial.println(accompl);
      mesTemp[accompl].accompl = 0;
    }

    else if (argName == F("accompl_gen"))
    {
      if (argValue == F("true"))
      {
        for (byte k = 0; k < NomMessAll; k++)
        {
          mesTemp[k].accompl = 1;
        }
      }
      else
      {
        for (byte k = 0; k < NomMessAll; k++)
        {
          mesTemp[k].accompl = 0;
        }
      }
    }

    else if (argName == F("Need_gen")) {
      if (argValue == F("true")) {
        for (byte k = 0; k < NomMessAll; k++) {
          mesTemp[k].Need = 1;
        }
      }
      else {
        for (byte k = 0; k < NomMessAll; k++) {
          mesTemp[k].Need = 0;
        }
      }
    }

    else if (argName == F("SaveSense")) {
      save_SensorConfFile();
    }

    else if (argName == F("ntpUpd")) {
      if (argValue == F("true")) ntpUpd = 1;
      else ntpUpd = 0;
    }
    else if (argName == F("TimerMixAvailEnd")) {
      if (argValue == F("true")) TimerMixAvailEnd = 1;
      else TimerMixAvailEnd = 0;
    }
    else if (argName == F("TimerMixAvailSt")) {
      if (argValue == F("true")) TimerMixAvailSt = 1;
      else TimerMixAvailSt = 0;
    }

    else if (argName == F("TimerWarmAvailEnd")) {
      if (argValue == F("true")) TimerWarmAvailEnd = 1;
      else TimerWarmAvailEnd = 0;
    }
    else if (argName == F("TimerWarmAvailSt")) {
      if (argValue == F("true")) TimerWarmAvailSt = 1;
      else TimerWarmAvailSt = 0;
    }

    String _argName;
    for (byte i = 0; i < NomPrerMixAll; i++) {
      _argName = F("PrerMixAvail"); _argName += String(i);
      if (argName == _argName) {
        if (argValue == F("true")) PrerMix[i].Avail = HIGH;
        else PrerMix[i].Avail = LOW;
      }
    }


    _argName = F("SenseStatus");
    for (byte i = 0; i < NSenseFact; i++) {
      _argName = F("SenseStatus"); _argName += String(i);
      Serial.println(_argName);

      if (argName == _argName)
      {
        if (argValue == F("true")) t[i] = 1;
        else t[i] = 2;
        Serial.print(argValue); Serial.print(i);
      }
    }

  }
  server.send(resp, F("text/html"), message);
}
//----------------------------------------------------------------------------------------------

