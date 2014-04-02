using System;
using MongoDB.Driver;
using MongoDB.Bson;
using System.Collections;
using System.Threading;

namespace ReplicaSetOpsExample
{
	class MainClass
	{
		public static void performOperation() {
			MongoClient mc = new MongoClient("mongodb://aks-osx.local:27017,aks-osx.local:27018,aks-osx.local:27019/?readPreference=primaryPreferred");
			IList cursorList = new ArrayList ();

			long counter = 0;
			MongoServer ms = mc.GetServer ();
			MongoDatabase mDb = ms.GetDatabase ("test");
			using (ms.RequestStart (mDb)) {
				while (true) {
					++counter;
					try {
						bool collExists = mDb.CollectionExists ("data");
						var coll = mDb.GetCollection ("data");
						long collCount = coll.Count ();
						if (counter % 100 == 0) {
							Console.WriteLine ("Collection Stats [Thread: " + Thread.CurrentThread.ManagedThreadId
							+ ", Exists: " + collExists
							+ ", Count: " + collCount + ", listSize: " + cursorList.Count + "]");
						}

						cursorList.Add (coll.FindAll ());
					} catch (Exception ex) {
						Console.WriteLine ("Caught Exception within While Loop: " + ex.StackTrace);
					}
				}
			}
		}

		public static void Main (string[] args)
		{
			for (int i = 0; i < 300; ++i) {
				System.Threading.ThreadStart y = new System.Threading.ThreadStart (performOperation);
				System.Threading.Thread x = new System.Threading.Thread (y);
				x.Start ();
			}
		}
	}
}
