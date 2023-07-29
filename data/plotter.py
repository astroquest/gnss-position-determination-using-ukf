import pandas as pd
import matplotlib.pyplot as plt

plt.style.use("bmh")

def simulation_results():
    df_sim = pd.read_csv("sim_results.txt",sep=',',skiprows=(0),header=(0))

    plt.figure()
    plt.plot(df_sim["x_sat_1 (m)"]*1e-3, df_sim["y_sat_1 (m)"]*1e-3, label="trajectory")
    plt.plot(df_sim["x_sat_2 (m)"]*1e-3, df_sim["y_sat_2 (m)"]*1e-3, label="trajectory")
    plt.plot(df_sim["x_sat_3 (m)"]*1e-3, df_sim["y_sat_3 (m)"]*1e-3, label="trajectory")
    plt.plot(df_sim["x_sat_4 (m)"]*1e-3, df_sim["y_sat_4 (m)"]*1e-3, label="trajectory")
    plt.scatter(df_sim["x_sat_1 (m)"][0]*1e-3, df_sim["y_sat_1 (m)"][0]*1e-3, label="init pos")
    plt.xlabel("x (km)")
    plt.ylabel("y (km)")
    plt.title("Satellite Orbit Around Earth")
    plt.axis("equal")
    plt.legend()

    plt.figure()
    plt.plot(df_sim["t (s)"], df_sim["R_1 (m)"]*1e-3, label="sat 1")
    plt.plot(df_sim["t (s)"], df_sim["R_2 (m)"]*1e-3, label="sat 2")
    plt.plot(df_sim["t (s)"], df_sim["R_3 (m)"]*1e-3, label="sat 3")
    plt.plot(df_sim["t (s)"], df_sim["R_4 (m)"]*1e-3, label="sat 4")
    plt.xlabel('t (s)')
    plt.ylabel('range (km)')
    plt.title('Range between receiver and satellite')
    plt.legend()


def estimation_results():
    df_estimates = pd.read_csv("estimation_results.txt",sep=',',skiprows=(0),header=(0))

    plt.figure()
    plt.plot(df_estimates["t (s)"], df_estimates["x_rec_baseline (m)"], label="baseline")
    plt.plot(df_estimates["t (s)"], df_estimates["x_rec (m)"], label="estimate")
    plt.xlabel("time (s)")
    plt.ylabel("x position (m)")
    # plt.ylim((-10,10))
    plt.title('Receiver Position')
    plt.legend()

    plt.figure()
    plt.plot(df_estimates["t (s)"], df_estimates["x_rec_baseline (m)"] - df_estimates["x_rec (m)"], label="x")
    plt.plot(df_estimates["t (s)"], df_estimates["y_rec_baseline (m)"] - df_estimates["y_rec (m)"], label="y")
    plt.xlabel("time (s)")
    plt.ylabel("position error (m)")
    plt.ylim((-5,5))
    plt.title('Receiver Position Error')
    plt.legend()

    # plt.figure()  # add z-axis component
    # plt.plot(df_estimates["t (s)"], df_estimates["z_rec_baseline (m)"] - df_estimates["z_rec (m)"])
    # plt.xlabel("time (s)")
    # plt.ylabel("z position error (m)")
    # plt.title('Receiver Position Error')

    plt.figure()
    plt.plot(df_estimates["t (s)"], df_estimates["clock_bias_baseline (m)"] - df_estimates["clock_bias (m)"])
    plt.xlabel("time (s)")
    plt.ylabel("clock bias error (m)")
    plt.ylim((-5,5))
    plt.title('Clock Bias Error')


if __name__ == "__main__":
    # simulation_results()
    estimation_results()

    plt.draw()
    plt.pause(1)
    input("press to close")
    plt.close()