flags = -lgcrypt

objects = main.o

md5 : $(objects)
	gcc -o md5 $(objects) $(flags)

.PHONY : clean

clean:
	rm md5 $(objects)
