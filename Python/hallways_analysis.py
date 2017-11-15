from datetime import datetime, timedelta


with open('hallways.csv', 'r') as f:
    records = [line.strip('\n').split(',') for line in f.readlines()]

header = records[0]
data = records[1:]

data = [(datetime.strptime(dt, '%Y/%m/%d %H:%M'), int(cnt)) for dt, cnt in data]
start_dt = datetime(2016, 5, 31, 0, 0, 0)
end_dt = datetime(2016, 6, 14, 0, 0, 0)
delta = timedelta(minutes=5)

start = 0
res = {}
while start_dt < end_dt:
    end = start
    key = '{} ~ {}'.format(start_dt, start_dt + delta)
    while end < len(data) and data[end][0] < (start_dt + delta):
        end += 1
    total_cnt = sum(cnt for dt, cnt in data[start:end])
    start = end
    start_dt += delta
    res[key] = total_cnt


print(res)
