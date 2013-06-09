#include <iostream>
#include <queue>

class A {
public:

#define REQRESP_STATES RRS(not_conn)RRS(conn)RRS(req1_sent)RRS(resp1a_rcvd)\
RRS(resp1b_rcvd)RRS(req2_sent)RRS(resp2_rcvd)

	enum states {
#define RRS(x) rrs_##x,
		REQRESP_STATES rrs_count
#undef RRS
	};
};

int main(void) {
	std::cout << "---- Enum Problem ----" << std::endl << std::endl;

	std::cout << "req2_sent: " <<  A::rrs_req2_sent << " -> " << A::rrs_count << std::endl;
	return 0;
}
