def fibs(num):
	result=[0,1]
	for i in range(num-2):
		result.append(result[-2]+result[-1])
	return result

if __name__=='__main__':
	k=input("Enter a number:")
	print fibs(k)

