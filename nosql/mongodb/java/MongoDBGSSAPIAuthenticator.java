import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.mongodb.MongoClient;
import com.mongodb.MongoCredential;
import com.mongodb.ServerAddress;

public class MongoDBGSSAPIAuthenticator {
	final static Logger _log = Logger.getLogger(MongoDBGSSAPIAuthenticator.class.getName());

	public static void main(String[] args) {
		System.out.println("Invoked the class main: " + MongoDBGSSAPIAuthenticator.class.getName());
		if (args.length < 2) {
			System.out.println("Invalid invocation, needs atleast two parameters.");
			System.out.println("Usage: " + MongoDBGSSAPIAuthenticator.class.getName() + " <MongoServer> <UserId>");
			System.exit(1);
		}

		String serverName = args[0];
		String userId = args[1];

		try {
			System.out.println("Running the Java GSSAPI Authentication with following parameters {user: "
					+ userId + ", server: " + serverName + "}");

			MongoCredential credential = MongoCredential.createGSSAPICredential(userId);
			MongoClient mongoClient = new MongoClient(new ServerAddress(serverName), Arrays.asList(credential));
			mongoClient.getDB("test").getCollection("test").findOne();
			System.out.println("Should have successfully authenticated");
		} catch (Exception e) {
			System.out.println("Exception raised during the authentication process" + e);
			e.printStackTrace();
			System.exit(1);
		}

		System.exit(0);
	}
}
