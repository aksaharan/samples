using System;
using MongoDB.Driver;
using MongoDB.Bson;

namespace RunCommandFromApp
{
	class MainClass
	{
		public static void turnNoTableScanOnOff(bool status) {
			MongoClient mc = new MongoClient("mongodb://aks-osx-centos:23021/");

			MongoServer ms = mc.GetServer ();
			MongoDatabase mDb = ms.GetDatabase ("admin");
			CommandDocument cd = new CommandDocument ();
			cd.Add ("setParameter", new BsonBoolean (true));
			cd.Add ("notablescan", new BsonBoolean (status));
			using (ms.RequestStart (mDb)) {
				try {
					CommandResult cr = mDb.RunCommand(cd);
					Console.WriteLine("Changed [notablescan = " + status + "] : " + cr.ToString());
				} catch (Exception ex) {
					Console.WriteLine ("Caught Exception within While Loop: " + ex.StackTrace);
				}
			}
		}

		public static void Main (string[] args)
		{
			turnNoTableScanOnOff (true);
			Console.WriteLine ("Turned notablescan on - test the query now");
			System.Threading.Thread.Sleep (60000);
			turnNoTableScanOnOff (false);
			Console.WriteLine ("Turned notablescan off - test the query now again");
		}
	}
}
