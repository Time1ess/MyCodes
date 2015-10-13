import scrapy

class DlutSpier(scrapy.spiders.Spider):
    name='dlut'
    allowed_domains=['dlut.edu.cn']
    start_urls=[
            'http://www.dlut.edu.cn',
            ]

    def parse(self,response):
        filename=response.url.split('/')[-1]
        with open(filename,'w') as f:
            sel=response.xpath('//title').extract()
            print sel
            f.write(''.join(sel))
