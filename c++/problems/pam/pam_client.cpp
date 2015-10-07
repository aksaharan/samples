#include <iostream>

#include <sys/types.h>
#include <security/pam_appl.h>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Invalid number of parameters: Usage <User> <Pass>" << endl;
		return 1;
	}

	cout << "Starting PAM session for [UserId: " << argv[1] << ", Passwd: XXXX" << "]" << endl;

	int errorCode = 0;
	pam_handle_t* pPamHandle;
	if (pam_start("auth", argv[1], NULL, &pPamHandle)) {
		cerr << "pam_start failed with error" << endl;
	}

	if (pam_end(pPamHandle, errorCode)) {
		cerr << "pam_end failed with error" << endl;
	}

	return 0;
}
