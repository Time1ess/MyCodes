months = [
    'January',
    'February',
    'March',
    'April',
    'May',
    'June',
    'July',
    'August',
    'September',
    'October',
    'November',
    'December'
]

endings = ['st','nd','rd']+17*['th']\
         +['st','nd','rd']+7*['th']\
         +['st']

year=raw_input('Year:')
month=raw_input('Month:')
day=raw_input('Day:')

month_number=int(month)
day_number=int(day)

month_name=months[month_number-1]
day_name=day+endings[day_number-1]
print month_name+' '+day_name+','+year

