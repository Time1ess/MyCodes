width=input("Please enter width:")

price_width=10
item_width=width-price_width

header_fmt='%-*s%*s'
fmt='%-*s%*.2f'

print '='*width

print header_fmt%(item_width,'Item',price_width,'Price')

print '-'*width

print fmt%(item_width,'Apples',price_width,0.4)
print fmt%(item_width,'Pears',price_width,0.5)
print fmt%(item_width,'Cantaloupes',price_width,1.92)
print fmt%(item_width,'Dried Apricots (16 oz.)',price_width,8)
print fmt%(item_width,'Prunes (4 lbs.)',price_width,12)

print '='*width
