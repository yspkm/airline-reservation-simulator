#include "rbtree.h"

bool RB_INSERT(rbtree_t *T, key_t k)
{
	return rb_insert_key(T, k, DUMMY_DATA);
}

bool RB_DELETE(rbtree_t *T, key_t k)
{
	return rb_delete_key(T, k);
}

void PRINT_BST(rbtree_t *T)
{
	rb_print(T, T->root, NULL, false);
}

// alloc & free
void rb_malloc(rbtree_t *T)
{
	T->nil = (rbnode_t *)malloc(sizeof(rbnode_t));
	T->nil->p = NULL;
	T->nil->left = NULL;
	T->nil->right = NULL;
	T->nil->key = 0x0;
	T->nil->data = 0x0;
	T->nil->color = BLACK;
	T->root = NULL;
}

void rb_free(rbtree_t *T)
{
	while (T->root != T->nil)
		rb_delete_key(T, T->root->key);
	free(T->nil);
}

// PRINT
void init_edge(rbedge_t *this, rbedge_t *prev, char *str)
{
	this->prev = prev;
	this->str = str;
}

void show_edges(rbedge_t *e)
{
	if (e == NULL)
	{
		return;
	}

	show_edges(e->prev);
	printf("%s", e->str);
}
#include "path.h"
#include "graph.h"
extern void print_path_rbtree(path_t *);
extern void print_tunit(tunit_t);
extern void print_actual_time(double);

void print_node(rbnode_t * cur)
{
	path_t *p;
	mhd_t t;
    printf("RID(%d): [", cur->key);
    p = (path_t*) cur->data;
    t = get_mhd(p->dtime[0]);
    printf("%s, %d, %c, %c, ", p->name, t.d, p->src + 'a', p->dst + 'a');
    print_path(p);
	printf("]");
}

int rb_print(rbtree_t *T, rbnode_t *cur, rbedge_t *previous, bool isLeft)
{
	static char *str0 = (char *)"---";
	static char *str1 = (char *)".---";
	static char *str2 = (char *)"   |";
	static char *str3 = (char *)"`---";

	if (cur == T->nil || cur==NULL)
	{
		return 0;
	}

	char *prev_str = (char *)"    ";
	rbedge_t obj_this;
	rbedge_t *edge = &obj_this;

	init_edge(edge, previous, prev_str);

	rb_print(T, cur->right, edge, true);

	if (previous == NULL)
	{
		edge->str = str0;
	}
	else if (isLeft)
	{
		edge->str = str1;
		prev_str = str2;
	}
	else
	{
		;
		edge->str = str3;
		previous->str = prev_str;
	}

	show_edges(edge);
	printf(" %c: ", cur->color);
	print_node(cur);
	printf("\n");

	if (previous)
	{
		previous->str = prev_str;
	}
	edge->str = (char *)"   |";

	rb_print(T, cur->left, edge, false);
	return 0;
}


// operations
rbnode_t *rb_maximum(rbtree_t *T, rbnode_t *cur)
{
	rbnode_t *ret;
	ret = cur;
	while (ret->right != T->nil)
	{
		ret = ret->right;
	}
	return ret;
}

rbnode_t *rb_minimum(rbtree_t *T, rbnode_t *x)
{
	while (x->left != T->nil)
		x = x->left;
	return x;
}

rbnode_t *predecessor(rbtree_t *T, rbnode_t *cur)
{
	rbnode_t *ret;
	ret = cur->left;
	if (ret != T->nil)
		ret = rb_maximum(T, ret);
	return ret;
}

rbnode_t *tree_successor(rbtree_t *T, rbnode_t *x)
{
	rbnode_t *y;
	if (x->right != T->nil)
	{
		y = rb_minimum(T, x->right);
		goto done;
	}
	y = x->p;
cond:
	if (y != T->nil && x == y->right)
		goto loop;
	else
		goto done;
loop:
	x = y;
	y = y->p;
	goto cond;
done:
	return y;
}

rbnode_t *rb_recursive_search(rbtree_t *T, rbnode_t *cur, key_t k)
{
	rbnode_t *ret;
	if (cur != T->nil)
	{
		if (cur->key == k)
		{
			ret = cur;
		}
		else if (k < cur->key)
		{
			ret = rb_recursive_search(T, cur->left, k);
		}
		else // if (k > cur->key)
		{
			ret = rb_recursive_search(T, cur->right, k);
		}
	}
	else
	{
		ret = T->nil;
	}

	return ret;
}

bool rb_search(rbtree_t *T, key_t k)
{
	if (!T->root || T->root==T->nil)
		return false;
	bool ret;
	rbnode_t *find;
	find = rb_recursive_search(T, T->root, k);
	if (find == T->nil)
	{
		ret = false;
	}
	else
	{
		ret = true;
	}
	return ret;
}

void left_rotate(rbtree_t *T, rbnode_t *x)
{
	rbnode_t *y;
	y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
	{
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == T->nil)
	{
		T->root = y;
	}
	else if (x == x->p->left)
	{
		x->p->left = y;
	}
	else
	{
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void right_rotate(rbtree_t *T, rbnode_t *y)
{
	rbnode_t *x;
	x = y->left;
	y->left = x->right;
	if (x->right != T->nil)
	{
		x->right->p = y;
	}
	x->p = y->p;
	if (y->p == T->nil)
	{
		T->root = x;
	}
	else if (y == y->p->left)
	{
		y->p->left = x;
	}
	else
	{
		y->p->right = x;
	}
	x->right = y;
	y->p = x;
}

void rb_transplant(rbtree_t *T, rbnode_t *src, rbnode_t *dst)
{
	if (src->p == T->nil)
		T->root = dst;
	else if (src == src->p->left)
		src->p->left = dst;
	else
		src->p->right = dst;
	dst->p = src->p;
}

key_t nearest_neighbor(rbtree_t *T, key_t k)
{
	rbnode_t *cur;

	cur = T->root;
	while (cur != T->nil)
	{
		if (k == cur->key)
			break;

		if (k < cur->key)
		{
			if (cur->left == T->nil)
				break;
			cur = cur->left;
		}
		else
		{
			if (cur->right == T->nil)
				break;
			cur = cur->right;
		}
	}

	cur = abs(cur->key - k) <= abs(cur->p->key - k) ? cur : cur->p;
	return cur->key;
}
 
// insert
bool rb_insert_key(rbtree_t *T, key_t k, data_t item)
{
	bool ret;

	rbnode_t *z = (rbnode_t *)malloc(sizeof(rbnode_t));
	z->color = RED;
	z->key = k;
	z->p = T->nil;
	z->left = T->nil;
	z->right = T->nil;
	z->data = item;

	ret = true;
	if (!rb_insert(T, z))
	{
		ret = false;
		free(z);
	}

	return ret;
}

bool rb_insert(rbtree_t *T, rbnode_t *z)
{
	if (T->root == NULL)
	{
		z->left = T->nil;
		z->right = T->nil;
		z->p = T->nil;
		z->color = BLACK;
		T->root = z;
		return true;
	}

	rbnode_t *x, *y;

	if (rb_search(T, z->key))
		return false;

	x = T->root;
	y = x->p;

	while (x != T->nil)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == T->nil)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;

	rb_insert_fixup(T, z);
	return true;
}

void rb_insert_fixup(rbtree_t *T, rbnode_t *z)
{
	rbnode_t *y;
	while (z->p->color == RED)
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->right)
				{
					z = z->p;
					left_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(T, z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->left)
				{
					z = z->p;
					right_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(T, z->p->p);
			}
		}
	}
	T->root->color = BLACK;
}

// delete
bool rb_delete_key(rbtree_t *T, key_t k)
{
	rbnode_t *y, *z;
	z = rb_recursive_search(T, T->root, k);
	y = rb_delete(T, z);
	if (y != T->nil)
	{
		free(y);
		return true;
	}
	return false;
}

rbnode_t *rb_delete(rbtree_t *T, rbnode_t *z)
{
	rbnode_t *x, *y;
	if (z->left == T->nil || z->right == T->nil)
		y = z;
	else
		y = tree_successor(T, z);
	if (y->left != T->nil)
		x = y->left;
	else
		x = y->right;
	x->p = y->p;
	if (y->p == T->nil)
		T->root = x;
	else if (y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;

	if (y != z)
	{
		z->key = y->key;
		z->data = y->data;
	}

	if (y->color == BLACK)
		rb_delete_fixup(T, x);

	return y;
}

void rb_delete_fixup(rbtree_t *T, rbnode_t *x)
{
	rbnode_t *w;
	while (x != T->root && x->color == BLACK)
	{
		if (x == x->p->left)
		{
			w = x->p->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				left_rotate(T, x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(T, w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				left_rotate(T, x->p);
				x = T->root;
			}
		}
		else // 반대
		{
			w = x->p->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				right_rotate(T, x->p);
				w = x->p->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(T, w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				right_rotate(T, x->p);
				x = T->root;
			}
		}
	}
	x->color = BLACK;
}
