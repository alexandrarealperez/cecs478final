#!/bin/bash
set +e

echo "[*] Running negative input test..."

make build >/dev/null 2>&1

./nids nonexistent.pcap tcp 10 >/dev/null 2>&1
status=$?

if [ $status -ne 0 ]; then
    echo "PASS: Correctly handled nonexistent PCAP file"
else
    echo "FAIL: Expected error for nonexistent PCAP"
    exit 1
fi