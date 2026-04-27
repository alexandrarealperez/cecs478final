# Architecture

The system is a lightweight Network Intrusion Detection System (NIDS) designed to process PCAP files and identify suspicious traffic patterns. It operates as a modular pipeline where each component is responsible for a specific stage of packet analysis.

The process begins with packet capture, where network traffic is read from PCAP files using the libpcap library. The parser then extracts relevant information from each packet, including IP addresses, port numbers, and TCP flags. This parsed data is passed to the detection component, which applies rule-based logic to identify suspicious behaviors such as SYN-based traffic patterns.

When potential threats are detected, the logger records alerts and key processing steps into log files. In addition to logging, the system includes a metrics exporter that generates summary statistics in JSON format, providing a structured overview of the analysis results.

Overall, the data flow follows a straightforward pipeline: PCAP input is processed by the parser, analyzed by the detector, logged by the system, and summarized through metrics output. The entire system runs end-to-end within a Docker container and can be executed using a single command sequence.