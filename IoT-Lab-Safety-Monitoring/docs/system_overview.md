# System Overview

## Alert Priority Logic

| Priority | Condition            | LED    | Buzzer | LCD Message       |
|----------|----------------------|--------|--------|-------------------|
| 1        | Fire detected        | 🔴 Red   | ON     | FIRE ALERT!       |
| 2        | Gas level > 2500     | 🟡 Yellow | ON    | GAS LEAKAGE!      |
| 3        | Equipment moved >10cm| 🔵 Blue  | ON     | EQUIP MOVED       |
| –        | All normal           | 🟢 Green | OFF   | Temp / Hum / Gas  |

## ThingSpeak Fields

| Field   | Data              |
|---------|-------------------|
| Field 1 | Temperature (°C)  |
| Field 2 | Humidity (%)      |
| Field 3 | Gas Level         |
| Field 4 | Distance (cm)     |
| Field 5 | Alert Status      |

## Data Flow
