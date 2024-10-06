#include<iostream>
#include <thread> // Include the thread header
#include <chrono> // Include the chrono header
#include <mutex>

using namespace std;

mutex mtx;

class Db
{
    string dbInstance="";
    
    static Db* db;

    // The constructor should always be private to prevent the new Db() call.
    Db(string dbConnUrl){
        dbInstance=dbConnUrl;
    }
    
    public:
    
    static Db* initialiseConn(string dbUri);

    void getDBConn(){
        cout<<"Db conn is : "<<dbInstance<<endl;
    }
};

Db* Db::db=NULL;

Db* Db::initialiseConn(string dbUri)
{

    // To fix the problem of threads we havae to synchronize the threads, meaning this block is executable only by single thread at a given point of time.
    // This is done by locking [Mutex].
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
    //============ Critical section =============
    if(db!=NULL) 
    return db;
    return db=new Db(dbUri);
    //===========================================
    // Mutex is automatically unlocked when lock goes out of scope
}

void exec1(){
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for 5 seconds
    Db* db = Db::initialiseConn("db1");
    db->getDBConn();
}

void exec2(){
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for 5 seconds
    Db* db = Db::initialiseConn("db2");
    db->getDBConn();
}

int main(){
    thread t1(exec1); // executing exec1 function on thread t1.
    thread t2(exec2); // executing exec2 function on thread t2.
    t1.join(); // awaiting main thread until this thread finishes execution.
    t2.join(); // awaiting main thread until this thread finishes execution.
    return 0;
}