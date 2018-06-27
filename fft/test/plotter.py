import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = []
for i in range(0, 4):
    data.append([])

with open('data.csv') as f:
    for line in f.readlines():
        v = line.strip().split(',')
        for j in range(0, 4):
            #print(v[j])
            data[j].append(float(v[j]))
plt.plot(data[0], data[1])
plt.plot(data[0], data[2])
plt.plot(data[0], data[3])
plt.savefig('out.png', dpi=600)
