#!/bin/bash
set -e

make build
mkdir -p artifacts/release/pcaps
python3 scripts/generate_pcaps.py

./nids artifacts/release/pcaps/test.pcap > /tmp/happy_output.txt

if grep -q "Total packets" /tmp/happy_output.txt; then
  echo "PASS: happy path processed PCAP successfully"
else
  echo "FAIL: expected packet processing output"
  exit 1
fi