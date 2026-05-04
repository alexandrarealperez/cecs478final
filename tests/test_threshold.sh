#!/bin/bash
set -e

make build
mkdir -p artifacts/release/pcaps
python3 scripts/generate_pcaps.py

./nids artifacts/release/pcaps/test.pcap > /tmp/threshold_output.txt

if grep -q "Total packets" /tmp/threshold_output.txt; then
  echo "PASS: threshold test completed successfully"
else
  echo "FAIL: threshold test did not process packets"
  exit 1
fi