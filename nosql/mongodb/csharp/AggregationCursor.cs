using System;
using System.Collections;

using MongoDB.Driver;
using MongoDB.Bson;

namespace AggregationCursor
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			MongoClient mc = new MongoClient ("mongodb://localhost:27017");
			MongoDatabase mDB = mc.GetServer ().GetDatabase ("test");
			Console.WriteLine ("Got MongoDB Database");

			MongoCollection mColl = mDB.GetCollection ("aggTest");
			AggregateArgs aggArgs = new AggregateArgs ();
			aggArgs.OutputMode = AggregateOutputMode.Cursor;
			aggArgs.Pipeline = new [] {
				new BsonDocument {
					{
						"$match", new BsonDocument { 
							{"a", new BsonInt32(1)}
						}
					}
				}
			};


			Console.WriteLine ("Complete AggArgs ");
			long rowCount = 0;
			IEnumerable aggResults = mColl.Aggregate (aggArgs);
			foreach (BsonDocument doc in aggResults) {
				Console.WriteLine ("Fetching Agg Result Records in Cursor [" + rowCount + "]");
				++rowCount;
			}
			Console.WriteLine ("Completed Agg result Scan: " + rowCount);
		}
	}
}