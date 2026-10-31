
import csv
import re
import statistics
import subprocess
from pathlib import Path

import matplotlib.pyplot as plt

ROOT = Path(__file__).resolve().parent.parent
RESULTS = ROOT / "results"

THREAD_COUNTS = [1, 2, 4, 8, 16]
REPETITIONS = 3

# Adjust these commands to match your compiled executables.
SINGLE_CMD = ["./build/single"]
MULTI_CMD = ["./build/multi"]


def benchmark(command):
    times = []

    for _ in range(REPETITIONS):
        result = subprocess.run(
            command,
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=True
        )

        match = re.search(
            r"Execution Time:\s*([\d.eE+-]+)\s*seconds",
            result.stdout
        )

        if not match:
            raise RuntimeError(
                f"Could not find timing in output:\n{result.stdout}"
            )

        times.append(float(match.group(1)))

    return statistics.median(times)


def main():
    RESULTS.mkdir(exist_ok=True)

    print("Running single-threaded baseline...")
    baseline = benchmark(SINGLE_CMD)

    data = [("Single", 0, baseline, 1.0)]

    for count in THREAD_COUNTS:
        print(f"Benchmarking {count} threads...")

        elapsed = benchmark(MULTI_CMD + [str(count)])
        speedup = baseline / elapsed

        data.append((f"{count} threads", count, elapsed, speedup))

        print(f"  Time: {elapsed:.4f}s | Speedup: {speedup:.2f}x")

    # Save results to CSV
    with open(RESULTS / "benchmark.csv", "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Method", "Threads", "Time (s)", "Speedup"])
        writer.writerows(data)

    
    # Generate graph
    labels = [row[0] for row in data]
    times = [row[2] for row in data]
    speedups = [row[3] for row in data]

    fig, ax = plt.subplots(figsize=(11, 6))
    bars = ax.bar(labels, speedups)

    ax.axhline(
        1.0, linestyle="--", color="gray",
        label="Single-threaded baseline"
    )

    ax.set_xlabel("Thread Configuration")
    ax.set_ylabel("Speedup (x)")
    ax.set_title("Matrix Multiplication — Thread Scaling")
    ax.legend()

    # Show speedup and execution time above every bar
    bar_labels = [
        f"{speed:.2f}x\n{elapsed:.3f}s"
        for speed, elapsed in zip(speedups, times)
    ]

    ax.bar_label(bars, labels=bar_labels, padding=4)
    ax.set_ylim(0, max(speedups) * 1.30)

    plt.tight_layout()
    plt.savefig(RESULTS / "speedup.png", dpi=200)

    # Open interactive graph window
    plt.show()



if __name__ == "__main__":
    main()
