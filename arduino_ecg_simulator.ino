/*
 * ECG MONITOR - Arduino Simulator
 * Simula señal ECG con 6 derivadas + marcapasos
 * Compatible con backend Node.js
 * 
 * Derivadas:
 * 1: I (Limb Lead I)
 * 2: II (Limb Lead II) 
 * 3: III (Limb Lead III)
 * 4: aVR (Augmented Vector Right)
 * 5: aVL (Augmented Vector Left)
 * 6: aVF (Augmented Vector Foot)
 * 
 * Baudrate: 115200
 */

// ============ CONFIGURACIÓN ============

#define BAUD_RATE 115200
#define ECG_SAMPLE_RATE 250  // Muestras por segundo (250 Hz = cada 4ms)
#define HEART_RATE_BASE 72   // BPM base
#define MARCAPASOS_CHANCE 0.05  // 5% de probabilidad de evento de marcapasos

// ============ VARIABLES GLOBALES ============

unsigned long lastSampleTime = 0;
unsigned long lastPacketTime = 0;
const unsigned long PACKET_INTERVAL = 40;  // Enviar cada 40ms (25 packets/seg)

float ecgPhase = 0.0;
int currentDerivada = 1;  // Derivada activa (1-6)
bool ecgRunning = true;   // ¿ECG en ejecución?
bool autoMode = true;     // Modo automático de derivadas
unsigned int packetCount = 0;
float heartRate = HEART_RATE_BASE;
float derivadaChangeTimer = 0.0;  // Timer para cambiar derivadas en auto mode

// Mapeo de derivadas
const char* derivadaNames[] = {"", "I", "II", "III", "aVR", "aVL", "aVF"};

// ============ FUNCIONES ECG SIMULADO ============

/**
 * Genera forma de onda ECG realista basada en fase del ciclo cardíaco
 * Simula componentes PQRST
 */
float generateECGWave(float phase, int derivada) {
  // Normalizar fase a [0, 1]
  float p = fmod(phase, 1.0);
  
  // Amplitudes y características diferentes por derivada
  float amplitude = 1.0;
  float offset = 0.0;
  
  switch(derivada) {
    case 1:  // I - normal
      amplitude = 0.8;
      break;
    case 2:  // II - máxima amplitud
      amplitude = 1.2;
      break;
    case 3:  // III - amplitud media-baja
      amplitude = 0.6;
      break;
    case 4:  // aVR - invertida (negativa)
      amplitude = -0.9;
      break;
    case 5:  // aVL - media-alta
      amplitude = 0.95;
      break;
    case 6:  // aVF - similar a II
      amplitude = 1.15;
      offset = 0.1;
      break;
  }
  
  float wave = 0.0;
  
  // Onda P (atrial depolarization) - 0.0 a 0.1
  if (p < 0.1) {
    wave += 0.3 * sin((p - 0.05) * M_PI / 0.1) * amplitude;
  }
  
  // Segmento PR - 0.1 a 0.15
  if (p >= 0.1 && p < 0.15) {
    wave += 0.0;  // Línea de base
  }
  
  // Complejo QRS (ventricularización) - 0.15 a 0.35
  if (p >= 0.15 && p < 0.35) {
    float qrs_pos = (p - 0.15) / 0.2;
    if (qrs_pos < 0.25) {
      // Q wave
      wave += -0.4 * sin(qrs_pos * M_PI / 0.25) * amplitude;
    } else if (qrs_pos < 0.5) {
      // R wave (pico principal)
      float r_pos = (qrs_pos - 0.25) / 0.25;
      wave += 1.5 * sin(r_pos * M_PI) * amplitude;
    } else if (qrs_pos < 0.75) {
      // S wave
      float s_pos = (qrs_pos - 0.5) / 0.25;
      wave += -0.5 * sin(s_pos * M_PI / 0.25) * amplitude;
    } else {
      // Retorno a línea base
      wave += 0.2 * sin((qrs_pos - 0.75) * M_PI / 0.25) * amplitude;
    }
  }
  
  // Segmento ST - 0.35 a 0.5
  if (p >= 0.35 && p < 0.5) {
    wave += 0.05 * sin((p - 0.35) * M_PI / 0.15) * amplitude;
  }
  
  // Onda T (ventricular repolarization) - 0.5 a 0.75
  if (p >= 0.5 && p < 0.75) {
    float t_pos = (p - 0.5) / 0.25;
    wave += 0.7 * sin(t_pos * M_PI) * amplitude;
  }
  
  // Retorno a línea base - 0.75 a 1.0
  if (p >= 0.75) {
    wave += 0.0;  // Línea de base
  }
  
  // Añadir ruido fisiológico
  float noise = (random(0, 20) - 10) * 0.02;
  
  // Convertir a rango ADC 0-1023 (simulado aquí como 0-100 para visualización)
  return constrain((wave + 50.0 + offset) * 0.8 + noise, 10, 90);
}

/**
 * Calcula BPM aproximado basado en fase
 */
int calculateBPM() {
  return (int)heartRate;
}

/**
 * Detecta evento de marcapasos aleatoriamente
 */
bool checkMarcapasos() {
  if (ecgPhase < 0.02) {  // Solo en el inicio del ciclo
    return random(0, 100) < (MARCAPASOS_CHANCE * 100);
  }
  return false;
}

/**
 * Cambia a siguiente derivada (modo auto)
 */
void changeDerivada() {
  currentDerivada++;
  if (currentDerivada > 6) {
    currentDerivada = 1;
  }
}

// ============ MANEJO DE COMANDOS ============

void handleCommand(char cmd) {
  switch(cmd) {
    // Control ECG
    case 'e':
    case 'E':
      ecgRunning = true;
      Serial.println("ACK,ECG_ON");
      break;
      
    case 's':
    case 'S':
      ecgRunning = false;
      Serial.println("ACK,ECG_OFF");
      break;
    
    // Modo automático
    case 'a':
    case 'A':
      autoMode = true;
      Serial.println("ACK,AUTO_ON");
      Serial.print("AUTO,DERIVADA,");
      Serial.println(derivadaNames[currentDerivada]);
      break;
    
    // Modo manual
    case 'm':
    case 'M':
      autoMode = false;
      Serial.println("ACK,MANUAL_ON");
      break;
    
    // Seleccionar derivada (1-6)
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
      currentDerivada = cmd - '0';  // Convertir char a int
      autoMode = false;
      Serial.print("ACK,DERIVADA,");
      Serial.println(derivadaNames[currentDerivada]);
      break;
    
    // Query
    case 'q':
    case 'Q':
    case '?':
      Serial.print("STATUS: Derivada=");
      Serial.print(derivadaNames[currentDerivada]);
      Serial.print(" Mode=");
      Serial.print(autoMode ? "AUTO" : "MANUAL");
      Serial.print(" Running=");
      Serial.println(ecgRunning ? "YES" : "NO");
      break;
    
    default:
      // Ignorar comandos desconocidos silenciosamente
      break;
  }
}

// ============ SETUP ============

void setup() {
  Serial.begin(BAUD_RATE);
  delay(1000);
  
  // Mensaje de bienvenida
  Serial.println("READY");
  Serial.println("STATUS: ECG Simulator v1.0 - Starting");
  
  randomSeed(analogRead(A0));  // Inicializar generador de números aleatorios
  
  lastSampleTime = millis();
  lastPacketTime = millis();
}

// ============ LOOP PRINCIPAL ============

void loop() {
  unsigned long now = millis();
  
  // -------- Leer comandos del serial --------
  if (Serial.available() > 0) {
    char inChar = Serial.read();
    
    // Ignorar caracteres de control y espacios
    if (inChar != '\n' && inChar != '\r' && inChar != ' ') {
      handleCommand(inChar);
    }
  }
  
  // -------- Generar y enviar datos ECG --------
  if (ecgRunning) {
    unsigned long elapsed = now - lastPacketTime;
    
    if (elapsed >= PACKET_INTERVAL) {
      lastPacketTime = now;
      
      // Calcular fase basada en BPM
      // 1 ciclo completo = 60/BPM segundos
      float cycleDuration = 60000.0 / heartRate;  // En milisegundos
      ecgPhase += (float)PACKET_INTERVAL / cycleDuration;
      
      // Modo automático: cambiar derivada cada 8 ciclos
      if (autoMode) {
        derivadaChangeTimer += (float)PACKET_INTERVAL / cycleDuration;
        if (derivadaChangeTimer >= 7.0) {
          changeDerivada();
          derivadaChangeTimer = 0.0;
          Serial.print("AUTO,DERIVADA,");
          Serial.println(derivadaNames[currentDerivada]);
        }
      }
      
      // Generar valor ECG
      float ecgValue = generateECGWave(ecgPhase, currentDerivada);
      int bpm = calculateBPM();
      
      // Checklist marcapasos
      int mp = checkMarcapasos() ? 1 : 0;
      
      // Emitir evento marcapasos
      if (mp == 1) {
        Serial.println("EVENT,MP");
      }
      
      // Enviar datos en formato esperado
      Serial.print("DATA,");
      Serial.print((int)ecgValue);
      Serial.print(",");
      Serial.print(derivadaNames[currentDerivada]);
      Serial.print(",");
      Serial.print(bpm);
      Serial.print(",");
      Serial.println(mp);
      
      packetCount++;
      
      // Simular variabilidad de ritmo cardíaco (cambios lentos)
      if (random(0, 100) < 2) {  // 2% de probabilidad
        heartRate += random(-2, 3);  // +/- 2 BPM cambio aleatorio
        heartRate = constrain(heartRate, 40, 150);  // Mantener rango fisiológico
      }
    }
  }
}
