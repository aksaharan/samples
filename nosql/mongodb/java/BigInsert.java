import com.mongodb.BasicDBObjectBuilder;
import com.mongodb.DBCollection;
import com.mongodb.MongoClient;
import com.mongodb.MongoClientOptions;
import com.mongodb.MongoException;
import com.mongodb.ReadPreference;

public class BigInsert {

	static String makeLargeString(int size) {
		StringBuffer sb = new StringBuffer(size);
		while (sb.length() < size) {
			sb.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		}
		return sb.toString();
	}
	

	public static void main(String[] args) {
		try {
			MongoClient mongoConnection = null;

			try {
				// Should be using MongoClient instead in newer versions
				MongoClientOptions.Builder mcoBuilder = MongoClientOptions.builder();
				mcoBuilder.readPreference(ReadPreference.primaryPreferred());
				mongoConnection = new MongoClient("localhost:2717", mcoBuilder.build());
				
				DBCollection coll = mongoConnection.getDB("test").getCollection("bigdoc");
				
				String largeString = makeLargeString(1024 * 1024 * 7);
				BasicDBObjectBuilder dbObjectBuilder = BasicDBObjectBuilder.start();
				dbObjectBuilder.append("key_1", largeString);
				dbObjectBuilder.append("key_2", largeString);
				dbObjectBuilder.append("key_3", largeString);
				dbObjectBuilder.append("key_4", largeString);
				dbObjectBuilder.append("key_5", largeString);
				dbObjectBuilder.append("key_6", largeString);
				dbObjectBuilder.append("key_7", largeString);
				dbObjectBuilder.append("key_8", largeString);
				coll.insert(dbObjectBuilder.get());
			} catch (MongoException e) {
				if (mongoConnection != null) {
					mongoConnection.close();
				}
				throw e;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}