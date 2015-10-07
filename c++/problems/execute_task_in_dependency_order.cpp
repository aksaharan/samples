/// given a list of tasks
// tasks can have dependencies on other tasks

// A, B, C, D
// B -> C -> A -> B

// A, C, D, B

// C depends on A
// B depends on C
// A has no dependencies

class Task {
    List<Task> Depenencies {get;} // I depend on A
    void Execute();
    bool HasExecuted();
}


List<Tasks> getRootNodes(List<Task> tasks) {
    HashMap<Task, long> rootNodeMap;
    parseRootNodes(tasks, rootNodeMap);
    
    List<Tasks> rootNodes = new List<Task>();
    foreach (pair<Task, long> rootNode : rootNodeMap) {
        if (rootNode.second == 0) {
            rootNodes.add(rootNode.first);
        }
    }
    
    return rootNodes;
}

void parseRootNodes(List<Task> tasks, HashMap<Task, long> rootNodes) {
    foreach (Task task : tasks) {
        if (!rootNodes.get(task)) {
            rootNodes.add(task, 0);
        }
        foreach (Task dTask : task.getDependencies()) {
            if (rootNodes.get(dTask)) {
                rootNodes[dTask] = rootNodes[dTask] + 1;
            }
            getRootNodes(dTask.getDependencies(), rootNodes);
        }
    }
}

void runTask(Task task) {
    if (task.hasExecuted()) {
        return;
    }
    
    foreach (Task childTask : task.getDependcies()) {
        runTask(childTask);
    }
    
    // Do processing this task
    task.Execute();    
}

void runTasks(List<Task> tasks) {
    List<Tasks> rootNodes = getRootNodes(tasks);
    foreach (Task task : rootNodes) {
        runTask(task);
    }
}
