#!/bin/bash
set -e

echo "[*] Running threshold detection test..."

make build >/dev/null 2>&1

mkdir -p artifacts/release/pcaps
mkdir -p artifacts/release/logs
mkdir -p artifacts/release/metrics

python3 scripts/generate_pcaps.py --count 200 >/dev/null 2>&1

./nids artifacts/release/pcaps/test.pcap tcp 50 > /tmp/threshold_output.txt

if grep -q "ALERT" /tmp/threshold_output.txt; then
    echo "PASS: Threshold detection triggered successfully"
else
    echo "FAIL: Expected alert not triggered"
    exit 1
fi