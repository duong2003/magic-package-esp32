#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

const char* broadcastAddress = "192.168.1.255"; // Broadcast address of your network
const int wolPort = 9; // Default WOL port

// MAC address of the target device
uint8_t mac[] = {0x30, 0x9C, 0x23, 0xB0, 0x4A, 0x22};

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  sendWOLPacket();
  delay(5000); // Send the WOL packet every 5 seconds
}

void sendWOLPacket() {
  // Create a UDP object
  WiFiUDP udp;
  
  // Open UDP connection to the broadcast address and WOL port
  if (udp.beginPacket(broadcastAddress, wolPort)) {
    Serial.println("Sending WOL packet...");
    
    // Write the magic packet data to the UDP packet
    udp.write(0xFF);
    for (int i = 0; i < 15; i++) {
      udp.write(mac, 6);
    }
    
    // Send the UDP packet
    udp.endPacket();
    Serial.println("WOL packet sent!");
  } else {
    Serial.println("Failed to send WOL packet!");
  }
}
