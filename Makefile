CC=g++
CFLAGS= -lpqxx -lpq
OUT=lab2
SRCS= src/main.cpp src/connection.cpp src/transaction_mng.cpp

$(OUT):$(SRCS)
	$(CC) $(SRCS)	$(CFLAGS)	-o $(OUT)

clean:
	rm $(OUT)
