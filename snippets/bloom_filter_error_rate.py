from math import e


def bloom_err(m_div_n, k):
    return (1 - e ** (- k / m_div_n)) ** k


K = 12
M_div_N = 32
print('m/n\t', end='')
for k in range(1, K + 1):
    print("K = %d\t\t" % k, end='')
print()
for m_div_n in range(2, M_div_N + 1):
    print('%d\t' % m_div_n, end='')
    for k in range(1, K + 1):
        print('%.7f\t' % bloom_err(m_div_n, k), end='')
    print()
