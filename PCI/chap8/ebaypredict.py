#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-23 14:34
# Last modified: 2016-08-24 16:54
# Filename: ebaypredict.py
# Description:
import urllib2
import httplib
import re
from xml.dom.minidom import parseString
from private_keys import DEVKEY, APPKEY, CERTKEY, USERTOKEN


dev_key = DEVKEY
app_key = APPKEY
cert_key = CERTKEY
user_token = USERTOKEN
finding_url = 'http://svcs.ebay.com/services/search/FindingService/v1?'
trading_url = 'api.ebay.com'


def get_headers_finding(apicall):
    headers = {'OPERATION-NAME': apicall,
               'SERVICE-VERSION': '1.0.0',
               'SECURITY-APPNAME': app_key,
               'RESPONSE-DATA-FORMAT': 'XML'}
    return headers


def get_headers_trading(apicall, site_id='0', compatability_level='889'):
    headers = {'X-EBAY-API-COMPATIBILITY-LEVEL': compatability_level,
               'X-EBAY-API-DEV-NAME': dev_key,
               'X-EBAY-API-APP-NAME': app_key,
               'X-EBAY-API-CERT-NAME': cert_key,
               'X-EBAY-API-CALL-NAME': apicall,
               'X-EBAY-API-SITEID': site_id,
               'Content-Type': 'text/xml'}
    return headers


def send_request(api_type, apicall, opts=None):
    if api_type == 'finding':
        headers = get_headers_finding(apicall)
        for key, value in headers.items():
            opts += '&%s=%s' % (key, value)
        conn = urllib2.urlopen(finding_url+opts)
        if conn.getcode() != 200:
            print 'Error sending request:'
            data = None
        else:
            data = conn.read()
            conn.close()
    elif api_type == 'trading':
        headers = get_headers_trading(apicall)
        connection = httplib.HTTPSConnection(trading_url)
        connection.request("POST", '/ws/api.dll',
                           opts, get_headers_trading(apicall))
        response = connection.getresponse()
        if response.status != 200:
            print "Error sending request:" + response.reason
        else:
            data = response.read()
            connection.close()
    return data


def get_single_value(node):
    def get_value(tag):
        nl = node.getElementsByTagName(tag)
        if len(nl) > 0:
            tag_node = nl[0]
            if tag_node.hasChildNodes():
                return tag_node.firstChild.nodeValue
        return -1
    return get_value


def do_search(query, category_id=None, page=1):
    opts = 'paginationInput.entriesPerPage=30'
    opts += '&paginationInput.pageNumber='+str(page)
    if category_id is not None:
        opts += '&categoryId='+str(category_id)
    opts += '&keywords='+query

    data = send_request('finding', 'findItemsAdvanced', opts)
    response = parseString(data)
    item_nodes = response.getElementsByTagName('item')
    results = []
    for item in item_nodes:
        values = get_single_value(item)
        item_id = values('itemId')
        item_title = values('title')
        item_price = values('currentPrice')
        item_ends = values('endTime')
        results.append((item_id, item_title, item_price, item_ends))
    return results


def get_category(query='', parent_id=None, site_id='0'):
    lquery = query.lower()
    xml = """
          <?xml version='1.0' encoding='utf-8'?>
          <GetCategoriesRequest xmlns="urn:ebay:apis:eBLBaseComponents">
          <RequesterCredentials>
          <eBayAuthToken>%s</eBayAuthToken>
          </RequesterCredentials>
          <DetailLevel>ReturnAll</DetailLevel>
          <ViewAllNodes>true</ViewAllNodes>
          <CategorySiteID>%s</CategorySiteID>
          """ % (user_token, site_id)
    if parent_id is None:
        xml += '<LevelLimit>1</LevelLimit>'
    else:
        xml += '<CategoryParent>'+str(parent_id)+'</CategoryParent>'
    xml += '</GetCategoriesRequest>'
    data = send_request('trading', 'GetCategories', xml)
    category_list = parseString(data)
    cate_nodes = category_list.getElementsByTagName('Category')
    for node in cate_nodes:
        values = get_single_value(node)
        cat_id = values('CategoryID')
        name = values('CategoryName')
        if name.lower().find(lquery) != -1:
            print cat_id, name


def get_item(item_id):
    xml = """
          <?xml version='1.0' encoding='utf-8'?>
          <GetItemRequest xmlns="urn:ebay:apis:eBLBaseComponents">
          <RequesterCredentials>
          <eBayAuthToken>%s</eBayAuthToken>
          </RequesterCredentials>
          <ItemID>%s</ItemID>
          <DetailLevel>ItemReturnAttributes</DetailLevel>
          <IncludeItemSpecifics>true</IncludeItemSpecifics>
          </GetItemRequest>
          """ % (user_token, item_id)
    data = send_request('trading', 'GetItem', xml)
    results = {}
    response = parseString(data)
    values = get_single_value(response)
    results['title'] = values('Title')
    selling_status_node = response.getElementsByTagName('SellingStatus')[0]
    values = get_single_value(selling_status_node)
    results['price'] = values('CurrentPrice')
    results['bids'] = values('BidCount')
    results['solds'] = values('QuantitySold')
    seller = response.getElementsByTagName('Seller')
    results['feedback'] = get_single_value(seller[0])('FeedbackScore')
    attribute_set = response.getElementsByTagName('NameValueList')
    attributes = {}
    for att in attribute_set:
        values = get_single_value(att)
        att_name = values('Name')
        att_value = values('Value')
        attributes[att_name] = att_value
    results['attributes'] = attributes
    return results


def make_laptop_dataset(laptops=None):
    if laptops is None:
        search_results = do_search('laptop', category_id=177)
    else:
        search_results = laptops
    results = []
    for idx, r in enumerate(search_results):
        item = get_item(r[0])
        att = item['attributes']
        try:
            data = cleanup_data(att)
            data += (float(item['feedback']),)
            entry = {'input': data, 'result': float(item['price'])}
            results.append(entry)
        except Exception, e:
            print 'failed.', e
        print '%d/%d' % (idx, len(search_results))
    return results


def cleanup_data(data_dict):
    nums = re.compile(r'(\d*\.\d+|\d+)')
    memory = float(nums.findall(data_dict['Memory'])[0])
    memory = memory/1024 if memory > 100 else memory
    cpu_speed = float(nums.findall(data_dict['Processor Speed'])[0])
    screen_size = float(nums.findall(data_dict['Screen Size'])[0])
    hdd_size = int(nums.findall(data_dict['Hard Drive Capacity'])[0])
    hdd_size = hdd_size*1024 if hdd_size < 10 else hdd_size
    return (memory, cpu_speed, screen_size, hdd_size)
