#!/bin/bash

set -e

mkdir -p artifacts/release/pcaps
mkdir -p artifacts/release/logs
mkdir -p artifacts/release/metrics
mkdir -p artifacts/release/charts
mkdir -p artifacts/release/results

echo "[*] Building packet sniffer..."
make build

echo "[*] Generating PCAP..."
python3 scripts/generate_pcaps.py

echo "[*] Running packet sniffer..."
./nids artifacts/release/pcaps/test.pcap > artifacts/release/logs/demo.log

echo "[*] Exporting metrics..."
python3 scripts/export_metrics.py

echo "[*] Creating chart..."
python3 scripts/make_chart.py

echo "[*] Demo complete"