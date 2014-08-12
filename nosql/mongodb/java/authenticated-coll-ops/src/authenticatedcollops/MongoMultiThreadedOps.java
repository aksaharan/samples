package authenticatedcollops;

import java.util.ArrayList;
import java.util.Collection;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.mongodb.DB;

public class MongoMultiThreadedOps extends MongoOps {
	ExecutorService _taskExecutor;
	Collection<Callable<Boolean>> _tasks;
	
	public MongoMultiThreadedOps() throws Exception {
		super();
		_taskExecutor = Executors.newFixedThreadPool(400);
		_tasks = new ArrayList<Callable<Boolean>>();
	}
	
	protected boolean runBaseCollTest(long runId, long totalId, DB db, long maxCollOps) {
		return super.runCollTest(runId, totalId, db, maxCollOps);
	}

	@Override
	protected boolean runCollTest(long runId, long totalId, DB db, long maxCollOps) {
		_tasks.add(new CollTestCallable(runId, totalId, maxCollOps, db, this));
		return true;
	}
	
	@Override
	public boolean runTest(long loopCount, long maxCollOps) {
		super.runTest(loopCount, maxCollOps);
		try {
			_taskExecutor.invokeAll(_tasks);
		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {
			_taskExecutor.shutdown();
		}
		return true;
	}
	
	class CollTestCallable implements Callable<Boolean> {
		long _runId, _totalId, _maxCollOps;
		DB _db;
		MongoMultiThreadedOps _instance;
		
		public CollTestCallable(long runId, long totalId, long maxCollOps, DB db, MongoMultiThreadedOps instance) {
			_runId = runId;
			_totalId = totalId;
			_maxCollOps = maxCollOps;
			_db = db;
			_instance = instance;
		}
		
		@Override
		public Boolean call() throws Exception {
			return _instance.runBaseCollTest(_runId, _totalId, _db, _maxCollOps);
		}
	}
 }
