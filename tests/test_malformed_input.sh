#!/bin/bash
set +e

make build >/dev/null 2>&1

echo "bad data" > /tmp/bad.pcap
./nids /tmp/bad.pcap >/dev/null 2>&1
status=$?

if [ $status -ne 0 ]; then
  echo "PASS: correctly handled malformed PCAP"
else
  echo "FAIL: expected error on malformed PCAP"
  exit 1
fi