// Biblioteca utilizada para armazenar dados na memória de programa
#include <avr/pgmspace.h>

// Biblioteca utilizada para substituir micros() do Arduino por uma funçao com precisão de 1 uS
#include "time.h"

// Biblioteca utilizada para manipulação de bits
#include "bits.h"

// Seleciona a musica a ser tocada do arquivo musicas.h
#define MUSICA 8

// Carrega a musica selecionada
#include "musicas.h"

// Grava os valores em microsegundos do período das notas musicais, a primeira nota é núla (não toca nada) e a primeira é Sí (NOTE_B0) seguida de Dó (NOTE_C1)
PROGMEM prog_uint16_t NOTES[] = {0, 16129, 15152, 14286, 13514, 12821, 12195, 11364, 10870, 10204, 9615, 9091, 8621, 8065, 7692, 7246, 6849, 6410, 6098, 5747, 5376, 5102, 4808, 4545, 4274, 4065, 3817, 3597, 3401, 3205, 3030, 2857, 2703, 2551, 2404, 2273, 2146, 2024, 1908, 1805, 1701, 1608, 1515, 1433, 1351, 1276, 1205, 1136, 1073, 1012, 956, 903, 852, 804, 759, 716, 676, 638, 602, 568, 536, 506, 478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253, 239, 226, 213, 201, 190, 179, 169, 159, 151, 142, 134, 127, 119, 113, 106, 100 };

// As variáveis que armazenam o período da nota que está sendo tocada (em uS)
unsigned int channel1 = 0;
unsigned int channel2 = 0;
unsigned int channel3 = 0;

// Armazena o tempo em uS atual
unsigned long currentTimeMicros = 0;

// Variáveis para armazenar o tempo do último acionamento do timer (neste caso de 1 a 4)
unsigned long timer1 = currentTimeMicros;
unsigned long timer2 = currentTimeMicros;
unsigned long timer3 = currentTimeMicros;
unsigned long timer4 = currentTimeMicros;
boolean timer5_enabled = true;

// Variáveis de estado da trilha 1
unsigned int pos1 = 0;
uint32_t track1NextEvent = 0;
uint8_t note1 = 0;

// Variáveis de estado da trilha 2
unsigned int pos2 = 0;
uint32_t track2NextEvent = 0;
uint8_t note2 = 0;

// Variáveis de estado da trilha 3
unsigned int pos3 = 0;
uint32_t track3NextEvent = 0;
uint8_t note3 = 0;


// Posição geral dentro da música MIDI
uint32_t midiPosition = 0;

void setup() {
  // Estas variaveis foram postas aqui por que o compilador não deixa inicializa-las fora de uma função

  track1NextEvent = pgm_read_dword_near(track1_tempo);
  track2NextEvent = pgm_read_dword_near(track2_tempo);
  track3NextEvent = pgm_read_dword_near(track3_tempo);
  
  // Inicia o timer 2 e os pinos pra saidas
  Time.begin();
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}


void loop() { 
  currentTimeMicros = Time.micros();
  if( channel1 != 0 and (currentTimeMicros - timer1 >= channel1))
  {
    bit_invert(PORTB, PB1);
    timer1 = currentTimeMicros;
  }
  if( channel2 != 0 and (currentTimeMicros - timer2 >= channel2))
  {
    bit_invert(PORTB, PB2);
    timer2 = currentTimeMicros;
  }
  if( channel3 != 0 and (currentTimeMicros - timer3 >= channel3))
  {
    bit_invert(PORTB, PB3);
    timer3 = currentTimeMicros;
  }  

  if(currentTimeMicros - timer4 >= midi_bpm) {
    midiPosition++;
    timer4 = currentTimeMicros;
  }

  if(midiPosition == track1NextEvent) {
    if(midiPosition < track1_size) {
      note1 = pgm_read_word_near(track1_music + pos1);
      channel1 = pgm_read_word_near( NOTES + note1 );
      pos1++;
      track1NextEvent = pgm_read_dword_near(track1_tempo + pos1);
    } else {
      channel1 = 0;
    }
  }

  if(midiPosition == track2NextEvent) {
    if(midiPosition < track2_size) {
      note2 = pgm_read_word_near(track2_music + pos2);
      channel2 = pgm_read_word_near( NOTES + note2 );
      pos2++;
      track2NextEvent = pgm_read_dword_near(track2_tempo + pos2);
    } else {
      channel2 = 0;
    }
  }

  if(midiPosition == track3NextEvent) {
    if(midiPosition < track3_size) {
      note3 = pgm_read_word_near(track3_music + pos3);
      channel3 = pgm_read_word_near( NOTES + note3 );
      pos3++;
      track3NextEvent = pgm_read_dword_near(track3_tempo + pos3);
    } else {
      channel3 = 0;
    }
  }
