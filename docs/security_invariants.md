# Security Invariants

- Only synthetic or test PCAP data is used for analysis
- No real user or live network traffic is captured or processed
- The system handles invalid inputs safely, including:
  - nonexistent PCAP files
  - empty PCAP files
  - malformed or corrupted files
- The program does not crash when encountering bad input
- Logs contain only metadata (packet counts, alerts) and do not include sensitive payload data
- All processing occurs inside a Docker container, isolating the system from the host environment