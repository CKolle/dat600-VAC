import random

def generate_random_numbers(filename, count, min_value=0, max_value=1000):
    with open(filename, 'w') as f:
        for _ in range(count):
            f.write(f"{random.randint(min_value, max_value)}\n")

if __name__ == "__main__":
    generate_random_numbers("../dataset/small/random_100.txt", 100, 0, 1000)
    generate_random_numbers("../dataset/small/random_1000.txt", 1000, 0, 10000)
    generate_random_numbers("../dataset/medium/random_10000.txt", 10000, 0, 100000)
    generate_random_numbers("../dataset/medium/random_100000.txt", 100000, 0, 1000000)
    generate_random_numbers("../dataset/large/random_1000000.txt", 1000000, 0, 1000000000)
    generate_random_numbers("../dataset/large/random_10000000.txt", 10000000, 0, 1000000000)
    generate_random_numbers("../dataset/large/random_100000000.txt", 100000000, 0, 1000000000)
    