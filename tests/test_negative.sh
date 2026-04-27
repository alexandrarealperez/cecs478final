#!/bin/bash

./nids nonexistent.pcap 2>/dev/null

if [ $? -ne 0 ]; then
  echo "PASS"
else
  echo "FAIL"
  exit 1
fi