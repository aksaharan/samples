// CC insert.c -o insert -Isrc/mongoc/ -I src/libbson/src/bson/ -L src/libbson/.libs/ -L .libs/ -lbson -lmongoc-1.0
//
#include "mongoc.h"

const char* const TEST_NS = "test.big_document";

int main(int argc, const char* argv[]) {
	// To simulate a large document insert failure related behaviour.
	//
	mongoc_collection_t *collection;
	bson_error_t error;
	mongoc_client_t *client;
	bson_t *doc;
	char longStr[2 * 1024*1024] = {};

	fprintf(stderr, "Will continue with memsetting the values.\n");
	memset(longStr, 'a', sizeof(longStr));
	longStr[sizeof(longStr) - 1] = '\0';

	mongoc_init();
	client = mongoc_client_new("mongodb://127.0.0.1:27018");
	if (!client) {
		fprintf(stderr, "Failed to make client connection to mongod");
		return 1;
	}

	fprintf(stderr, "Will continue with creating the object.\n");

	doc = bson_new();
	BSON_APPEND_UTF8(doc, "key_1", longStr);
	BSON_APPEND_UTF8(doc, "key_2", longStr);
	BSON_APPEND_UTF8(doc, "key_3", longStr);
	BSON_APPEND_UTF8(doc, "key_4", longStr);
	BSON_APPEND_UTF8(doc, "key_5", longStr);
	BSON_APPEND_UTF8(doc, "key_6", longStr);
	BSON_APPEND_UTF8(doc, "key_7", longStr);
	BSON_APPEND_UTF8(doc, "key_8", longStr);

	fprintf(stderr, "Completed creating the document.. will continue with insertion.\n");
	collection = mongoc_client_get_collection (client, "test", "test");

	if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
		printf ("%s\n", error.message);
	}

	bson_destroy(doc);
	mongoc_collection_destroy(collection);

	mongoc_client_destroy(client);
	return 0;
}
