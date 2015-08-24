from urllib import urlopen
from reportlab.graphics.shapes import *
from reportlab.graphics.charts.lineplots import LinePlot
from reportlab.graphics.charts.textlabels import Label
from reportlab.graphics import renderPDF



URL='http://services.swpc.noaa.gov/text/predicted-sunspot-radio-flux.txt'
COMMENT_CHARS='#:'

data=[]

for line in urlopen(URL).readlines():
	if not line.isspace() and not line[0] in COMMENT_CHARS:
		data.append([float(n) for n in line.split()])


drawing=Drawing(400,200)

pred=[row[2] for row in data]
high=[row[3] for row in data]
low=[row[4] for row in data]
times=[row[0]+row[1]/12.0 for row in data]

lp=LinePlot()
lp.x=50
lp.y=50
lp.height=125
lp.width=300
lp.data=[zip(times,pred),zip(times,high),zip(times,low)]
lp.lines[0].strokeColor=colors.blue
lp.lines[1].strokeColor=colors.red
lp.lines[2].strokeColor=colors.green

drawing.add(lp)
drawing.add(String(250,150,'Sunpots',fontSize=14,fillColor=colors.red))

renderPDF.drawToFile(drawing,'report2.pdf','Sunpots')
