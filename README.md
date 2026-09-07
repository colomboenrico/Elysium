Space Station Elysium

Simulatore di una stazione spaziale ad anello, con motore di simulazione in **C++** e una dashboard web in stile **mission control** che mostra la telemetria in tempo reale. Tutto il sistema gira in **Docker Compose**: un container esegue la simulazione, l'altro serve l'interfaccia web comunicano tra loro tramite un volume condiviso.

![Station banner](web/static/station.png)

## Cosa fa

Ogni tick della simulazione aggiorna lo stato della stazione: ossigeno, acqua, energia, cibo, crediti, morale della popolazione ed efficienza dei pannelli solari. Diversi sistemi interagiscono tra loro — i pannelli solari alimentano l'energia, i generatori d'ossigeno e i riciclatori d'acqua mantengono l'equipaggio in vita, le fattorie producono cibo, parchi e centri ricreativi aumentano il morale, e l'economia genera crediti in base alla popolazione. Eventi casuali (meteoriti, guasti ai sistemi vitali, tempeste solari, arrivo di nuovi coloni) tengono la situazione dinamica.

Un **sistema esperto basato su regole** (`AdvisorSystem`) analizza lo stato della stazione a ogni tick e restituisce un consiglio prioritario  ad esempio segnala scorte critiche prima ancora che diventino un problema, o suggerisce di investire i crediti in eccesso.

Dalla dashboard è possibile costruire nuove infrastrutture (pannelli solari, fattorie, riciclatori d'acqua, generatori d'ossigeno, parchi, appartamenti di lusso, centri d'intrattenimento) spendendo i crediti accumulati: il comando viene scritto dal server web, letto dalla simulazione C++ al tick successivo, ed eseguito se ci sono fondi sufficienti.

## Dashboard

- Gauge segmentati in stile mission control per ossigeno, acqua, energia e cibo, con mini-grafici storici (sparkline)
- Pannello "Onboard AI" con il messaggio dell'advisor e stato colonia/infrastrutture aggiornati in tempo reale
- Pannello di costruzione con 7 tipi di strutture acquistabili
- Log eventi con storico degli ultimi accadimenti
- Overlay grafico sull'illustrazione della stazione: ogni struttura costruita illumina il relativo nodo con un'animazione, per vedere a colpo d'occhio cosa è stato aggiunto alla stazione

## Architettura

```
┌──────────────────────┐            ┌──────────────────────┐
│ sim (C++)            │            │ web (Flask)          │
│                      │            │                      │
│ SimulationEngine     │            │ /api/state           │
│ scrive state.json    │   volume   │ /api/events          │
│ legge command.txt    │            │ /api/build (POST)    │
│                      │            │ serve la dashboard   │
└──────────────────────┘            └──────────────────────┘
```

I due container comunicano tramite un volume Docker condiviso (`simdata`), senza bisogno di un protocollo di rete dedicato:

- `state.json` — snapshot completo dello stato, scritto in modo atomico (file temporaneo + rename) a ogni tick
- `events.log` — log append-only in formato JSON-lines degli eventi della simulazione
- `command.txt` — comando di costruzione in attesa, scritto dal server web e consumato dalla simulazione

## Stack tecnico

- **C++** — motore di simulazione, build multi-stage con Docker (`gcc:13` per la build, `debian:bookworm-slim` per il runtime, linking statico di libstdc++)
- **Python / Flask** — API REST che espone lo stato della simulazione al frontend
- **HTML/CSS/JS ** — dashboard, grafici disegnati su `<canvas>` senza librerie esterne
- **Docker Compose** — orchestrazione dei due servizi

## Avvio

```bash
docker compose up --build
```

La dashboard è disponibile su [http://localhost:8080](http://localhost:8080).

## Struttura del progetto

```
SpaceStationSim/     # motore di simulazione C++ (progetto Xcode)
web/                 # server Flask + dashboard
docker-compose.yml   # orchestrazione dei due servizi
```
