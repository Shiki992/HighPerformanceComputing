from random import random,uniform
from tqdm import tqdm

if __name__ == "__main__":
    file="nos2.txt"
    f=open(file,"w")
    for i in tqdm(range(1000000000)):
        f.write(str(uniform(10,10000000)))
        f.write("\n")
    f.close()