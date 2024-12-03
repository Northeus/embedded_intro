import matplotlib.pyplot as plt
import matplotlib.animation as anim
import serial

ser = serial.Serial('/dev/ttyACM0', 115200)

fig, ax = plt.subplots()
ax.set_ylim((0, 5000))
line, = ax.plot(list(range(128)), [0] * 128)


def update(frame):
    inpu = ser.readline()
    data = [int(x) for x in inpu.split()]

    if len(data) != 128:
        return line

    line.set_ydata(data)

    return line


ani = anim.FuncAnimation(fig, update)
plt.show()
