#!/bin/bash

./nids artifacts/release/pcaps/test.pcap > output.txt

if grep -q "Total packets" output.txt; then
  echo "PASS"
else
  echo "FAIL"
  exit 1
fi