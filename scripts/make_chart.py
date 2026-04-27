import matplotlib.pyplot as plt

labels = ['Packets', 'Alerts']
values = [20, 1]

plt.bar(labels, values)
plt.title("NIDS Results")
plt.savefig("artifacts/release/charts/results.png")