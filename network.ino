
// const char *ssid = "kolin2";
// const char *password = "hovnokleslo";

// //WebServer server(80);

// void newtworkStartup()
// {
//     lcdStartNetworking();
//     WiFi.begin(ssid, password);
//     delay(3000);
//     if (WiFi.status() == WL_CONNECTED)
//     {
//         commSerial.println("");
//         commSerial.print("Connected to ");
//         commSerial.println(ssid);
//         commSerial.print("IP address: ");
//         commSerial.println(WiFi.localIP());
//         lcdNetworkStatus(0);
//     }
//     else
//     {
//         lcdNetworkStatus(1);
//         commSerial.println("");
//         commSerial.print("failed to connect in time");
//     }

//     server.on("/", HTTP_GET, handleIndexPage);
//     server.on("/firmware", HTTP_GET, handleFirmwarePage);
//     server.on("/firmwareupdate", HTTP_POST, handleFirmware1, handleFirmware2);
//     server.on("/getdata", handleData); //To get update of ADC Value only
//     server.begin();
// }

// void handleData()
// {
//     int a = random(1024);

    
//     //constructBigString();
//     //commSerial.print(stringBuffer);
//     String webValue = String(a);
//     server.send(200, "text/plane", webValue); //Send ADC value only to client ajax request
// }

// void handleIndexPage()
// {
//     String s = INDEX_page;
//     server.sendHeader("Connection", "close");
//     server.send(200, "text/html", s);
// }

// void handleFirmwarePage()
// {
//     String s = FIRMWARE_page;
//     server.sendHeader("Connection", "close");
//     server.send(200, "text/html", s);
// }

// void handleFirmware1()
// {
//     server.sendHeader("Connection", "close");
//     server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
//     ESP.restart();
// }

// void handleFirmware2()
// {
//     HTTPUpload &upload = server.upload();
//     if (upload.status == UPLOAD_FILE_START)
//     {
//         commSerial.printf("Update: %s\n", upload.filename.c_str());
//         if (!Update.begin(UPDATE_SIZE_UNKNOWN))
//         { //start with max available size
//             Update.printError(commSerial);
//         }
//     }
//     else if (upload.status == UPLOAD_FILE_WRITE)
//     {
//         /* flashing firmware to ESP*/
//         if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
//         {
//             Update.printError(commSerial);
//         }
//     }
//     else if (upload.status == UPLOAD_FILE_END)
//     {
//         if (Update.end(true))
//         { //true to set the size to the current progress
//             commSerial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
//         }
//         else
//         {
//             Update.printError(commSerial);
//         }
//     }
// }