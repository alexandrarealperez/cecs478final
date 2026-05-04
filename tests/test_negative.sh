#!/bin/bash
set +e

make build >/dev/null 2>&1

./nids nonexistent.pcap >/dev/null 2>&1
status=$?

if [ $status -ne 0 ]; then
  echo "PASS: correctly handled nonexistent PCAP"
else
  echo "FAIL: expected error on nonexistent PCAP"
  exit 1
fi