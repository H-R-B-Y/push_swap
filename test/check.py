#! /usr/bin/python3
import subprocess, random

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

def main():
	sorted = True
	while (sorted):
		num_list = generate_random_list(100)
		_, sorted = run_executable("./push_swap.out", num_list)
	print('"' + ' '.join(map(str, num_list)) + '"')

main()