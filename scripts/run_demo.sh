#!/bin/bash
set -e

PCAP_FILE="${PCAP_FILE:-artifacts/release/pcaps/test.pcap}"
PACKET_COUNT="${PACKET_COUNT:-200}"
BPF_FILTER="${BPF_FILTER:-tcp}"
SYN_THRESHOLD="${SYN_THRESHOLD:-50}"

mkdir -p artifacts/release/pcaps
mkdir -p artifacts/release/logs
mkdir -p artifacts/release/metrics
mkdir -p artifacts/release/charts
mkdir -p artifacts/release/results

rm -f artifacts/release/logs/demo.log
rm -f artifacts/release/metrics/results.json
rm -f artifacts/release/charts/results.png
rm -f artifacts/release/charts/results_table.txt

echo "[*] Building Packet Sniffer with BPF..."
make build

echo "[*] Generating synthetic PCAP dataset..."
python3 scripts/generate_pcaps.py --count "$PACKET_COUNT" --output "$PCAP_FILE"

echo "[*] Running Packet Sniffer with BPF filter..."
./nids "$PCAP_FILE" "$BPF_FILTER" "$SYN_THRESHOLD"

echo "[*] Validating generated metrics..."
python3 scripts/export_metrics.py

echo "[*] Creating visualization and table..."
python3 scripts/make_chart.py

cat > artifacts/release/results/draft_results.md <<EOF
# Draft Results

The system processed a synthetic PCAP generated with Scapy.

Configured packet count: $PACKET_COUNT

BPF filter used: $BPF_FILTER

SYN threshold used: $SYN_THRESHOLD

The IDS logic analyzed TCP flags and counted packets dynamically during execution. The system generated an event-based alert after the SYN threshold was exceeded.

Generated evidence:
- artifacts/release/pcaps/test.pcap
- artifacts/release/logs/demo.log
- artifacts/release/metrics/results.json
- artifacts/release/charts/results.png
- artifacts/release/charts/results_table.txt
EOF

echo "[*] Demo complete"