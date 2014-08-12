package authenticatedcollops;


/*
 * Run mongo / mongos in authenticated mode and add following users in specific databases
 * 
 * use admin
 * db.addUser({user: "myuser", pwd: "password", roles: ["readWriteAnyDatabase", "userAdminAnyDatabase", "dbAdminAnyDatabase", "clusterAdmin"]})
 * 
 * use test
 * db.addUser({user: "myuser-testdb", pwd: "password", roles: ["readWrite", "userAdmin", "dbAdmin"]})
 * 
 */

import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.bson.types.BSONTimestamp;
import org.bson.types.ObjectId;

import com.mongodb.BasicDBObjectBuilder;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBObject;
import com.mongodb.Mongo;
import com.mongodb.MongoException;
import com.mongodb.MongoOptions;
import com.mongodb.ServerAddress;
import com.mongodb.WriteResult;

public class MongoOps {
	private int _connectTimeout;
	private int _socketTimeout;
	private int _connectionPoolSize;

	private boolean _isMongoAuthenticationOn;
	
	List<ServerAddress> _addressList;
	private Map<String, DB> _dbCache = new HashMap<String, DB>();
	private Map<String, Map<String, String>> _dbCredentials = new HashMap<String, Map<String,String>>();

	public MongoOps() throws Exception {
		// Add credentials by the database
		_dbCredentials.put("admin", createDBCeredentialEntry("myuser", "password"));
		_dbCredentials.put("test", createDBCeredentialEntry("myuser-testdb", "password"));
		
		_connectTimeout = 60000; // in milli-seconds
		_socketTimeout = 60000; // in milli-seconds
		_connectionPoolSize = 500;
		_isMongoAuthenticationOn = false;

		_addressList = new ArrayList<ServerAddress>();
		_addressList.add(new ServerAddress("ec2-54-191-19-1.us-west-2.compute.amazonaws.com", 27017));
	}
	
	private Map<String, String> createDBCeredentialEntry(String user, String passwd) {
		Map<String, String> map = new HashMap<String, String>();
		map.put("user", user);
		map.put("passwd", passwd);
		return map;
	}
	
	public DB getMongoDB(String dbName) {
		try {
			DB db = _dbCache.get(dbName);
			if (db == null) {
				Mongo mongo = getMongoConection();
				if (mongo != null) {
					db = mongo.getDB(dbName);
					if (_isMongoAuthenticationOn) {
						db.authenticate(_dbCredentials.get(dbName).get("user"), _dbCredentials.get(dbName).get("passwd").toCharArray());
						// or can use authenticateCommand as well
						//db.authenticateCommand(dbCredentials.get(dbName).get("user"), dbCredentials.get(dbName).get("passwd").toCharArray());
					}
					_dbCache.put(dbName, db);
				}
			}
			return db;

		} catch (UnknownHostException e) {
			throw new MongoException("Unknown mongoDB host", e);
		}
	}

	private Mongo getMongoConection() throws UnknownHostException {
		Mongo mongoConnection = null;

		try {
			// Should be using MongoClient instead in newer versions
			MongoOptions mongoOptions = new MongoOptions();
			mongoOptions.connectTimeout = _connectTimeout;
			mongoOptions.socketTimeout = _socketTimeout;
			mongoOptions.connectionsPerHost = _connectionPoolSize;
			mongoConnection = new Mongo(_addressList,mongoOptions);
		} catch (MongoException e) {
			if(mongoConnection != null){
				mongoConnection.close();	
			}
			throw e; 
		}
		return mongoConnection;
	}
	
	private boolean listDBs() {
		System.out.println("--- Listing database names --- ");
		try {
			DB db = getMongoDB("admin");
			List<String> dbNames = db.getMongo().getDatabaseNames();
			long dbIndex = 0;
			for (String dbName : dbNames) {
				System.out.println(" db[" + dbIndex + "] = " + dbName);
				++dbIndex;
			}
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	private boolean listCollections(DB db) {
		System.out.println("  --- Listing Collection names {db: " + db.getName() + "}");
		try {
			Set<String> collNames = db.getCollectionNames();
			long collIndex = 0;
			for (String collName : collNames) {
				System.out.println("    [" + collIndex + "] = " + collName);
				++collIndex;
			}
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	protected boolean runCollTest(long runId, long totalId, DB db, long maxCollOps) {
		DBObject obj;
		WriteResult writeResult;
		String findId = "", op = "";
		long failCount = 0;
		
		long collOps = (long)(Math.random() * maxCollOps);
		collOps = (collOps == 0 ? maxCollOps : collOps);
		System.out.println("-- [" + Thread.currentThread().getId()
				+ "] Running test instance " + runId + " of " + totalId + " for "
				+ collOps + " collection ops --");
		
		DBCollection coll = db.getCollection("random_ops");
		for (int i = 0; i < collOps; ++i) {
			writeResult = null;
			findId = "name-" + (long)(Math.random() * i);
			try {
				//switch (i % 5) {
				switch (1) {
				case 0: // Do deletes operations
					op = "delete";
					obj = coll.findOne(BasicDBObjectBuilder.start("name", findId).get());
					writeResult = coll.remove(obj);
					break;
				
				case 1: // Do insert operations
					op = "insert";
					findId = "name-" + i;
					obj = BasicDBObjectBuilder.start("name", findId)
							.add("currentTime", new BSONTimestamp())
							.add("famCounter", 0)
							.add("upCounter", 0)
							.add("yetAnotherId", "test-" + (new ObjectId()).toString())
							.get();
					writeResult = coll.insert(obj);
					break;
				
				case 2: // Do findAndModify operations
					op = "findAndModify";
					obj = coll.findAndModify(BasicDBObjectBuilder.start("name", findId).get()
							, BasicDBObjectBuilder.start("$set", BasicDBObjectBuilder.start("famCounter", 1).get()).get());
					break;
					
				case 3: // Do find and cursor loop
					op = "find";
					//DBCursor cur = coll.find();
					coll.count();
					/*
					while (cur.hasNext()) {
						cur.next();
					}
					*/
					break;
					
				default: // Do update operations
					op = "update";
					writeResult = coll.update(BasicDBObjectBuilder.start("name", findId).get()
							, BasicDBObjectBuilder.start("$set", BasicDBObjectBuilder.start("upCounter", 2).get()).get());
					break;
				}
				
				if (writeResult != null && !op.equals("find")) {
					// Do something to check the validness to executed result
				}
			} catch (Exception e) {
				++failCount;
				System.out.println("  [" + Thread.currentThread().getId() + "] failed ops {op: " 
						+ op + ", id: " + findId + ", failCount: " + failCount + "}");
			}
		}
		return true;
	}
	
	private void sleep(long millis) {
		try {
			Thread.sleep(millis);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public boolean runTest(long loopCount, long maxCollOps) {
		if (!listDBs()) {
			return false;
		}
		
		DB db = getMongoDB("test");
		sleep(50);
		listCollections(db);
		
		for (long i = 1; i <= loopCount; ++i) {
			runCollTest(i, loopCount, db, maxCollOps);
		}
		return true;
	}

	public static void main(String[] args) {
		try {
			//MongoOps instance = new MongoOps();
			MongoOps instance = new MongoMultiThreadedOps();
			instance.runTest(400, 10000);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
