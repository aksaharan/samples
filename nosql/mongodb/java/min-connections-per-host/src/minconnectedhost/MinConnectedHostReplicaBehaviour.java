package minconnectedhost;

import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;

import com.mongodb.*;

public class MinConnectedHostReplicaBehaviour implements Runnable {
	MongoClientOptions mco = null;
	List<MongoClient> mcList = new ArrayList<MongoClient>();
	
	public MinConnectedHostReplicaBehaviour(List<ServerAddress> serverAddresses, long mongoClientCount) throws UnknownHostException {
		MongoClientOptions.Builder mcoBuilder = new MongoClientOptions.Builder();
		mcoBuilder.readPreference(ReadPreference.primary());
		mcoBuilder.writeConcern(WriteConcern.ACKNOWLEDGED);
		mcoBuilder.minConnectionsPerHost(20);
		mcoBuilder.connectionsPerHost(100);
		mcoBuilder.requiredReplicaSetName("replset");
		mcoBuilder.maxConnectionIdleTime(1);
		mco = mcoBuilder.build();
		
		for (long i = 0; i < mongoClientCount; ++i) {
			MongoClient mc = new MongoClient(serverAddresses, mco);
			//mc.getDatabaseNames();
		}
	}
	
	@Override
	public void run() {
		try {
			Thread.sleep(100 * 1000);
		} catch (Exception e) {
			e.printStackTrace(System.out);
		} finally {
			cleanupMongoClients();
		}
	}
	
	private void cleanupMongoClients() {
		for (MongoClient mc : mcList) {
			mc.close();
		}
	}

	public static void main(String[] args) {
		try {
			List<ServerAddress> serverAddresses = new ArrayList<ServerAddress>();
			serverAddresses.add(new ServerAddress("localhost", 27017));
			serverAddresses.add(new ServerAddress("localhost", 27018));
			serverAddresses.add(new ServerAddress("localhost", 27019));

			new MinConnectedHostReplicaBehaviour(serverAddresses, 2).run();
		} catch (Exception e) {
			e.printStackTrace(System.out);
		}
	}

}
