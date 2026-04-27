# Architecture

The system is a lightweight Network Intrusion Detection System (NIDS) that processes PCAP files and detects suspicious traffic patterns.

## Components

- **Packet Capture**: Reads packet data from PCAP files using libpcap.
- **Parser**: Extracts relevant packet fields such as IP addresses, ports, and TCP flags.
- **Detector**: Applies rule-based logic to identify suspicious behavior (e.g., SYN-based traffic patterns).
- **Logger**: Records alerts and processing steps into log files.
- **Metrics Exporter**: Outputs summary statistics in JSON format.

## Data Flow

PCAP → Parser → Detector → Logger → Metrics Output

The system runs end-to-end inside a Docker container using: