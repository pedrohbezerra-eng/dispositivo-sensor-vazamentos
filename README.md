# Detector de Gás MQ-2 Arduino

Sistema automático de detecção de gases inflamáveis que calibra o ambiente limpo na inicialização e dispara alarmes quando detecta concentrações perigosas de gás.

## 📋 Componentes Necessários

### Obrigatórios
- Arduino Uno/Nano/Mega
- Sensor de gás MQ-2
- Buzzer ativo
- Resistores 220Ω (se necessário)
- Protoboard/jumpers

### Opcionais (melhoram a funcionalidade)
- Display LCD 16x2 com módulo I2C
- LED indicador
- Módulo relé (para automação)
- Fonte de alimentação externa 12V (para o sensor)

## 🔌 Esquema de Ligação

### Ligações Principais
```
MQ-2:
  VCC → 5V Arduino
  GND → GND Arduino
  A0  → Pino A0 Arduino

Buzzer:
  (+) → Pino 9 Arduino
  (-) → GND Arduino
```

### Ligações Opcionais
```
LCD I2C:
  VCC → 5V Arduino
  GND → GND Arduino
  SDA → A4 Arduino (Uno/Nano)
  SCL → A5 Arduino (Uno/Nano)

LED:
  Ânodo (+) → Pino 8 Arduino
  Cátodo (-) → Resistor 220Ω → GND

Relé:
  VCC → 5V Arduino
  GND → GND Arduino
  IN  → Pino 7 Arduino
```

## 📚 Bibliotecas Necessárias

Instale via Arduino IDE:
1. **Wire.h** (já incluída no Arduino IDE)
2. **LiquidCrystal_I2C** (apenas se usar LCD)
   - Sketch → Include Library → Manage Libraries
   - Busque por "LiquidCrystal I2C" → Install

## 🚀 Como Usar

### 1. Upload do Código
- Conecte o Arduino ao computador
- Abra o Arduino IDE
- Cole o código fornecido
- Selecione placa e porta corretas
- Faça upload

### 2. Primeira Inicialização
1. **Aquecimento (45s)**: Sensor aquece automaticamente
2. **Calibração**: Sistema define baseline do ar limpo
3. **Funcionamento**: Monitoramento contínuo inicia

### 3. Interpretando os Resultados

**Com LCD:**
- `GAS: [valor]` - Leitura atual do sensor
- `T: [limite]` - Threshold calculado (baseline + 100)

**Sem LCD:**
- Buzzer silencioso = Ar normal
- Buzzer tocando = Gás detectado

## ⚙️ Configuração

### Parâmetros Ajustáveis (no código):
```cpp
const int THRESHOLD_OFFSET = 100;  // Sensibilidade (padrão: 100)
const unsigned long WARMUP_TIME_MS = 45000;  // Tempo aquecimento (45s)
```

- **THRESHOLD_OFFSET**: Aumente para menos sensível, diminua para mais sensível
- **WARMUP_TIME_MS**: Tempo de aquecimento do sensor (recomendado: 30-60s)

## 🔧 Troubleshooting

### Problemas Comuns

**Sensor sempre em alarme:**
- Verifique se há gases no ambiente durante calibração
- Calibre em ambiente com ar limpo
- Ajuste THRESHOLD_OFFSET para valor maior

**Sensor nunca alarma:**
- Verifique conexões do MQ-2
- Teste com isqueiro (sem acender) próximo ao sensor
- Diminua THRESHOLD_OFFSET

**LCD não funciona:**
- Verifique endereço I2C (padrão: 0x27)
- Teste outros endereços: 0x3F, 0x20
- Verifique conexões SDA/SCL

**Buzzer não toca:**
- Verifique se é buzzer ativo (não passivo)
- Teste ligação direta no pino
- Verifique polaridade

### Testando o Sistema
1. **Teste de Gás**: Aproxime isqueiro (sem acender) do sensor
2. **Teste de Álcool**: Use álcool gel próximo ao sensor
3. **Verificação**: Alarme deve ativar em 1-2 segundos

## ⚠️ Avisos Importantes

- **Calibração**: Sempre calibre em ambiente com ar limpo
- **Aquecimento**: Não interrompa o período de aquecimento
- **Ventilação**: Use em local ventilado durante testes
- **Alimentação**: Sensor pode consumir até 150mA
- **Precisão**: Este é um projeto educacional, não substitui detectores comerciais

## 🛠️ Melhorias Possíveis

- Adicionar comunicação WiFi/Bluetooth
- Implementar log de dados em SD card
- Criar interface web para monitoramento
- Adicionar mais tipos de sensores
- Implementar diferentes níveis de alarme

## 📞 Suporte

Para dúvidas sobre o código ou montagem, abra uma issue no repositório com:
- Descrição do problema
- Fotos da montagem (se possível)
- Mensagens de erro (se houver)
