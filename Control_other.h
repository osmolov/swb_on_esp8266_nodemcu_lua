void working_other()
{
  uint32_t Other_control_now = millis();
#ifdef USE_DHT

  uint16_t t_dht, h_dht;
  


  if (((Other_control_now - DHT_control ) > 2500) || (Other_control_now < 2500))
  { //выполняем

    h_dht = dht.readHumidity();   //Считываем влажность
    t_dht = dht.readTemperature();// Считываем температуру
    if (isnan(h_dht) || isnan(t_dht))  {
#ifdef USE_LOG
      Serial.println("Засада с DHT");
#endif
#ifdef USE_LCD
      lcd.setCursor(0, 0);
      lcd.print(F("--DHT Error--   "));
#endif

    }
    else {
#ifdef USE_LCD
      lcd.setCursor(0, 0);
      lcd.print("H=" + String(h_dht) + " %, T=" + String(t_dht) + " C  ");
#endif

#ifdef USE_LOG
      Serial.print("Влажность: "); Serial.print(h_dht); Serial.println(" %\t");
      Serial.print("Температура: "); Serial.print(t_dht); Serial.println(" C");
#endif

    }
    DHT_control = Other_control_now;
  }
#endif

  
#ifdef USE_LCD
 if (((Other_control_now - LCD_control ) > 1000) || (Other_control_now < 1000))
  { //выполняем

    lcd.setCursor(0, 1);
    lcd.print(timeToStr(now_timeUnx) + " " + dateToStr(now_timeUnx).substring(0, 5) + "  ");
    LCD_control = Other_control_now;
  }
#endif
}
//------------------------------------------------------------------------------------------------------------------
