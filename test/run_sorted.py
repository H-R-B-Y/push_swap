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
	
	# Parse operation count and sorted output
	operations_count = int(output_lines[0])
	sorted_output = list(map(int, output_lines[1].split()))

	# Check if the sorted output is actually sorted
	is_correctly_sorted = sorted_output == sorted(list(map(int, input_list)), reverse=True)
	
	return operations_count, is_correctly_sorted

def generate_random_list(size):
	"""Generates a unique random list of integers between -100000 and 100000."""
	return random.sample(range(-100000, 100001), size)


def collect_data(executable_name, list_size, num_runs, max_workers=4):
	"""Generates data by running the executable num_runs times with random lists of list_size in parallel."""
	correct_operations = []
	incorrect_operations = []
	
	def task():
		random_list = generate_random_list(list_size)
		operations, is_correct = run_executable(executable_name, random_list)
		return operations, is_correct
	
	with ThreadPoolExecutor(max_workers=max_workers) as executor:
		futures = [executor.submit(task) for _ in range(num_runs)]
		for future in futures:
			operations, is_correct = future.result()
			if is_correct:
				correct_operations.append(operations)
			else:
				incorrect_operations.append(operations)
	
	return correct_operations, incorrect_operations

def plot_histogram(correct_operations, incorrect_operations, title, ax):
	"""Plots a histogram with side-by-side bars for correct and incorrect sorting outcomes."""
	bins = range(min(correct_operations + incorrect_operations), max(correct_operations + incorrect_operations) + 1)
	
	# Plot histograms with different colors and labels for correct and incorrect
	ax.hist(correct_operations, bins=bins, alpha=0.6, label="Correctly Sorted", color='skyblue', edgecolor='black', align='left')
	ax.hist(incorrect_operations, bins=bins, alpha=0.6, label="Incorrectly Sorted", color='salmon', edgecolor='black', align='right')

	# Add legend and labels
	ax.set_title(title)
	ax.set_xlabel("Number of Operations")
	ax.set_ylabel("Frequency")
	ax.legend()

def main():
	# Setup argument parser
	parser = argparse.ArgumentParser(description="Run executable and plot sorting operation count.")
	parser.add_argument("executable", help="Path to the sorting executable")
	parser.add_argument("--num_runs", type=int, default=100, help="Number of times to run each list size")
	parser.add_argument("--output", type=str, default="output.png", help="Filename to save the output plot")
	parser.add_argument("--threads", type=int, default=4, help="Number of threads to use")

	args = parser.parse_args()
	
	print(os.getcwd())

	# Run data collection
	correct_100, incorrect_100 = collect_data(args.executable, 100, args.num_runs, max_workers=args.threads)
	correct_500, incorrect_500 = collect_data(args.executable, 500, args.num_runs, max_workers=args.threads)

	# Plotting the results
	fig, axes = plt.subplots(1, 2, figsize=(24 * 2, 12 * 2))

	# Plot for 100 elements
	plot_histogram(correct_100, incorrect_100, "Operations to Sort 100 Random Numbers", axes[0])

	# Plot for 500 elements
	plot_histogram(correct_500, incorrect_500, "Operations to Sort 500 Random Numbers", axes[1])

	plt.tight_layout()
	plt.savefig(args.output)

if __name__ == "__main__":
	main()