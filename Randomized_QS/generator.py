import random

# Generate a random number of integers between 300 and 500
n = random.randint(300, 500)

# Generate random integers (for example between 1 and 1000)
numbers = [random.randint(1, 1000) for _ in range(n)]

# Write them to input.txt
with open("in.dat", "w") as f:
    for num in numbers:
        f.write(f"{num}\n")

print(f"Generated {n} random numbers in input.txt")
