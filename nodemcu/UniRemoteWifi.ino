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

void twilio_text(String body) {
  HTTPClient client;

  String url = "https://api.twilio.com/2010-04-01/Accounts/AC958ad4c79a2240ae5e25456aa84ac040/Messages.json?To=+18182161021&From=+13235242392"
                + "&Body=" + body;

  client.begin(url);
  client.setAuthorization("AC958ad4c79a2240ae5e25456aa84ac040", "e40c0f44f96ee07fb532a6f648523d15");

  int httpCode = client.sendRequest("POST");
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
    delay(1000);
  }
}
