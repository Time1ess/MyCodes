from array import array


numbers = array('h', [-2, -1, 0, 1, 2])
print(numbers)
memv = memoryview(numbers)
print(len(memv))
print(memv[0])
memv_oct = memv.cast('B')
print(memv_oct.tolist())
memv_oct[5] = 4
print(numbers)
