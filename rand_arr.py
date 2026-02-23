import random
random.seed(1) # for reproducibility

rand_data = random.sample(range(1, 10000), 100)
print(rand_data)

worst_case_data = list(range(0, 10000, 100))
print(worst_case_data)
