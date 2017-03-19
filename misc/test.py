#!/home/xwang/anaconda3/bin/python3.6
import urllib
import re
from urllib.request import urlopen
from bs4 import BeautifulSoup


start_url='https://egov.uscis.gov/casestatus/landing.do'

def find_sessionid( htmls):
    jsids=re.findall('jsessionid=([0-9A-F]*)',htmls);
    sessionid=""
    if(len(jsids)==0):
        print("Error! no jsessionid is not found.")
        sys.exit(-2);
    for i in jsids:
        sessionid=i
        break
    return sessionid;
def get_html(url_input,value):
    data=urllib.parse.urlencode(value);
    data=data.encode('ascii');
    req=urllib.request.Request(url_input, data, headers={'User-Agent': 'Mozilla/5.0'})

    try:
        response = urlopen(req);   
    except urllib.error.URLError as e:
        print(e.reason)
        sys.exit(-1);
    html=""
    for l in response.readlines():
        html=html+" "+ l.decode('utf-8');
    return html
def get_form_number(mess):
    re_form=re.findall("Form I-([0-9]*)", mess);
    if( len(re_form)==0):
        return ""
    return re_form[0];
    
post_val={};
start_html=get_html(start_url, post_val);
sessionid=find_sessionid(start_html);


myID='LIN1790311887'
post_val={'appReceiptNum':myID}
query_url='https://egov.uscis.gov/casestatus/mycasestatus.do;jsessionid={}'.format(sessionid)
lines=get_html(query_url, post_val)
sessionid=find_sessionid(lines);
print("New sessionid: {}".format(sessionid))
soup = BeautifulSoup(lines, 'html.parser');
divs = soup.findAll('div',{'class':'rows text-center'});
if(len(divs)<1):
    print("Error!parse failed")
    sys.exit(-1)

caption=divs[0].h1.text
message=divs[0].p.text
print("Cap: {}".format(caption))
print("Mes: {}".format(message))
#re_form=re.findall("Form I-([0-9]*)", message);
#if( len(re_form)>0):
#    print("Form ID: {}".format(re_form[0]))
print("Form ID: {}".format( get_form_number(message)) );

