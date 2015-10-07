#include "mongo.h"

const char* const TEST_NS = "twitter.tweet";

int main(int argc, const char* argv[]) {
	mongo conn;

	mongo_init(&conn);
	int status = mongo_client(&conn, "127.0.0.1", 27017);
	if (status != MONGO_OK) {
		fprintf(stderr, "Failed to make client connection to mongod [status: %d]", status);
		return 1;
	}

	bson query;
	bson_init(&query);
	bson_append_start_object(&query, "$query");
		bson_append_string(&query, "source", "web");
	bson_append_finish_object(&query);
	bson_finish(&query);

	mongo_cursor *cursor = mongo_find(&conn, TEST_NS, &query, NULL, 0, 0, 0);
	int count_matched = 0;
	bson *doc;

	// Assuming you are just looking for 100 key / value pair of max length of 99 characters
	const unsigned KV_ARRAY_LENGTH = 100;
	const unsigned MAX_KV_LENGTH = 105;
	char temp_key[KV_ARRAY_LENGTH][MAX_KV_LENGTH + 1], temp_value[KV_ARRAY_LENGTH][MAX_KV_LENGTH + 1];
	int i = 0;
	while (mongo_cursor_next(cursor) == MONGO_OK) {
		count_matched++;
		doc=(bson *)mongo_cursor_bson(cursor);

		bson_iterator it;
		bson_iterator_init(&it,doc);

		while (bson_iterator_next(&it) != BSON_EOO) {
			fprintf(stderr,"%s : %s\n", bson_iterator_key(&it), bson_iterator_string(&it));

			if (i < KV_ARRAY_LENGTH) {
				/* - Collect key-value pairs only if there is space in the array 
				 * - Key / Value woud be captured only till the max amount of space available for them i.e. MAX_KV_LENGTH in this case
				 * */
				strncpy(temp_key[i], bson_iterator_key(&it), MAX_KV_LENGTH);
				strncpy(temp_value[i], bson_iterator_string(&it), MAX_KV_LENGTH);
				temp_key[i][MAX_KV_LENGTH] = temp_value[i][MAX_KV_LENGTH] = '\0';
				++i;
			} else {
				/* whatever need to be done if there is no room in the array */
			}
		}
	}

	/* Test iterating through the key-value pair constructed in query iteration */
	fprintf(stdout, "--- Fields collected ---\n");
	int keyIndex = 0;
	for ( ; keyIndex < i; ++keyIndex) {
		fprintf(stdout, "{key: %s, value: %s}\n", temp_key[keyIndex], temp_value[keyIndex]);
	}

	mongo_cursor_destroy(cursor);
	mongo_destroy(&conn);
	return 0;
}
