void working_other()
{
  uint32_t Other_control_now = millis();
  
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
