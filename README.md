Current version: 1
Commands:
- Health: 0
- Alarm: 1
- Set Threshold: 16
- Set Period: 17
- Reset Alarm: 18

```mermaid
---
title: "Generic SFFA Packet"
---
packet
0-3: "Version"
4-7: "Command"
8-103: "Data"
```
