#include <Wire.h>
#include <SPI.h>
#include <U8g2lib.h>

// Definições dos pinos SPI para o SH1106
#define OLED_DC 8
#define OLED_CS 10
#define OLED_RESET 9

// Inicializa o display no modo SPI
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);

#define BUTTON_PIN 2

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("Iniciando OLED SH1106...");

    u8g2.begin();
    u8g2.clearBuffer();
    
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(10, 20, "Gerador de Dezenas");
    u8g2.drawStr(10, 30, "da Mega Sena!");
    u8g2.drawStr(10, 40, "Pressione o botao!");
    u8g2.sendBuffer();
    
    delay(2000);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        gerarNumerosMegaSena();
        delay(500); // Evita leituras repetidas do botão
    }
}

void gerarNumerosMegaSena() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(10, 10, "Numeros Sorteados:");
    
    int numeros[6];
    bool repetido;
    
    for (int i = 0; i < 6; i++) {
        do {
            repetido = false;
            numeros[i] = random(1, 61);
            
            for (int j = 0; j < i; j++) {
                if (numeros[i] == numeros[j]) {
                    repetido = true;
                    break;
                }
            }
        } while (repetido);
    }
    
    // Coordenadas para os círculos
    int posicoes[6][2] = {{20, 20}, {50, 20}, {80, 20}, {20, 50}, {50, 50}, {80, 50}};
    
    // Exibir números dentro de círculos
    for (int i = 0; i < 6; i++) {
        u8g2.drawCircle(posicoes[i][0], posicoes[i][1], 10, U8G2_DRAW_ALL);
        u8g2.setCursor(posicoes[i][0] - 6, posicoes[i][1] + 3);
        u8g2.print(numeros[i]);
    }
    
    u8g2.sendBuffer();
}
