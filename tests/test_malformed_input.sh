#!/bin/bash

echo "bad data" > bad.pcap
./nids bad.pcap
echo "PASS"