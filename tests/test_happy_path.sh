#!/bin/bash
set -e

echo "[*] Running happy path test..."

make build >/dev/null 2>&1

mkdir -p artifacts/release/pcaps
mkdir -p artifacts/release/logs
mkdir -p artifacts/release/metrics

python3 scripts/generate_pcaps.py --count 50 >/dev/null 2>&1

./nids artifacts/release/pcaps/test.pcap tcp 10 > /tmp/happy_output.txt

if grep -q "Total packets processed" /tmp/happy_output.txt; then
    echo "PASS: Happy path processed packets successfully"
else
    echo "FAIL: Expected packet processing output not found"
    exit 1
fi