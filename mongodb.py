#-*- coding=utf-8 -*-
from pymongo import  MongoClient
client=MongoClient('127.0.0.1',27017)
url='http://example.com/view/unitied-239'
html='hello'
db=client.cache
#db.webpage.insert({'url':url,'html':html})

#设置ID 为url ,并且更新HTML的内容
db.webpage.update({'_id':url},{'$set':{'html':html}},upsert=True)

print db.webpage.find_one({'_id':url})
