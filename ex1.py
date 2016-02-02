import threading

i = 0

def count(num):
	global i

	for j in range(0, 1000000):
		i += num


t1 = threading.Thread(target=count, args =((1),))
t1.start()

t2 = threading.Thread(target=count, args =((-1),))
t2.start()

print i
