#!/bin/bash
set +e

make build >/dev/null 2>&1

touch /tmp/empty.pcap
./nids /tmp/empty.pcap >/dev/null 2>&1
status=$?

if [ $status -ne 0 ]; then
  echo "PASS: correctly handled empty PCAP"
else
  echo "FAIL: expected error on empty PCAP"
  exit 1
fi