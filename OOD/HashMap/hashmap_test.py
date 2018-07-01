from hashmap import HashMap


def main():
    m = HashMap()

    ops = [
        ('insert', (5, 6), (True,)), ('lookup', (5,), (6,)),
        ('insert', (7, 3), (True,)), ('lookup', (7,), (3,)),
        ('lookup', (5,), (6,)), ('insert', (5, 2), (False,)),
        ('lookup', (5,), (2,)), ('erase', (5,), (True,)),
        ('lookup', (5,), (None,)), ('erase', (3,), (False,)),
    ]

    for op, input, expected_output in ops:
        if op == 'insert':
            output = (m.insert(*input),)
        elif op == 'lookup':
            output = (m.lookup(*input),)
        else:
            output = (m.erase(*input),)
        assert output == expected_output, 'Expected {} == {}'.format(
            output, expected_output)
        print('Succeed')


if __name__ == '__main__':
    main()
