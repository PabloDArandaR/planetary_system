import matplotlib.pyplot as plt
import argparse
import os
import pandas as pd


def plotLogFile():
    pass


def main():
    log_dir = os.path.join("log")
    filename = os.path.join(log_dir, "2023_10_19_13_21_34.csv")
    data = pd.read_csv(filename, delimiter=',')

    n_planets = int((len(data.columns) - 1) / 9)

    time = data.iloc[:,0].to_numpy()
    
    planets_data = []

    for i in range(n_planets):
        data_planet = data.iloc[:,1 + i*9:1 + (i + 1)*9].to_numpy()
        planets_data.append(data_planet)


    fig, ax = plt.subplots()

    for i in range(n_planets):
        ax.plot(planets_data[i][:,0], planets_data[i][:,1])
    
    ax.grid()

    fig.savefig("test_1.png")

if __name__ == "__main__":
    main()
