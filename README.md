# NASA NEO MONITOR — Projeto IoT com ESP32 + Node-RED + API NASA

## Descrição do Projeto

O projeto **NASA NEO Monitor** foi desenvolvido com foco em prevenção de riscos utilizando dados reais da NASA sobre objetos próximos da Terra (**Near Earth Objects - NeoWs**).

A aplicação utiliza:

- API oficial da NASA
- ESP32 no Wokwi
- Dashboard em Node-RED
- Sensores e atuadores IoT
- Comunicação Wi-Fi
- API REST

O sistema monitora asteroides próximos da Terra em tempo real, exibindo informações no dashboard e acionando alertas físicos no ESP32 conforme o nível de risco detectado.

---

# Integrantes

- Nathan Gabriel Pires Machado — RM: XXXXX
- Integrante 2 — RM: XXXXX
- Integrante 3 — RM: XXXXX

---

# Tecnologias Utilizadas

## Hardware / IoT
- ESP32
- HC-SR04 (sensor ultrassônico)
- LCD I2C 16x2
- LEDs
- Botão PushButton

## Software
- Wokwi
- Node-RED
- API NASA NeoWs
- Arduino IDE (ambiente Wokwi)

---

# Arquitetura do Projeto

NASA NeoWs API
       ↓
Node-RED Dashboard
       ↓ HTTP POST
ESP32 (Wokwi)
       ↓
LCD + LEDs + Sensores

---

# Objetivo

Criar um sistema IoT capaz de:

- consumir dados reais da NASA
- monitorar asteroides próximos da Terra
- gerar alertas de risco
- exibir informações em dashboard
- controlar dispositivos físicos via ESP32

---

# Requisitos Atendidos

| Requisito | Implementação |
|---|---|
| Protótipo IoT | ESP32 no Wokwi |
| 2 Entradas | HC-SR04 + Botão |
| 2 Saídas | LED Verde + LED Vermelho |
| Interface Local | LCD I2C |
| Wi‑Fi | ESP32 conectado |
| API REST | Endpoints HTTP |
| Dashboard | Node-RED |
| JSON | Comunicação REST |
| Dados Reais | API NASA NeoWs |

---

# API Utilizada

API oficial da NASA:

https://api.nasa.gov/

Endpoint utilizado:

https://api.nasa.gov/neo/rest/v1/feed

---

# Endpoints REST do ESP32

## GET /status

Retorna informações atuais do sistema:

```json
{
  "asteroid": "(2008 QV11)",
  "risk": "SAFE",
  "distance": 18818979,
  "sensor_distance": 20,
  "button": 0
}
```

---

## POST /nasa-data

Recebe dados do Node-RED:

```json
{
  "asteroid":"(2008 QV11)",
  "distance":18818979,
  "risk":"SAFE"
}
```

---

# Dashboard

O dashboard foi desenvolvido no Node-RED e possui:

- Nome do asteroide
- Gauge de distância
- Gráfico histórico
- Monitoramento em tempo real
- Integração com API NASA

Acesso:

http://127.0.0.1:1880/ui

---

# Sensores e Atuadores

## Entradas

### HC-SR04
Simula a aproximação do asteroide.

### PushButton
Aciona alerta manual.

---

## Saídas

### LED Verde
Indica condição segura.

### LED Vermelho
Indica condição de perigo.

---

## Interface Local

### LCD I2C
Exibe:
- status do sistema
- risco detectado
- alertas

---

# Como Executar

## 1. Rodar o Wokwi
- Abrir projeto ESP32
- Iniciar simulação

---

## 2. Rodar o Node-RED

Iniciar o Node-RED:

```bash
node-red
```

---

## 3. Abrir Dashboard

http://127.0.0.1:1880/ui

---

## 4. Configurar API Key NASA

Gerar API Key gratuita:

https://api.nasa.gov/

---

# Estrutura do Projeto

project/

├── esp32/
│   ├── sketch.ino
│   ├── diagram.json
│   └── libraries.txt
│
├── node-red/
│   └── flows.json
│
└── README.md

---

# Vídeo Demonstrativo

Link do vídeo:



---

# Disciplina

Disruptive Architectures: IoT, IoB & Generative AI

---

# Instituição

FIAP

---

# Licença

Projeto acadêmico desenvolvido para fins educacionais.
