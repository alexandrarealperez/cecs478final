# Architecture

This project implements a packet sniffer with BPF packet analysis, extended into a lightweight network intrusion system. The system processes PCAP files and analyzes packet level traffic to identify suspicious patterns.

The system begins by reading packet data from PCAP files using the libpcap library. A parser extracts relevant fields such as IP addresses, port numbers, and TCP flags. This information is then passed to the detection module, which applies rule based logic to identify suspicious traffic patterns, including SYN-based activity.

When potential threats are identified, a logging component records alerts and key processing steps. In parallel, a metrics exporter produces summary statistics in JSON format, and a visualization step generates charts to support evaluation.

The overall data flow follows a structured pipeline: PCAP input is parsed, analyzed, logged, and summarized through metrics and visual outputs. The system runs end-to-end within a Docker container using a single command sequence.