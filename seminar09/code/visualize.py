import matplotlib.pyplot as plt
import matplotlib.animation as anim
import serial

ser = serial.Serial('/dev/ttyACM1', 115200)

fig, ax = plt.subplots()
ax.set_ylim((0, 4096))
line, = ax.plot(list(range(128)), [0] * 128)


def update(frame):
    data = [int(x) for x in ser.readline().split()]
    line.set_ydata(data)

    return line


ani = anim.FuncAnimation(fig, update)
plt.show()
