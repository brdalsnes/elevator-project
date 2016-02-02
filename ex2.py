import threading

lock = threading.Lock()
i = 0

def count(num):
	lock.acquire();
	global i

	for j in range(0, 1000000):
		lock.acquire()
		try:
			i += num
		finally:
			lock.release()


t1 = threading.Thread(target=count, args =((1),))
t1.start()

t2 = threading.Thread(target=count, args =((-1),))
t2.start()

print i
