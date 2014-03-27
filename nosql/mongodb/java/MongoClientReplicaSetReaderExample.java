import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;


public class MongoClientReplicaSetReaderExample {
	public static void main(String[] args) {
		try {
			MongoClient mc = new MongoClient(new MongoClientURI("mongodb://xxxxx.local:27017,xxxxx.local:27018,xxxxx.local:27019"));
			DB db = mc.getDB("test");
			long counter = 0;
			while (true) {
				++counter;
				try {
					DBCollection dbColl = db.getCollection("data");
					long count = dbColl.getCount();
					if (counter % 100 == 0) {
						System.out.println("Collection Exists: " + (db.collectionExists("data") ? "Yes" : "No") 
								+ ", Count: " + count);
					}
					Thread.sleep(10);
				} catch (Exception e) {
					System.out.println("Failed in the while loop: " + e);
				}
			}
		} catch (Exception e) {
			e.printStackTrace(System.out);
		}
	}
}
