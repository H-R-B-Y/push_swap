#!/usr/bin/python3

import subprocess
import random
import matplotlib.pyplot as plt
import argparse
import os
import statistics
import math
from concurrent.futures import ThreadPoolExecutor

def run_executable(executable_name, input_list):
	"""Runs the executable with a given list of integers and captures the output."""
	input_list = list(map(str, input_list))
	result = subprocess.run([executable_name] + input_list, text=True, capture_output=True)
	output_lines = result.stdout.splitlines()
	
	# Assuming the first line is the operation count and the second line is the sorted list.
	operations_count = int(output_lines[0])
	return operations_count

def generate_random_list(size):
	"""Generates a unique random list of integers between -100000 and 100000."""
	return random.sample(range(-100000, 100001), size)


def collect_data(executable_name, list_size, num_runs, max_workers=4):
	"""Generates data by running the executable num_runs times with random lists of list_size in parallel."""
	operation_counts = []
	
	def task():
		random_list = generate_random_list(list_size)
		return run_executable(executable_name, random_list)
	
	with ThreadPoolExecutor(max_workers=max_workers) as executor:
		futures = [executor.submit(task) for _ in range(num_runs)]
		for future in futures:
			operation_counts.append(future.result())
	
	return operation_counts

def main():
	# Setup argument parser
	parser = argparse.ArgumentParser(description="Run executable and plot sorting operation count.")
	parser.add_argument("executable", help="Path to the sorting executable")
	parser.add_argument("--num_runs", type=int, default=100, help="Number of times to run each list size")
	parser.add_argument("--output", type=str, default="output.png", help="Filename to save the output plot")
	parser.add_argument("--threads", type=int, default=4, help="Number of threads to use")

	args = parser.parse_args()
	
	# Print current working directory
	print(os.getcwd())

	# Run data collection
	operations_100 = collect_data(args.executable, 100, args.num_runs, max_workers=args.threads)
	operations_500 = collect_data(args.executable, 500, args.num_runs, max_workers=args.threads)

	# Plotting the results
	plt.figure(figsize=(12, 6))

	# Calculate statistics for 100 elements
	mean_100 = statistics.mean(operations_100)
	median_100 = statistics.median(operations_100)
	mode_100 = statistics.mode(operations_100)
	stdev_100 = statistics.stdev(operations_100)
	min_100 = min(operations_100)
	max_100 = max(operations_100)

	# Plot for 100 elements
	plt.subplot(1, 2, 1)
	plt.hist(operations_100, bins=20, color='skyblue', edgecolor='black')
	plt.title("Operations to Sort 100 Random Numbers")
	plt.xlabel("Number of Operations")
	plt.ylabel("Frequency")
	# Display statistics on the plot
	plt.text(0.7, 0.7, f"Mean: {mean_100:.2f}\nMedian: {median_100}\nMode: {mode_100}\nStd Dev: {stdev_100:.2f}\nMin: {min_100}\nMax: {max_100}",
			transform=plt.gca().transAxes, fontsize=10, bbox=dict(facecolor='white', alpha=0.5))

	# Calculate statistics for 500 elements
	mean_500 = statistics.mean(operations_500)
	median_500 = statistics.median(operations_500)
	mode_500 = statistics.mode(operations_500)
	stdev_500 = statistics.stdev(operations_500)#
	min_500 = min(operations_500)
	max_500 = max(operations_500)

	# Plot for 500 elements
	plt.subplot(1, 2, 2)
	plt.hist(operations_500, bins=20, color='salmon', edgecolor='black')
	plt.title("Operations to Sort 500 Random Numbers")
	plt.xlabel("Number of Operations")
	plt.ylabel("Frequency")
	# Display statistics on the plot
	plt.text(0.7, 0.7, f"Mean: {mean_500:.2f}\nMedian: {median_500}\nMode: {mode_500}\nStd Dev: {stdev_500:.2f}\nMin: {min_500}\nMax: {max_500}",
			transform=plt.gca().transAxes, fontsize=10, bbox=dict(facecolor='white', alpha=0.5))

	plt.tight_layout()
	plt.savefig(args.output)

if __name__ == "__main__":
	main()