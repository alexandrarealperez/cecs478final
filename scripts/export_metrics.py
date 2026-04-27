import json

data = {
    "total_packets": 20,
    "alerts": 1
}

with open("artifacts/release/metrics/results.json", "w") as f:
    json.dump(data, f, indent=2)