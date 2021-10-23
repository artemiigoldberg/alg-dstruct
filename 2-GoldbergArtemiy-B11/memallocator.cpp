#include <stdio.h>
#include "memallocator.h"
#define TRUE 1
#define FALSE 0
#define MEM_PTR(block) (void*)((header*)block + 1)
#define HEADER_PTR(mem_ptr) (header*)mem_ptr - 1


struct header {
	struct header* next;
	struct header* prev;
	int block_size;
	char is_free;
};

typedef struct header header;

header* head = NULL;
int full_size = 0;

header* find_first_fit(int size) {
	if (head == NULL)
		return NULL;

	header* block_ptr = head;

	while (block_ptr != NULL) {
		if (block_ptr->is_free == TRUE)
			if (block_ptr->block_size >= size)
				break;

		block_ptr = block_ptr->next;
	}

	return block_ptr;
}

char create_block(header* block, int size) {
	if (head == NULL || block == NULL || block->is_free == FALSE)
		return FALSE;

	if (block->block_size - size > sizeof(header)) {
		header* new_block = (header*)((char*)MEM_PTR(block) + size);

		new_block->block_size = block->block_size - size - sizeof(header);
		new_block->is_free = TRUE;
		new_block->next = block->next;
		new_block->prev = block;
		
		if (block->next != NULL)
			block->next->prev = new_block;
		
		block->next = new_block;
	}

	block->block_size = size;
	block->is_free = FALSE;

	return TRUE;
}

int meminit(void* pMemory, int size) {
	if (head != NULL || size < sizeof(header) || pMemory == NULL)
		return 1;

	head = (header*)pMemory;

	head->block_size = size - sizeof(header);
	head->next = NULL;
	head->prev = NULL;
	head->is_free = TRUE;

	full_size = size;

	return 0;
}

void memdone() {
	int size = 0;

	if (head == NULL)
		return;

	header* block = head;

	while (block != NULL) {
		if (block->is_free == TRUE)
			size += block->block_size;

		block = block->next;
	}

	size += sizeof(header);

	if (size < full_size)
		fprintf(stderr, "Memory leak: \n\texpected %d\n\tcurrent %d\n", full_size, size);
}

void* memalloc(int size) {
	if (head == NULL)
		return NULL;

	header* found_block = find_first_fit(size); 

	if (found_block == NULL)
		return NULL;

	if (!create_block(found_block, size))
		return NULL;

	return MEM_PTR(found_block);
}

void memfree(void* p) {
	if (p == NULL)
		return;

	header* free_block = HEADER_PTR(p);

	if (free_block == NULL || free_block->is_free == TRUE)
		return;

	header* buffer_block = free_block;
	buffer_block->is_free = TRUE;

	if (free_block->prev != NULL) {
		if (free_block->prev->is_free == TRUE) {
			int new_size = 0;

			if (free_block->next != NULL)
				new_size = (char*)free_block->next - (char*)(free_block->prev + 1);
			else
				new_size = (char*)(head + 1) + full_size - (char*)(free_block->prev + 1);

			free_block->prev->next = free_block->next;
			
			if (free_block->next != NULL)
				free_block->next->prev = free_block->prev;

			free_block->prev->block_size = new_size;
			buffer_block = free_block->prev;
		}
	}

	if (buffer_block->next != NULL) {
		if (buffer_block->next->is_free == TRUE) {
			int new_size = 0;

			if (buffer_block->next->next != NULL)
				new_size = (char*)buffer_block->next->next - (char*)(buffer_block + 1);
			else
				new_size = (char*)(head + 1) + full_size - (char*)(buffer_block + 1);

			if (buffer_block->next->next != NULL)
				buffer_block->next->next->prev = buffer_block;

			buffer_block->next = buffer_block->next->next;
			buffer_block->block_size = new_size;
		}
	}

	if (buffer_block->next != NULL) {
		if (((char*)(buffer_block + 1) + buffer_block->block_size) != (char*)buffer_block->next) {
			void* leaked_ptr = (void*)((char*)(buffer_block + 1) + buffer_block->block_size);
			int size = (char*)buffer_block->next - (char*)leaked_ptr;

			buffer_block->block_size += size;
		}
	}
	else
		if (((char*)head + full_size) != ((char*)(buffer_block + 1) + buffer_block->block_size)) {
			void* leaked_ptr = (void*)((char*)(buffer_block + 1) + buffer_block->block_size);
			int size = (char*)head + full_size - (char*)leaked_ptr;

			buffer_block->block_size += size;
		}
}

int memgetminimumsize() {
	return sizeof(header);
}

int memgetblocksize() {
	return sizeof(header);
}