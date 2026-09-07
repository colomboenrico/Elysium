import json
import os
from flask import Flask, jsonify, render_template, request

app = Flask(__name__)
STATE_PATH = "/data/state.json"
COMMAND_PATH = "/data/command.txt"
EVENTS_PATH = "/data/events.log"

BUILD_TYPES = {"solar", "farm", "water", "oxygen", "park", "luxury", "entertainment"}


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/api/state")
def api_state():
    if not os.path.exists(STATE_PATH):
        return jsonify({"error": "not_ready"}), 503
    try:
        with open(STATE_PATH) as f:
            data = json.load(f)
    except (json.JSONDecodeError, OSError):
        # il simulatore stava scrivendo il file proprio in questo istante,
        # riprovare al prossimo aggiornamento della pagina
        return jsonify({"error": "not_ready"}), 503
    return jsonify(data)


@app.route("/api/events")
def api_events():
    if not os.path.exists(EVENTS_PATH):
        return jsonify([])
    events = []
    try:
        with open(EVENTS_PATH) as f:
            lines = f.readlines()[-25:]
    except OSError:
        return jsonify([])
    for line in lines:
        line = line.strip()
        if not line:
            continue
        try:
            events.append(json.loads(line))
        except json.JSONDecodeError:
            continue
    events.reverse()
    return jsonify(events)


@app.route("/api/build", methods=["POST"])
def api_build():
    data = request.get_json(silent=True) or {}
    build_type = data.get("type", "")
    if build_type not in BUILD_TYPES:
        return jsonify({"error": "invalid_type"}), 400
    with open(COMMAND_PATH, "w") as f:
        f.write(build_type)
    return jsonify({"ok": True})


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
