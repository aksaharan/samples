using System;
using System.Collections.Generic;
using MongoDB.Bson;
using MongoDB.Driver;

namespace SampleGistApp
{
	public class BulkWriteOperationsSample
	{
		private MongoClient _mc;
		private MongoServer _ms;
		private MongoDatabase _mdb;

		public BulkWriteOperationsSample (string[] args) {
			_mc = new MongoClient("mongodb://aks-osx:27017/");
			_ms = _mc.GetServer ();
			_mdb = _ms.GetDatabase ("test");
		}

		IList<BsonDocument> getAllDocuments(string collectionName) {
			IList<BsonDocument> docList = new List<BsonDocument>();
			using (_ms.RequestStart (_mdb)) {
				MongoCollection mc = _mdb.GetCollection ("csharp");
				MongoCursor<BsonDocument> cur = mc.FindAllAs<BsonDocument> ();
				System.Collections.Generic.IEnumerator<BsonDocument> e = cur.GetEnumerator ();
				while (e.MoveNext ()) {
					docList.Add(e.Current);
				}
			}
			return docList;
		}

		void displayCollection(string collectionName) {
			IList<BsonDocument> docList = getAllDocuments (collectionName);
			foreach (var doc in docList) {
				Console.WriteLine (" - " + doc.ToString ());
			}
			Console.WriteLine ("Total Entries in Collection [" + collectionName + "] = " + docList.Count);
		}

		public void runSampleInserts() {
			using (_ms.RequestStart (_mdb)) {
				try {
					MongoCollection mc = _mdb.GetCollection("csharp");
					BulkWriteOperation bwo = mc.InitializeOrderedBulkOperation();
					for (int i = 0; i < 1; ++i) {
						BsonDocument doc = new BsonDocument();
						doc.Add("counter", new BsonInt32(i));
						doc.Add("time", new BsonDateTime(new DateTime()));
						bwo.Insert(doc);
					}
					BulkWriteResult bwr = bwo.Execute();
					Console.WriteLine("Completed BulkInsert Operations [inserts: " + bwr.InsertedCount + "]");
					displayCollection("csharp");
				} catch (Exception ex) {
					Console.WriteLine ("Caught Exception while BulkWriteOperation for Insert: " + ex.StackTrace);
				}
			}
		}

		public void runSampleUpdates() {
			using (_ms.RequestStart (_mdb)) {
				try {
					MongoCollection mc = _mdb.GetCollection("csharp");
					BulkWriteOperation bwo = mc.InitializeOrderedBulkOperation();
					foreach (var doc in getAllDocuments("csharp")) {
						BulkWriteRequestBuilder bwrb = bwo.Find(new QueryDocument{ {"counter", doc.GetValue("counter").AsInt32 } });
						bwrb.Update(new UpdateDocument{ {"$set",  new UpdateDocument { {"counter", 1} } } });
					}
					BulkWriteResult bwr = bwo.Execute();
					Console.WriteLine("Completed BulkWriteOperations [updates: " + bwr.ModifiedCount + "]");
					displayCollection("csharp");
				} catch (Exception ex) {
					Console.WriteLine ("Caught Exception while BulkWriteOperation for Update: " + ex.StackTrace);
				}
			}
		}

		public void runSampleDeletes() {
			using (_ms.RequestStart (_mdb)) {
				try {
					IEnumerable<string> collNames = _mdb.GetCollectionNames();
					MongoCollection mc = _mdb.GetCollection("csharp");
					BulkWriteOperation bwo = mc.InitializeOrderedBulkOperation();
					BulkWriteRequestBuilder bwrb = bwo.Find(new QueryDocument{});
					bwrb.Remove();
					BulkWriteResult bwr = bwo.Execute();
					Console.WriteLine("Completed BulkWriteOperations [deletes: " + bwr.DeletedCount + "]");
					displayCollection("csharp");
				} catch (Exception ex) {
					Console.WriteLine ("Caught Exception while BulkWriteOperation for Delete: " + ex.StackTrace);
				}
			}
		}

		public void myMain() {
			runSampleInserts ();
			runSampleUpdates ();
			runSampleDeletes ();
		}
	}
}