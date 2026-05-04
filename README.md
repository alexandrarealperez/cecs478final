# Packet Sniffer with BPF 

##Project Report

https://docs.google.com/document/d/17GoSU_xFhZI35RHVpV0fs1DXtS-hihpQRz_ZIwLjPtQ/edit?usp=sharing 

## Overview
This project implements a packet sniffer using libpcap, and extends into a lightweight network intrusion detection system. The system processes PCAP files to analyze packet level traffic and detect suspicious patterns, such as SYN-based activity.

The system generates logs, metrics, and charts to support evaluation. All execution occurs inside a Docker container for a consistent environment.

## Features
- Packet inspection using libpcap
- Extraction of IP addresses, ports, and TCP flags
- Rule based detection of suspicious traffic patterns
- Metrics export
- Chart based visualization
- Docker based reproducibility
- Automated testing 



## Start

```bash
make up && make demo

# Goals
- Capture network packets using libpcap
- Detect basic attack patterns (port scans, SYN floods)
- Log alerts for suspicious activity

# Setup

# One-command bootstrap
```bash
make bootstrap
