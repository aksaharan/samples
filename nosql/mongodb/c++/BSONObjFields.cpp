#include <iostream>
#include <mongo/client/connpool.h>
#include <mongo/client/dbclientcursor.h>

using namespace bson;
using namespace mongo;

int main(void) {
	ScopedDbConnection dbc("localhost");

	BSONObj b = BSON("a"<<1<<"b"<<1);
	std::auto_ptr<DBClientCursor> cursor = dbc.conn().query("mydb.users", Query(), 0, 0, &b);
	while (cursor->more()) {
		BSONObj resultObj = cursor->next();
		std::cout << "Result Object: " << resultObj << std::endl;
	}

	return 0;
}
