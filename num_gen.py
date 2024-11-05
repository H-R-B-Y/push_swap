#! /usr/bin/python3
import random

# Generate the list
unique_numbers = random.sample(range(-50000, 50001), 10)
unique_numbers_str = ' '.join(map(str, unique_numbers))

# Write to a file (e.g., "args.txt")
with open("args.txt", "w") as file:
    file.write(unique_numbers_str)