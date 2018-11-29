#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define SPOTIFY_AUTHORIZATION_TOKEN "Bearer BQBjNHBuDTdjlcVi_yKOwK__QKvcYSoqUbbVN_ZDjYHtmOiBAkDDZiNBB7nd0TfKyCf4mBDIuFuU2aaeQvxHbcS6k4M4an24gRgXrfSu13RkF6QGnh9gtFQOrgvtiCwlLq0Eda0RJNsn1-JW-7LgkpN6aiBb"

// easily get fingerprints with https://www.grc.com/fingerprints.htm
#define SPOTIFY_FINGERPRINT "AB:BC:7C:9B:7A:D8:5D:98:8B:B2:72:A4:4C:13:47:9A:00:2F:70:B5"

const char* ssid = "Patrick's Fone";
const char* pass = "patrickstar";

bool isPlaying = false;

void spotify_play() {
  HTTPClient client;

  client.begin("https://api.spotify.com/v1/me/player/play", String(SPOTIFY_FINGERPRINT));

  client.addHeader("Accept", "application/json");
  client.addHeader("Content-Type", "application/json");
  client.addHeader("Content-Length", "0");
  client.addHeader("Authorization", SPOTIFY_AUTHORIZATION_TOKEN);

  int httpCode = client.sendRequest("PUT");
  Serial.write(httpCode);
}

void spotify_pause() {
  HTTPClient client;

  client.begin("https://api.spotify.com/v1/me/player/pause", String(SPOTIFY_FINGERPRINT));

  client.addHeader("Accept", "application/json");
  client.addHeader("Content-Type", "application/json");
  client.addHeader("Content-Length", "0");
  client.addHeader("Authorization", SPOTIFY_AUTHORIZATION_TOKEN);

  int httpCode = client.sendRequest("PUT");
  Serial.println(String(httpCode));
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting");
  }  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    int incomingByte;
    if (Serial.available()) {
      incomingByte = Serial.read();
    }

    switch(incomingByte) {
        case 5:
          spotify_pause();
          break;
    }

    

    
//    if (!isPlaying) {
//      spotify_play();
//      isPlaying = true;
//      Serial.println("Unpaused");
//    }
//    else {
//      spotify_pause();
//      isPlaying = false;
//      Serial.println("Paused");
//    }
    delay(1000);
  }
}
