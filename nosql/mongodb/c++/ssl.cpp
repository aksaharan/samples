#include <sstream>
#include <iostream>
#include <string>

using namespace std;

int main (int argc, char *argv[]) {

	ostringstream mongouri;
	mongouri << "mongodb://aks-osx-centos:27018/?ssl=true";
	MONGOC_DEBUG("%s : %d %s ", __func__, __LINE__, mongouri.str().c_str());

	mongoc_client_t *client;
	bson_error_t error;
	bson_t reply;

	mongoc_init();
	client = mongoc_client_new(mongouri.str().c_str());

	// SSL Options Starts Here
	char pem_file[256];
	mongoc_ssl_opt_t sslopt = { 0 };
	sprintf(pem_file, "%s", ADCDB_SSL_PEM_FILE);
	sslopt.pem_file = pem_file;
	//sslopt.ca_file = pem_file;
	sslopt.weak_cert_validation = true;
	mongoc_client_set_ssl_opts(client, &sslopt);

	MONGOC_DEBUG("ssl_opt: PEM FILE: %s, weak_cert_validation: %d", sslopt.pem_file, sslopt.weak_cert_validation);
	// SSL Options Ends Here

	if (client == NULL) {
		MONGOC_CRITICAL("%s : %d %s ", __func__, __LINE__, "Client is NULL");
		return 1;
	}

	bson_t replSetGetStatusCommand = BSON_INITIALIZER;
	bson_append_int32(&replSetGetStatusCommand, "replSetGetStatus", -1, 1);
	if (!mongoc_client_command_simple(client, "admin", &replSetGetStatusCommand, NULL, &reply, &error)) {
		MONGOC_ERROR("Failed to execute the command with error [%s]", error.message);
		return 1;
	}

	char* replyStr = bson_as_json(&reply, NULL);
	MONGOC_DEBUG("Completed command successfully: %s", replyStr);

	bson_free(replyStr);
	bson_destroy(&reply);
	mongoc_client_destroy(client);

	return EXIT_SUCCESS;
}
