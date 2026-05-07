import argparse
from pathlib import Path
from scapy.all import Ether, IP, TCP, wrpcap

parser = argparse.ArgumentParser(description="Generate synthetic TCP SYN PCAP")
parser.add_argument("--count", type=int, default=200)
parser.add_argument("--output", default="artifacts/release/pcaps/test.pcap")
parser.add_argument("--src", default="172.19.0.2")
parser.add_argument("--dst", default="1.1.1.1")
parser.add_argument("--sport", type=int, default=20)
parser.add_argument("--dport", type=int, default=80)

args = parser.parse_args()

Path(args.output).parent.mkdir(parents=True, exist_ok=True)

packets = []

for _ in range(args.count):
    packet = (
        Ether()
        / IP(src=args.src, dst=args.dst)
        / TCP(sport=args.sport, dport=args.dport, flags="S")
    )
    packets.append(packet)

wrpcap(args.output, packets)

print(f"Generated synthetic PCAP with {args.count} TCP SYN packets")
print(f"Output: {args.output}")