#!/usr/bin/env python

import pymongo
import time

client = pymongo.MongoClient("mongodb://localhost:20017,localhost:27018")

db = client.test

while 1 == 1:
	try:
		print "All Collections on DB: ", db.collection_names()
		time.sleep(10)
	except Exception as e:
		print "Exception caught: ", e
		time.sleep(2)
