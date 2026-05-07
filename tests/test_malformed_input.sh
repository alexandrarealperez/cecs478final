#!/bin/bash
set +e

echo "[*] Running malformed input test..."

make build >/dev/null 2>&1

echo "bad data" > /tmp/bad.pcap

./nids /tmp/bad.pcap tcp 10 >/dev/null 2>&1
status=$?

if [ $status -ne 0 ]; then
    echo "PASS: Correctly handled malformed PCAP"
else
    echo "FAIL: Expected error for malformed PCAP"
    exit 1
fi