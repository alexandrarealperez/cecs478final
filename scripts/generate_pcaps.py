from scapy.all import *

pkts = []
for i in range(20):
    pkts.append(IP(dst="1.1.1.1")/TCP(dport=80, flags="S"))

wrpcap("artifacts/release/pcaps/test.pcap", pkts)
print("PCAP generated")