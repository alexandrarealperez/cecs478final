# Draft Results

The system processed a synthetic PCAP generated with Scapy.

Configured packet count: 200

BPF filter used: tcp

SYN threshold used: 50

The IDS logic analyzed TCP flags and counted packets dynamically during execution. The system generated an event-based alert after the SYN threshold was exceeded.

Generated evidence:
- artifacts/release/pcaps/test.pcap
- artifacts/release/logs/demo.log
- artifacts/release/metrics/results.json
- artifacts/release/charts/results.png
- artifacts/release/charts/results_table.txt
