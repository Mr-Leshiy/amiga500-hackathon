#include <stdio.h>
#include <stdlib.h>

#include "parg.h"
#include "lib.h"
#include "encoding.h"

int main(int argc, const char **argv)
{
	Block genesis_block = create_genesis();
	print_block(&genesis_block);

	struct BlockChain chain;
	chain.b = genesis_block;

	struct parg_state ps;
	int c;
	parg_init(&ps);

	while ((c = parg_getopt(&ps, argc, argv, "b:m:v")) != -1) {
		switch (c) {
		case 'm':
			{
				printf("Sending message '%s'\n", ps.optarg);
				Tx tx = creates_tx(ps.optarg);

				// uint32_t bytes_size = tx_bytes_len(&tx);
				// uint8_t* bytes = (uint8_t*) malloc(bytes_size);
				// tx_to_bytes(&tx, bytes);

				// tx = tx_from_bytes(bytes);


				Block block = create_block(&chain.b, &tx);
				chain = add_block(&chain, block);
				// print_block(find_block(&chain, 0));
				break;
			}
		case 'b':
			{
				printf("Getting block message '%s'\n", ps.optarg);
				Tx tx = creates_tx(ps.optarg);
				Block block = create_block(&genesis_block, &tx);
				print_block(&block);
			}
			break;
		case 'v':
			printf("ironlink 1.0.0\n");
			return EXIT_SUCCESS;
			break;
		default:
			printf("error: unhandled option -%c\n", c);
			return EXIT_FAILURE;
			break;
		}
	}

	for (c = ps.optind; c < argc; ++c) {
		printf("nonoption '%s'\n", argv[c]);
	}

    return EXIT_SUCCESS;
}