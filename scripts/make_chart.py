import json
import matplotlib.pyplot as plt
from pathlib import Path

metrics_path = Path("artifacts/release/metrics/results.json")
chart_path = Path("artifacts/release/charts/results.png")
table_path = Path("artifacts/release/charts/results_table.txt")

with open(metrics_path, "r") as f:
    data = json.load(f)

labels = [
    "Total Packets",
    "SYN Packets",
    "ACK Packets",
    "Non-SYN Packets",
    "Alerts",
]

values = [
    data["total_packets"],
    data["syn_packets"],
    data["ack_packets"],
    data["non_syn_packets"],
    data["alerts"],
]

plt.figure(figsize=(11, 6))
bars = plt.bar(labels, values)

plt.title("Packet Sniffer with BPF: Detection Summary")
plt.xlabel("Metric")
plt.ylabel("Count")

for bar, value in zip(bars, values):
    plt.text(
        bar.get_x() + bar.get_width() / 2,
        bar.get_height(),
        str(value),
        ha="center",
        va="bottom",
        fontsize=10,
    )

summary = (
    f"BPF Filter: {data['bpf_filter']}\n"
    f"SYN Threshold: {data['syn_threshold']}\n"
    f"Detection Type: {data['detection_type']}"
)

plt.figtext(0.5, -0.06, summary, ha="center", fontsize=10)
plt.tight_layout(rect=[0, 0.12, 1, 1])
plt.savefig(chart_path, bbox_inches="tight")
plt.close()

with open(table_path, "w") as f:
    f.write("Packet Sniffer with BPF Results Summary\n")
    f.write("======================================\n")
    for label, value in zip(labels, values):
        f.write(f"{label}: {value}\n")
    f.write(f"BPF Filter: {data['bpf_filter']}\n")
    f.write(f"SYN Threshold: {data['syn_threshold']}\n")
    f.write(f"Detection Type: {data['detection_type']}\n")