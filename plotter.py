import pandas as pd
import matplotlib.pyplot as plt

plt.style.use("bmh")

if __name__ == "__main__":
    df = pd.read_csv("simulation_results.txt",sep=',',skiprows=(0),header=(0))

    # plt.figure()
    # plt.plot(df["x_sat_1 (m)"]*1e-3, df["y_sat_1 (m)"]*1e-3, label="trajectory")
    # plt.scatter(df["x_sat_1 (m)"][0]*1e-3, df["y_sat_1 (m)"][0]*1e-3, label="init pos")
    # plt.xlabel('x (km)')
    # plt.ylabel('y (km)')
    # plt.title('Satellite Orbit Around Earth')
    # plt.axis('equal')
    # plt.legend()

    plt.figure()
    plt.plot(df["t (s)"], df["R_1 (m)"]*1e-3, label="sat 1")
    plt.plot(df["t (s)"], df["R_2 (m)"]*1e-3, label="sat 2")
    plt.plot(df["t (s)"], df["R_3 (m)"]*1e-3, label="sat 3")
    plt.plot(df["t (s)"], df["R_4 (m)"]*1e-3, label="sat 4")
    plt.xlabel('t (s)')
    plt.ylabel('range (km)')
    plt.title('Range between receiver and satellite')
    plt.legend()

    plt.show()