from reportlab.lib import colors
from reportlab.graphics.shapes import *
from reportlab.graphics import renderPDF

data=[
		#Year Month Predicted High Low
		(2015,2,58.9,59.9,57.9),
		(2015,3,57.1,59.1,55.1),
		(2015,4,55.8,58.8,52.8),
		(2015,5,55,60,50),
		(2015,6,53.4,58.4,48.4),
		(2015,7,51.8,57.8,45.8),
		(2015,8,51.4,58.4,44.4),
		]

drawing=Drawing(200,150)

pred=[row[2] for row in data]
high=[row[3] for row in data]
low=[row[4] for row in data]
times=[200*((row[0]+row[1]/12.0)-2015)-110 for row in data]

drawing.add(PolyLine(zip(times,pred),strokeColor=colors.blue))
drawing.add(PolyLine(zip(times,high),strokeColor=colors.red))
drawing.add(PolyLine(zip(times,low),strokeColor=colors.green))
drawing.add(String(65,115,'Sunpots',fontSize=18,fillColor=colors.red))

renderPDF.drawToFile(drawing,'report1.pdf','Sunpots')
