# -*- coding: gbk -*-

import MySQLdb
from random import random
from time import clock

SIZE1 = 10000
SIZE2 = 100
DB_ENGINE = 'InnoDB' # InnoDB Memory MyISAM
print '测试数据量：', SIZE1 * SIZE2
print '测试引擎：', DB_ENGINE

t1 = clock()

sqls = ['INSERT INTO test (value) VALUES (%s)' % '),('.join([`random()` for i in xrange(SIZE1)]) for j in xrange(SIZE2)]
t2 = clock()

try:
  con = MySQLdb.connect(host='localhost',user='root', passwd='Dyc19930418', db='pythonsql',port=3306)
  t3 = clock()
  cu = con.cursor()
except:
	pass

con.autocommit(True)

try:
  cu.execute('DROP TABLE test')
except:
  pass

cu.execute('''CREATE TABLE test (
`id` INT AUTO_INCREMENT PRIMARY KEY,
`value` REAL)
ENGINE = %s''' % DB_ENGINE)
t4 = clock()

for sql in sqls:
  cu.execute(sql)
t5 = clock()

cu.execute('SELECT COUNT(*) FROM test WHERE value < 0.1')
print '共有%d个小于0.1的随机数' % cu.fetchone()[0]
t6 = clock()

cu.execute('SELECT * FROM test WHERE value > 0.9')
print '共有%d个大于0.9的随机数' % len(cu.fetchall())
t7 = clock()

cu.execute('UPDATE test SET value = value + 0.1 WHERE value > 0.4 AND value < 0.5')
t8 = clock()

cu.execute('DELETE FROM test WHERE value > 0.5 AND value < 0.6')
t9 = clock()

cu.close()
con.close()
t10 = clock()

con = MySQLdb.connect(host='localhost',user='root', passwd='Dyc19930418', db='pythonsql',port=3306)
t11 = clock()
con.close()

print '创建随机数：', t2 - t1
print '初次连接数据库：', t3 - t2
print '再次连接数据库：', t11 - t10
print '初始化数据库：', t4 - t3
print '插入：', t5 - t4
print '选择（COUNT）', t6 - t5
print '选择：', t7 - t6
print '更新：', t8 - t7
print '删除：', t9 - t8
print '关闭连接：', t10 - t9
print '总时间：', t10 - t1
