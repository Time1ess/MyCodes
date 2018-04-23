import numpy as np
import matplotlib.pyplot as plt


def bloom_err(m_div_n, k):
    return (1 - np.e ** (- k / m_div_n)) ** k


K = 12
M_div_N = 32
print('m/n\t', end='')
for k in range(1, K + 1):
    print("K = %d\t\t" % k, end='')
plt.figure(figsize=(16, 16))
print()
for m_div_n in range(2, M_div_N + 1):
    print('%d\t' % m_div_n, end='')
    errors = [100 * bloom_err(m_div_n, k) for k in range(1, K + 1)]
    for e in errors:
        print('%.7f\t' % e, end='')
    plt.plot(range(1, 1 + K), errors, label='%d' % m_div_n)
    print()
plt.ylim([0, 100])
plt.legend(title='M / N', bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
plt.ylabel('Error rate(%)')
plt.xlabel('Number of hash functions')
plt.title('Bloom filter error rates')
plt.show()
