/*******************************************************************************
  HTML Initialize
*******************************************************************************/
void WebServerInit() 
{
  server.on("/",          pagesHome);
  server.on("/home",      pagesHome);
  server.on("/ajax",      pagesAJAX);
  server.on("/command",   pagesCommand);

  server.on("/admin", HTTP_GET, []() {
    webpage = "";
    append_HTML_header();
    webpage += 
      "<div class=\"config\">"
      "<form name=loginForm>"
      "<h1>visioHOME Login</h1>"
      "<input name=userid placeholder='User ID'> "
      "<input name=pwd placeholder=Password type=Password> "
      "<input type=submit onclick=check(this.form) class=submit value=Login></form>"
      "</div>";
    append_HTML_footer();
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", webpage);
  });
  
  server.on("/server", HTTP_GET, []() {
    webpage = "";
    append_HTML_header();
    webpage += 
      "<div class=\"config\">"
      "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
      "<h1> Версия ПО ";
    webpage += siteversion;
    webpage += 
      "</h1><input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
      "<label id='file-input' for='file'>   Choose file...</label>"
      "<input type='submit' class=submit value='Update'>"
      "<br><br>"
      "<div id='prg'></div>"
      "<br><div id='prgbar'><div id='bar'></div></div><br><a href=\"";
    webpage += visiobas;
    webpage +=
      "/visiohome/app/sketch-visiohome.ino.bin\">new visiohome sketch</a><br></form>"
      "<script>"
      "function sub(obj){"
      "var fileName = obj.value.split('\\\\');"
      "document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
      "};"
      "$('form').submit(function(e){"
      "e.preventDefault();"
      "var form = $('#upload_form')[0];"
      "var data = new FormData(form);"
      "$.ajax({"
      "url: '/update',"
      "type: 'POST',"
      "data: data,"
      "contentType: false,"
      "processData:false,"
      "xhr: function() {"
      "var xhr = new window.XMLHttpRequest();"
      "xhr.upload.addEventListener('progress', function(evt) {"
      "if (evt.lengthComputable) {"
      "var per = evt.loaded / evt.total;"
      "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
      "$('#bar').css('width',Math.round(per*100) + '%');"
      "}"
      "}, false);"
      "return xhr;"
      "},"
      "success:function(d, s) {"
      "console.log('success!') "
      "},"
      "error: function (a, b, c) {"
      "}"
      "});"
      "});"
      "</script>";
      "</div>";
    append_HTML_footer();
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", webpage);
  });
  

  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // flashing firmware to ESP
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  
  server.onNotFound(handleNotFound);   // If the user types something that is not supported, say so
  server.begin(); Serial.println(F("Webserver started...")); // Start the webserver
}

/*******************************************************************************
  HTML header
*******************************************************************************/
void append_HTML_header()
{
  webpage  = "";
  webpage += "<!DOCTYPE html><html lang=\"ru\" manifest=\"appcache.manifest\"><head>";
  webpage += "<script src=\"https://code.jquery.com/jquery-3.2.1.min.js\"></script>"; // AJAX data
  webpage += "<script src=\""+ visiobas +"/visiohome/module/js/visiohome-1.0.0.js\"></script>"; // visiohome js
  webpage += "<link href=\""+ visiobas +"/visiohome/module/css/visiohome-1.0.0.css\" rel=\"stylesheet\">"; // visiohome css
  webpage += "\n\
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>\n\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\n\
    <meta name=\"mobile-web-app-capable\" content=\"yes\" />\n";
  webpage += "<title>" + object_name + "</title>";
  webpage += "</head>";
  webpage += "<body>";
  webpage += "<div class='main'>";
}

/*******************************************************************************
  HTML footer
*******************************************************************************/
void append_HTML_footer()
{
  webpage += "</div></body></html>";
}
