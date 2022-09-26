#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int* seg_tree_const(int* list, int size) {
	double temp = size;
	int height = 0;
	while (temp >= 2) {
		temp = temp / 2;
		height += 1;
	}
	height += 1;
	int t_size = (pow(2, height + 1)) - 1;
	int *segtree = calloc(t_size, sizeof(int));
	construct_tree(list, 0, size-1, segtree, 0);
	return segtree;
}

int construct_tree(int* list, int start, int end, int* segtree, int cur) {
	if (start == end) {
		segtree[cur] = list[start];
		return list[start];
	}
	int mid = start + (end - start) / 2;
	int child = 2 * cur;
	segtree[cur] = construct_tree(list, start, mid, segtree, child + 1) + construct_tree(list, mid + 1, end, segtree, child + 2);
	return segtree[cur];
}

int Getquery(int* segtree, int size, int q_s, int q_e) {
	int sum = 0;
	if (q_s<0 || q_e>size - 1 || q_e < q_s) {
		printf("�߸��� ���� ���� �ε��� �����Դϴ�.\n");
		return 0;
	}
	sum = Querysum(segtree, 0, size - 1, q_s, q_e, 0);
	return sum;
}

int Querysum(int* segtree, int start, int end, int q_s, int q_e, int cur) {
	if (q_s <= start && q_e >= end) {
		return segtree[cur];
	}
	if (end < q_s || start > q_e) {
		return 0;
	}
	int mid = start + (end - start) / 2;
	int child = 2 * cur;
	return Querysum(segtree, start, mid, q_s, q_e, child + 1) + Querysum(segtree, mid + 1, end, q_s, q_e, child + 2);
}

int* Segtree_update(int* segtree, int start, int end, int i, int d_value, int cur) {
	if (i<start || i>end) {
		return NULL;
	}
	segtree[cur] = segtree[cur] + d_value;
	if (start != end) {
		int mid = start + (end - start) / 2;
		int child = 2 * cur;
		Segtree_update(segtree, start, mid, i, d_value, child + 1);
		Segtree_update(segtree, mid + 1, end, i, d_value, child + 2);
	}
}

int print_tree(int* segtree, int size) {
	int height = 0;
	while (size >= 2) {
		size = size / 2;
		height += 1;
	}
	height += 1;
	int t_size = (pow(2, height + 1)) - 1;
	printf("\n���׸�Ʈ Ʈ���� �ϼ�\n");
	for (int i = 0; i < t_size; i++) {
		printf("%d\t", segtree[i]);
	}
	return t_size;
}


void main(void) {
	int size = 0;
	printf("���׸�Ʈ Ʈ���� ���̸� �����ּ���:");
	scanf("%d", &size);
	int *list = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		int temp = 0;
		printf("����Ʈ�� ������ �Է����ּ���: ");
		scanf("%d", &temp);
		list[i] = temp;
	}

	printf("\n�Է¹��� ����Ʈ�� ��\n");
	for (int j = 0; j < size; j++) {
		printf("%d\t", list[j]);
	}
	printf("\n");
	
	int* segtree = seg_tree_const(list, size);
	int seg_size = print_tree(segtree, size);

	int choose = 1;
	printf("\n\n���׸�Ʈ Ʈ���� Ȱ�� �˰����Դϴ�.\n");
	while (1) {
		printf("\n���� ������ ���� ���Ͻ÷��� �Ѵٸ� 1��\n���׸�Ʈ Ʈ���� ���� ������Ʈ �ϽŴٸ� 2��\n���׸�Ʈ Ʈ���� ����Ϸ��� 3��\n���α׷��� �����Ͻ÷��� 0�� �Է����ּ���: ");
		scanf("%d", &choose);
		if (choose == 0)
			break;
		else if (choose == 1) {
			int q_s, q_e;
			printf("���� ���� ���������� �ε���:");
			scanf("%d", &q_s);
			printf("���� ���� �������� �ε���:");
			scanf("%d", &q_e);
			int sum = Getquery(segtree, size, q_s, q_e);
			printf("�����Ͻ� ���� ������ ����: %d �Դϴ�.\n", sum);
		}
		else if (choose == 2) {
			int change, cindex = 0;
			printf("�����Ͻ� ���� �ε����� �Է����ּ���: ");
			scanf("%d", &cindex);
			printf("�����Ͻ� ���� �Է����ּ���: ");
			scanf("%d", &change);
			int d_value = change - list[cindex];
			list[cindex] = change;
			Segtree_update(segtree, 0, size, cindex, d_value, 0);
		}
		else if (choose == 3) {
			print_tree(segtree, size);
		}
		else {
			printf("�߸��� ���� �Է��ϼ̽��ϴ�.");
		}
	}
}