import matplotlib.pyplot as plt
import numpy as np

x = np.array([0, 30, 60, 90, 120])
y = np.array([0, 30, 60, 90, 120])


time_PC = np.array([0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 30, 50, 80, 100, 120])
voltage_PC = np.array([0.41, 0.51, 0.63, 0.76, 0.89, 1.2, 1.40, 1.79, 2.16, 2.43, 2.7, 2.7, 3.7, 4.1, 4.1, 4.1])
current_PC = np.array([140,140,140,140,140,140,140,140,140,140,140, 700, 700, 700, 450, 70])

font1 = {'family':'serif', 'color':'red', 'size':10}
font2 = {'family':'serif', 'color':'blue', 'size':10}

fig, ax1 = plt.subplots()


ax1.set_xlabel('Time (min)')
plt.title("Precharge                                               Constant current                                  Constant voltage")
ax1.set_ylabel('Voltage (V)', fontdict=font1)
ax1.plot(time_PC, voltage_PC, color = 'r')
ax1.grid()

ax2 = ax1.twinx()
ax2.set_ylabel('Current (mA)', fontdict=font2)
ax2.plot(time_PC, current_PC)


plt.show()
