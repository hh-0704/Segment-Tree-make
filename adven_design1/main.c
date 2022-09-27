#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int* seg_tree_const(int* list, int size) {     /* �־��� �Է� ����Ʈ�� ���׸�Ʈ Ʈ���� �����ϱ� ���� �� �ܰ� �˰��� */
	double temp = size;
	int height = log2(temp);
	int cal = pow(2, height);
	if (cal % size != 0) {
		height += 1;
	}
	int t_size = (pow(2, height + 1)) - 1;
	int *segtree = calloc(t_size, sizeof(int));
	construct_tree(list, 0, size-1, segtree, 0);
	return segtree;
}

int construct_tree(int* list, int start, int end, int* segtree, int cur) {   /* �־��� �Է� ����Ʈ�� ���׸�Ʈ Ʈ���� �����ϴ� �˰��� */
	if (start == end) {
		segtree[cur] = list[start];
		return list[start];
	}
	int mid = start + (end - start) / 2;
	int child = 2 * cur;
	segtree[cur] = construct_tree(list, start, mid, segtree, child + 1) + construct_tree(list, mid + 1, end, segtree, child + 2);
	return segtree[cur];
}

int Getquery(int* segtree, int size, int q_s, int q_e) {    /* ���׸�Ʈ Ʈ���� ����Ͽ� �κ� ���� ����ϱ� ���� �� �ܰ� �˰��� */
	int sum = 0;
	if (q_s<0 || q_e>size - 1 || q_e < q_s) {
		printf("�߸��� ���� ���� �ε��� �����Դϴ�.\n");
		return 0;
	}
	sum = Querysum(segtree, 0, size - 1, q_s, q_e, 0);
	return sum;
}

int Querysum(int* segtree, int start, int end, int q_s, int q_e, int cur) {    /* ���׸�Ʈ Ʈ���� ����Ͽ� �κ� ���� ����ϴ� �˰��� */
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

int* Segtree_update(int* segtree, int size, int find, int d_value) {     /* �Է� ����Ʈ�� ���� ����Ǿ��� �� ���׸�Ʈ Ʈ���� �����ϴ� �˰��� */
	int num = find;
	double temp = size;
	int height = log2(temp);
	int cal = pow(2, height);
	if (cal % size != 0) {
		height += 1;
	}
	int t_size = (pow(2, height + 1)) - 1;
	int find_index = -1;
	for (int i = 0; i < t_size; i++) {
		if (segtree[i] == find) {
			find_index = i;
		}
	}
	while (find_index >= 1) {
		segtree[find_index] += d_value;
		find_index = (find_index - 1) / 2;
	}
	segtree[find_index] += d_value;
	
	return segtree;
}

void print_tree(int* segtree, int size) {      /* ���׸�Ʈ Ʈ���ϼ��� ���� ����� �غ��� �˰��� */
	double temp = size;
	int height = log2(temp);
	int cal = pow(2, height);
	if (cal % size != 0) {
		height += 1;
	}
	int t_size = (pow(2, height + 1)) - 1;
	int step = 1;
	printf("\n���׸�Ʈ Ʈ���� �ϼ�\n");
	for (int i = 0; i < t_size; i++) {
		printf("%d\t", segtree[i]);
		if ((i + 1) == (pow(2, step) - 1)) {
			printf("\n");
			step += 1;
		}
	}
}


void main(void) {      /* ���׸�Ʈ Ʈ���� ���� ������ �����Ͽ� ������ �ߵǴ��� Ȯ���ϱ����� �����Լ� */
	int size = 0; 
	printf("�Է� ����Ʈ�� ���̸� �����ּ���:");      /* �Է¸���Ʈ�� ���̸� ���ϴ� �ܰ� */
	scanf("%d", &size);
	int *list = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		int temp = 0;
		printf("����Ʈ�� ������ �Է����ּ���: ");       /* �Է¸���Ʈ�� ���̰� �������� ������ ���̿� �°� ������� �Է¸���Ʈ�� ���� �Է��ϴ� �ܰ� */
		scanf("%d", &temp);
		list[i] = temp;
	}

	printf("\n�Է¹��� ����Ʈ�� ��\n");    /* �Է¹��� �Է¸���Ʈ�� ���� Ȯ���� ����ϴ� �ڵ� */
	for (int j = 0; j < size; j++) {
		printf("%d\t", list[j]);
	}
	printf("\n");
	
	int* segtree = seg_tree_const(list, size);     /* ���׸�Ʈ Ʈ���� �����ϰ� �����Լ����� ���� �޴� �ܰ� */
	print_tree(segtree, size);              /* �Է¸���Ʈ�� ���� ���׸�Ʈ Ʈ���� �ϼ��� ���� ������ִ� �ܰ� */

	int choose = 1;
	printf("\n\n���׸�Ʈ Ʈ���� Ȱ�� �˰����Դϴ�.\n");
	while (1) {			/* while���� Ȱ���� ���׸�Ʈ Ʈ���� Ȱ��˰��� ���� ������ ���� ���ϴ� �˰���� �Է¸���Ʈ�� ���� ������Ʈ �Ͽ����� ���׸�Ʈ Ʈ���� ������Ʈ�ϴ� ����� Ȯ���ϴ� �޴��� ������ �κ� */
		printf("\n���� ������ ���� ���Ͻ÷��� �Ѵٸ� 1��\n���׸�Ʈ Ʈ���� ���� ������Ʈ �ϽŴٸ� 2��\n���׸�Ʈ Ʈ���� ����Ϸ��� 3��\n���α׷��� �����Ͻ÷��� 0�� �Է����ּ���: ");
		scanf("%d", &choose);
		if (choose == 0)		/* ���α׷� ���� �޴� */
			break;
		else if (choose == 1) {      /* ���� ������ ���� ���ϴ� �Լ��� �����Լ� Ȱ��κ� */
			int q_s, q_e;
			printf("���� ���� ���������� �ε���:");   /* �ε����� �Է¸���Ʈ�� �ε����� ������� �Է��� �޴� ���� */
			scanf("%d", &q_s);
			printf("���� ���� �������� �ε���:");    /* ���� ������ ���� ���Ϸ��� �ε����� ���� �޾Ƶ鿩 �Ѱ��ִ� ���� */
			scanf("%d", &q_e);
			int sum = Getquery(segtree, size, q_s, q_e);
			printf("\n�����Ͻ� ���� ������ ����: %d �Դϴ�.\n", sum);
		}
		else if (choose == 2) {
			int change, cindex = 0;
			printf("�����Ͻ� ���� �ε����� �Է����ּ���: ");   /* �ε����� ���� �Է¸���Ʈ�� �������� �ε����� ���� �ް� ó���� */
			scanf("%d", &cindex);
			printf("�����Ͻ� ���� �Է����ּ���: ");      /* ���� �Է¸���Ʈ �ε��� ���� ������Ʈ�� ���� �Է¹޴� ���� */
			scanf("%d", &change);
			int d_value = change - list[cindex];
			Segtree_update(segtree, size,list[cindex], d_value);
			list[cindex] = change;
		}
		else if (choose == 3) {    /* ���� ���׸�Ʈ Ʈ���� ���¸� ����ϴ� �޴� */
			print_tree(segtree, size);
		}
		else {    /* ����ó�� */
			printf("�߸��� ���� �Է��ϼ̽��ϴ�.");
		}
	}
}