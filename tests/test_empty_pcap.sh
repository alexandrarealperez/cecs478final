#!/bin/bash
set +e

echo "[*] Running empty PCAP test..."

make build >/dev/null 2>&1

touch /tmp/empty.pcap

./nids /tmp/empty.pcap tcp 10 >/dev/null 2>&1
status=$?

if [ $status -ne 0 ]; then
    echo "PASS: Correctly handled empty PCAP"
else
    echo "FAIL: Expected error for empty PCAP"
    exit 1
fi