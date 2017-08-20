#include "index_tree.h"

#define MAXINDEX (1<< MAX_ID)

struct index_tree{
	u32 id;
	struct index_tree *free_index;
	struct index_tree *idx[INDEX_BRANCH];
	void *data;
}

struct index_tree g_tree[MAX_INDEX];

struct index_tree * find_idx(struct index_tree * idx_head, int id);
struct index_tree * create_idx(struct index_tree * idx_head, int id);
void delete_data(struct index_tree * idx);
void *get_data(struct index_tree * idx, int id);

struct index_tree * find_idx(struct index_tree * idx_head, int id)
{
	struct index_tree *idx;

	if(idx_head == NULL)
		return NULL;

	if(id == idx_head->id)
		return idx_head;

	for(int i=0;i<INDEX_BRANCH;i++){
		idx = find_slot(idx_head->idx[i],id);
		if(idx)
			return idx;
	}

	return NULL;
}

struct index_tree * find_slot(struct index_tree * idx_head, int id)
{
	struct index_tree *idx;
	idx = find_idx(idx_head,id);
	if(idx)
		return idx;
	else
		create_idx(idx_head, id);
}

int insert_id(int id,void *data, struct index_tree *idx_head)
{
	struct index_tree *idx = find_slot(idx_head, id);

	add_data(idx, data);
	return idx.id;
}

int delete_id(int id,struct index_tree *idx_head)
{
	struct index_tree *idx = find_idx(idx_head, id);
	if(idx)
		delete_data(idx);
	return 0;
}

void * find_data(struct index_tree *idx_head,id)
{
	struct index_tree *idx = find_idx(idx_head,id);
	if(idx)
		return get_data(idx,id);
	return NULL;
}

void init_tree(struct index_tree *idx_head)
{
	memset(idx_head,0,sizeof(struct index_tree));
	for(int i=0;i<MAX_INDEX;i++){
		idx_head->free_index = &g_tree[i];
		idx_head = idx_head->free_index;
	}
}
