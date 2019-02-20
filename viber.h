String doViberMessage(void) {
   String msg = "";
   
   msg += "[BMP280 t]: " + String(bme.readTemperature()) + ", ";
   msg += "[BMP280 mmHg]: " + String(bmePressure) + ", ";
   msg += "[BMP280 alt]: " + String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + " // ";
   for (uint8_t i = 0; i < NSenseMax; i++)  {
     if (t[i] == 1) {
        msg += "[Temp" + String(i) + "]: " + String(tempC[i]) + " ";
     }
   }

   return msg;
}

void doViberStatusMessage(void) {
   if ( (!ApMode) && (WiFi.status() == WL_CONNECTED) && useViber ) {
      Serial.print("[HTTP] begin...\n");
      http.begin(viberURL);
      http.addHeader("Content-Type", "application/application/json");

      Serial.print("[HTTP] POST...\n");
      // start connection and send HTTP header
      int httpCode;
      
      json_obj = "\"auth_token\": \"" + viberAuthToken + "\", \"receiver\": \"" + viberUserId + "\", \"min_api_version\": 1, \"sender\": { \"name\": \"ESP8266 Bot\", \"avatar\": \"http://powereyesonline.com/avatar.jpg\" }, \"tracking_data\": \"tracking data\", \"type\": \"text\",  \"text\": \"" + doViberMessage() + "\"";

      Serial.print("[JSON] : {" + json_obj + "}\n");
      
      httpCode = http.POST("{" + json_obj + "}");

      Serial.print("[RESPONSE]: " + String(httpCode) + "\n");
   }
}

void doViberAlarmMessage(int sensN) {
   if ( (!ApMode) && (WiFi.status() == WL_CONNECTED) && useViber ) {
      int httpCode = -1;

      while (httpCode != 200) {
         http.begin(viberURL);
         http.addHeader("Content-Type", "application/application/json");

         json_obj = "\"auth_token\": \"" + viberAuthToken + "\", \"receiver\": \"" + viberUserId + "\", \"min_api_version\": 1, \"sender\": { \"name\": \"ESP8266 Bot\", \"avatar\": \"http://powereyesonline.com/avatar.jpg\" }, \"tracking_data\": \"tracking data\", \"type\": \"text\",  \"text\": \"Alarm on sensor" + mesTemp[sensN].NsenseM + ": " + mesTemp[sensN].TempM + "! " + mesTemp[sensN].Message + "! Other metrics: " + doViberMessage() + "\"";
         Serial.print("[JSON] : {" + json_obj + "}\n");
         httpCode = http.POST("{" + json_obj + "}");
         Serial.print("[RESPONSE] : " + String(httpCode) + "\n");
         delay(20);
      }
   }  
}
