#include "Enclave_t.h"
#include <sgx_trts.h>
#include <string.h>

uint8_t g_a[4096];
uint8_t g_b[4096];

int ecall_test(const char *message, size_t message_len)
{
	ocall_print(message);

	return 31337;
}

void ecall_cca_init(uintptr_t *ptr)
{
	memset(g_a, 'A', 4096);
	memset(g_b, 'B', 4096);

	uintptr_t addr = (uintptr_t)&g_b[0];

	*ptr = addr;
}

void ecall_cca()
{
	uint8_t rand = 0;

	sgx_status_t status = sgx_read_rand(&rand, sizeof(uint8_t));

	if(status != SGX_SUCCESS) return;

	int val = 0;

	if(rand < 127) val = g_a[0];
	else val = g_b[0];

}