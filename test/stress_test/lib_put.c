#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <kvs.h>

#define CNT 104858
#define KEY_BUFFER_SIZE 10002
#define VALUE_BUFFER_SIZE (100*1024)

KVS_ENV kvs_env;
char value_buffer[VALUE_BUFFER_SIZE];
char key_buffer[KEY_BUFFER_SIZE];

void get_key(char* key, int i, int* key_size)
{
	*key_size = 0;
	if (i == 0) *key_size = 1;
	while (i > 0)
	{
		key[*key_size] = '0' + i % 10;
		i = i / 10;
		(*key_size)++;
	}
	key[*key_size] = '0';
}

int main()
{
	long long start, end, duration, t1, t2;
	struct timeval tv;
	int i, key_size;

	kvs_env.init_type = INIT_TYPE_CREATE;
	kvs_env.disk_file_path = "disk_file";
	kvs_env.IMAGE_file_path = "IMAGE_file";
	kvs_env.log_file_path = "log_file";
	kvs_env.buffer_sleep_time = 0;
	kvs_env.buffer_horizon_size = 50 * 1024 * 1024;
	kvs_env.buffer_size = 500 * 1024 * 1024;

	for (i = 0; i < VALUE_BUFFER_SIZE; i++)
		value_buffer[i] = 'a';

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000 * 1000 + tv.tv_usec;

	if (kv_init(&kvs_env) != 0)
	{
		printf("kvs_init fail\n");
		return -1;
	}

	duration = 0;
	for (i = 0; i < CNT; i++)
	{
		get_key(key_buffer, i, &key_size);
		gettimeofday(&tv, NULL);
		t1 = tv.tv_sec * 1000 * 1000 + tv.tv_usec;

		if (kv_put(key_buffer, key_size, value_buffer, VALUE_BUFFER_SIZE) != 0)
		{
			printf("kv_put fail\n");
			return -1;
		}
		gettimeofday(&tv, NULL);
		t2 = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
		duration += (t2 - t1) / 1000;
	}

	kv_exit(1);

	printf("back time: %lld ms\n", duration);
	gettimeofday(&tv, NULL);
	end = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
	duration = (end - start) / 1000;

	printf("total time: %lld ms\n", duration);
	return 0;
}
